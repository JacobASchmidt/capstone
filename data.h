#pragma once

#include "atomic_double.h"

#define INPUT_SIZE  94
#define HIDDEN_SIZE 25
#define OUTPUT_SIZE 5
#define NUM_LAYERS  4

#define MAX_WEIGHT_SIZE HIDDEN_SIZE

double weights1[INPUT_SIZE][MAX_WEIGHT_SIZE] = {{0}};
double weights2[HIDDEN_SIZE][MAX_WEIGHT_SIZE] = {{0}};
double weights3[HIDDEN_SIZE][MAX_WEIGHT_SIZE] = {{0}};


double (*weights[MAX_WEIGHT_SIZE])[] = {weights1, weights2, weights3};

struct weight_dim {
    int first, second;
};

struct weight_dim weight_dims[] = {
    {.first = INPUT_SIZE, .second = HIDDEN_SIZE},
    {.first = HIDDEN_SIZE, .second = HIDDEN_SIZE},
    {.first = HIDDEN_SIZE, .second = OUTPUT_SIZE},
};


atomic_double input[INPUT_SIZE] = {0};
atomic_double layer1[HIDDEN_SIZE] = {0};
atomic_double layer2[HIDDEN_SIZE] = {0};
atomic_double output[OUTPUT_SIZE] = {0};

atomic_double *layers[] = {input, layer1, layer2, output};

size_t layer_dims[] = {
    INPUT_SIZE,
    HIDDEN_SIZE,
    HIDDEN_SIZE,
    OUTPUT_SIZE
};