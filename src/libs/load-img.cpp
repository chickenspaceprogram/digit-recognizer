#include "load-img.hpp"

static int get_int(FILE *file);

Images getImages(char *images_filename, char *labels_filename) {
    FILE *imgs_fp = fopen(images_filename, "rb");
    FILE *labels_fp = fopen(labels_filename, "rb");
    Images images = {.err_occurred = false};
    int num_imgs;
    if (imgs_fp == NULL || labels_fp == NULL) {
        images.err_occurred = true;
        return images;
    }
    if ((get_int(imgs_fp) != IMG_MAGIC_NUM) || (get_int(labels_fp) != LABEL_MAGIC_NUM)) {
        images.err_occurred = true;
        fclose(imgs_fp); fclose(labels_fp);
        return images;
    }
    if ((num_imgs = get_int(imgs_fp)) != get_int(labels_fp) || get_int(imgs_fp) != ROWS || get_int(imgs_fp) != COLS) {
        images.err_occurred = true;
        fclose(imgs_fp); fclose(labels_fp);
        return images;
    }
    images.num_images = num_imgs;
    images.images = (Image *)malloc(sizeof(Image) * images.num_images);
    if (images.images == NULL) {
        images.err_occurred = true;
        fclose(imgs_fp); fclose(labels_fp);
        return images;
    }

    for (int i = 0; i < images.num_images; ++i) {
        if (feof(labels_fp)) {
            images.err_occurred = true;
            fclose(imgs_fp); fclose(labels_fp);
            free(images.images);
            return images;
        }
        images.images[i].label = getc(labels_fp);
        for (int j = 0; j < ROWS * COLS; ++j) {
            if (feof(imgs_fp)) {
                images.err_occurred = true;
                fclose(imgs_fp); fclose(labels_fp);
                free(images.images);
                return images;
            }
            images.images[i].pixels[j] = (double)getc(imgs_fp) / (double)255;
        }
    }
    fclose(imgs_fp); fclose(labels_fp);
    return images;

}

int get_int(FILE *file) {
    int val = 0;
    for (int i = 0; i < sizeof(int) && !feof(file); ++i) {
        val += fgetc(file);
        val <<= 8;
    }
    return val;
}