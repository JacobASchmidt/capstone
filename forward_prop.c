#include "forward_prop.h"

double ReLU(double d)
{
    if (d < 0)
        return 0;
    else 
        return d;
}

void compute_z(struct z_range range, const double *(*weights[MAX_WEIGHT_SIZE]), const struct atomic_double *input, struct atomic_double *output)
{

    for (int i = range.i_low; i < range.i_high; ++i) {
        double res = 0;
        int j_low = 0, j_high = range.j_max;
        if (i == range.i_low) 
            j_low = range.j_low;

        if (i == range.i_high)
            j_high = range.j_high;
            
        for (int j = j_low; j < j_high; ++j) {
            double input_val = atomic_double_unchecked_load(&input[i]);
            res += input_val * (*weights[j])[i]; //this is terrible for cache, must fix for big speedup
        }
        atomic_double_fetch_add(&output[i], res);
    }
}

void activation(struct activation_range range, struct atomic_double *output)
{
    for (int i = range.low; i < range.high; ++i) 
        atomic_double_update(&output[i], ReLU);
}
