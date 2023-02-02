#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdatomic.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ranges.h"
#include "sync_group.h"
#include "data.h"

#define NUM_THREADS 94

struct sync_group sync_group;

void *feed_forward(void *arg)
{
    sync_control sc = SYNC_CONTROL_INIT;
    struct range *ranges = arg;

    for (int i = 0; i < NUM_LAYERS - 1; ++i) {
        compute_z(ranges[i].z_range, weights, layers[i], layers[i+1]);
        sync_threads(&sync_group, &sc);
        activation(ranges[i].activation_range, layers[i]);
        sync_threads(&sync_group, &sc);
    }
    
    return NULL;
}


void split_ranges(int num_workers, int i, int j, struct range *ranges)
{
    // this code is hard to get right, might be buggy
    int num_each = i*j / num_workers;

    for (int k = 0; k < i*j; k += ) {
        
    }

}


int main()
{
    sync_group_init(&sync_group, NUM_THREADS);

}