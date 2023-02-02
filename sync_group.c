#include "sync_group.h"

void toggle(int *i)
{
    if (*i == 0)
        *i = 1;
    else 
        *i = 0;
}

void sync_group_init(struct sync_group *sg, int num_threads)
{
    sg->num_threads = num_threads;
    sg->wait_group[0] = sg->num_threads;
    sg->wait_group[1] = sg->num_threads;
}
void sync_threads(struct sync_group *sg, sync_control *sync_control)
{
    //this code is juggling razor blades, but it works!
    atomic_fetch_sub_explicit(&sg->wait_group[*sync_control], 1, memory_order_relaxed);
    for (;;) {
        int num = atomic_load_explicit(&sg->wait_group[*sync_control], memory_order_relaxed);
        if (num == 0) {
            atomic_store_explicit(&sg->wait_group[*sync_control], sg->num_threads, memory_order_relaxed);
            toggle(sync_control);
            break;
        }
        if (num == sg->num_threads) {
            toggle(sync_control);
            break;
        }
    }
}
