#include "load-img.hpp"

static int get_int(FILE *file);

std::vector<Image> getImages(char *images_filename, char *labels_filename) {
    FILE *imgs_fp = fopen(images_filename, "rb");
    FILE *labels_fp = fopen(labels_filename, "rb");
    std::vector<Image> images;
    Image img;
    if (imgs_fp == NULL || labels_fp == NULL) {
        throw ENOENT;
    }
    if ((get_int(imgs_fp) != IMG_MAGIC_NUM) || (get_int(labels_fp) != LABEL_MAGIC_NUM)) {
        throw BAD_FILE;
    }
    int num_imgs = get_int(imgs_fp);
    int num_labels = get_int(labels_fp);
    int num_rows = get_int(imgs_fp);
    int num_cols = get_int(imgs_fp);
    if (num_imgs != num_labels || num_rows != ROWS || num_cols != COLS) {
        throw BAD_FILE;
    }

    for (int i = 0; i < num_imgs; ++i) {
        if (feof(labels_fp)) {
            throw BAD_FILE;
        }
        img.label = getc(labels_fp);
        for (int j = 0; j < ROWS * COLS; ++j) {
            if (feof(imgs_fp)) {
                throw BAD_FILE;
            }
            img.pixels[j] = (double)getc(imgs_fp) / (double)255;
        }
        images.push_back(img);
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