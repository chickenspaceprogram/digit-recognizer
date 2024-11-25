#ifndef NETWORK_H
#define NETWORK_H

typedef struct network Network;

struct network {
    int input_len;
    int hidden_len;
    int output_len;
    int num_hidden_layers;
    void (*free)(Network *);
};

#endif