#include "load-img.hpp"

static int get_int(FILE *file);

int get_int(FILE *file) {
    int val = 0;
    for (int i = 0; i < sizeof(int) && !feof(file); ++i) {
        val += fgetc(file);
        val <<= 8;
    }
    return val;
}

std::vector<std::vector<float>> GetImages(char *images_filename) {
    std::vector<std::vector<float>> images;
    std::vector<float> image;
    FILE *fp = fopen(images_filename, "rb");
    if (fp == NULL) {
        throw "File could not be opened.";
    }
    if (get_int(fp) != IMG_MAGIC_NUM) {
        throw "Invalid image.";
    }

    int image_size = get_int(fp) * get_int(fp);
    while (!feof(fp)) {
        for (int i = 0; i < image_size; ++i) {
            if (feof(fp)) {
                throw "file ended early";
            }
            image.push_back((float)getc(fp) / 255);
        }
        images.push_back(image);
        image.clear();
    }
}

std::vector<std::vector<float>> GetLabels(char *labels_filename) {
    std::vector<std::vector<float>> labels;
    std::vector<float> empty{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    FILE *fp = fopen(labels_filename, "rb");
    if (fp == NULL) {
        throw "File could not be opened.";
    }
    if (get_int(fp) != LABEL_MAGIC_NUM) {
        throw "Invalid file."
    }

    int num_labels = get_int(fp);
    int counter = 0;
    char chr;
    while (!feof(fp)) {
        labels.push_back(empty);
        labels[++counter][getc(fp)] = 1;
    }
    return labels;
}