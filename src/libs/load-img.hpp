#ifndef LOAD_IMG_H
#define LOAD_IMG_H

#define ROWS    28
#define COLS    28
#define IMG_MAGIC_NUM 2051
#define LABEL_MAGIC_NUM 2049

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Image {
    double pixels[ROWS * COLS];
    unsigned char label;
};

struct Images {
    Image *images;
    int num_images;
    bool err_occurred;
};

Images getImages(char *images_filename, char *labels_filename);

#endif