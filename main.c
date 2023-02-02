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
#include "forward_prop.h"
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
    // this is almost certainly wrong, fix in future
    int num_each = i*j / num_workers;

    int idx = 0;

    for (int k = 0; k < i*j; k += num_each) {
        int low = k;
        int high = k + num_each;

        int low_i = low / num_workers;
        int high_i = high / num_workers;

        int low_j = low % num_workers;
        int high_j = high % num_workers;

        int num_weights = j;

        ranges[idx++] = (struct range) {
            .z_range = {
                .i_low = low_i,
                .i_high = high_i,
                .j_low = low_j,
                .j_high = high_j,
                .j_max = j
            },
        };
    }
    //zero out rest, so they do nothing
    while (idx < num_workers)
        ranges[idx++] = (struct range){};
    

    //again this is hard to get right
    idx = 0;
    int num_each_activation = i / num_workers;
    for (int k = 0; k < i; k += num_each_activation) {
        ranges[idx++].activation_range = (struct activation_range) {
            .low = k,
            .high = k + num_each_activation,
        };
    }
    //the rest are handled by zeroing out ranges
    
    // I think this is actually pretty close to correct after all
}


int main()
{
    sync_group_init(&sync_group, NUM_THREADS);

}