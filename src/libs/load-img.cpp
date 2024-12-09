#include "load-img.hpp"

static int get_int(FILE *file);

int get_int(FILE *file) {
    int val = 0;
    for (unsigned int i = 0; (i < sizeof(int)) && !feof(file); ++i) {
        val <<= 8;
        val += fgetc(file);
    }
    return val;
}

std::vector<std::vector<float>> GetImages(char *images_filename, float img_variance) {
    std::vector<std::vector<float>> images;
    std::vector<float> image;
    FILE *fp = fopen(images_filename, "rb");
    if (fp == NULL) {
        throw "File could not be opened.";
    }
    if (get_int(fp) != IMG_MAGIC_NUM) {
        throw "Invalid image.";
    }
    int num_imgs = get_int(fp);
    int image_size = get_int(fp) * get_int(fp);
    int next_chr;
    for (int i = 0; i < num_imgs; ++i) {
        for (int j = 0; j < image_size; ++j) {
            if ((next_chr = getc(fp)) == EOF) {
                printf("i=%d, j=%d, image_size=%d\n", i, j, image_size);
                throw "file ended early";
            }
            image.push_back((((float)next_chr / 255)) * img_variance);
        }
        images.push_back(image);
        image.clear();
    }
    if (!((next_chr = getc(fp)) == EOF)) {
        printf("%d ", next_chr);
        while (!feof(fp)) {
            printf("%d ", getc(fp));
        }
        throw "GetImages: incorrect number of images read";
    }
    fclose(fp);
    return images;
}

std::vector<std::vector<float>> GetLabels(char *labels_filename) {
    std::vector<std::vector<float>> labels;
    std::vector<float> empty{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    FILE *fp = fopen(labels_filename, "rb");
    if (fp == NULL) {
        throw "File could not be opened.";
    }
    if (get_int(fp) != LABEL_MAGIC_NUM) {
        throw "Invalid file.";
    }

    int num_labels = get_int(fp);
    int next_chr;
    for (int i = 0; i < num_labels; ++i) {
        if ((next_chr = getc(fp)) == EOF) {
            throw "File not right length.";
        }
        labels.push_back(empty);
        labels[i][next_chr] = 1;
    }
    fclose(fp);
    return labels;
}