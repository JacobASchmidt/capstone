#pragma once

#include "atomic_double.h"

#define INPUT_SIZE  94
#define HIDDEN_SIZE 25
#define OUTPUT_SIZE 5
#define NUM_LAYERS  4

//check with above and should be max layer size that is not the input size
#define MAX_WEIGHT_SIZE HIDDEN_SIZE

struct weight_dim {
    int first, second;
};
