#pragma once

#include "atomic_double.h"

//check with data.c and should be max layer size that is not the input size
#define MAX_WEIGHT_SIZE HIDDEN_SIZE

struct atomic_double *get_layers() 
const int *get_layer_dims()

struct weight_dim {
    int first, second;
};

const double *get_weights();
const struct weight_dim *get_weight_dims();