#include "forward_prop.h"

double ReLU(double d)
{
    if (d < 0)
        return 0;
    else 
        return d;
}

void compute_z(struct z_stream z_stream, const double (*weights[MAX_WEIGHT_SIZE])[], const struct atomic_double *input, struct atomic_double *output)
{
    while (!z_stream_done(z_stream))
    {
        struct z_element z_indices = z_stream_next(&z_stream);
        int i = z_indices.i, j = z_indices.j;
        double input_val = atomic_double_unchecked_load(&input[i]);
        double res = input_val * (*weights[j])[i]; // might want to fix this for cache, dirty writes can be a killer
        atomic_double_fetch_add(&output[i], res); // this also might be an optimzation point, maybe not write to main memory every update
    }
}

void activation(struct activation_stream stream, struct atomic_double *output)
{
    while (!activation_stream_done(stream)) {
        activation_element i = activation_stream_next(&stream);
        atomic_double_unchecked_update(&output[i], ReLU);
    }
}
