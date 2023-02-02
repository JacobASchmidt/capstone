#pragma once

#include "atomic_double.h"
#include "ranges.h"

void compute_z(struct z_range range, const double **weights, const struct atomic_double *input, struct atomic_double *output);
void activation(struct activation_range range, struct atomic_double *output);