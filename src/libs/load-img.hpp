#ifndef LOAD_IMG_HPP
#define LOAD_IMG_HPP

#define ROWS    28
#define COLS    28
#define IMG_MAGIC_NUM 2051
#define LABEL_MAGIC_NUM 2049

#define IMG_ENOENT 1
#define BAD_FILE 2

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <vector>

std::vector<std::vector<float>> GetImages(char *images_filename);
std::vector<std::vector<float>> GetLabels(char *labels_filename);

#endif