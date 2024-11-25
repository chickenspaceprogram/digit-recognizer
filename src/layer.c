#include "layer.h"

void free_layer(Layer *layer);
void set_activations(
    Layer *current,
    Layer *prev,
    float (*activation_fn)(float)
);

Layer newLayer(int size, int prev_size) {
    Layer layer = {.size = size, .malloc_error = false, .free = &free_layer, .set_activations = &set_activations};
    layer.weights = malloc(sizeof(double) * layer.size * prev_size);
    if (layer.weights == NULL) {
        layer.malloc_error = true;
        goto weights;
    }

    for (int i = 0; i < layer.size * prev_size; ++i) {
        layer.weights[i] = rand_weight();
    }

    layer.activations = malloc(sizeof(double) * layer.size);
    if (layer.activations == NULL) {
        layer.malloc_error = true;
        goto activations;
    }
    
    layer.activations_no_fn = malloc(sizeof(double) * layer.size);
    if (layer.activations_no_fn == NULL) {
        layer.malloc_error = true;
        goto activations_no_fn;
    }

    layer.biases = malloc(sizeof(double) * layer.size);
    if (layer.biases == NULL) {
        layer.malloc_error = true;
        goto biases;
    }

    for (int i = 0; i < layer.size; ++i) {
        layer.biases[i] = 0;
    }
    
    biases:
    free(layer.activations);
    activations_no_fn:
    free(layer.activations_no_fn);
    activations:
    free(layer.weights);
    weights:
    return layer;
}

void free_layer(Layer *layer) {
    free(layer->activations);
    free(layer->activations_no_fn);
    free(layer->biases);
    free(layer->weights);
}

void set_activations(Layer *current, Layer *prev, float (*activation_fn)(float)) {
    mtrx_vec_mult(current->weights, prev->activations, current->activations_no_fn, prev->size, current->size);
    vec_add(current->biases, current->activations_no_fn, current->size);
    for (int i = 0; i < current->size; ++i) {
        current->activations[i] = activation_fn(current->activations_no_fn[i]);
    }
}