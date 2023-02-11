#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdatomic.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "partition.h"
#include "sync_group.h"
#include "forward_prop.h"
#include "data_main.h"

#define NUM_THREADS 94

struct sync_group sync_group;

void *feed_forward(void *arg)
{
    sync_control sc = SYNC_CONTROL_INIT;
    struct partition *partitions = arg;

    for (int i = 0; i < NUM_LAYERS - 1; ++i) {
        compute_z(partitions[i].z_stream, weights, layers[i], layers[i+1]);
        sync_threads(&sync_group, &sc);
        activation(partitions[i].activation_stream, layers[i+1]);
        sync_threads(&sync_group, &sc);
    }
    
    return NULL;
}


int main()
{
    sync_group_init(&sync_group, NUM_THREADS);

}