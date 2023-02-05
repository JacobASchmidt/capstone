#pragma once

#include "atomic_double.h"
#include "data.h"
#include "partition.h"

void compute_z(struct z_stream z_stream, const double *(*weights[MAX_WEIGHT_SIZE]), const struct atomic_double *input, struct atomic_double *output);
void activation(struct activation_stream activation_stream, struct atomic_double *output);