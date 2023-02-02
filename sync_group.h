#pragma once

#include <stdatomic.h>
#include "common.h"


typedef int sync_control;

#define SYNC_CONTROL_INIT 0

struct sync_group {
    atomic_int wait_group[2];
    int num_threads;
};

void sync_group_init(struct sync_group *sg, int num_threads);
void sync_threads(struct sync_group *sg, sync_control *sync_control);

