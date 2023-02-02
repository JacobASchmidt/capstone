#include "spinlock.h"

void lock(struct spinlock *lock)
{
    for (;;) {
        bool want = false;
        //I'm not so sure about the memory order for the fail case
        while (!atomic_compare_exchange_weak_explicit(&lock->flag, &want, 1, memory_order_acquire, memory_order_relaxed))
        {
            while (atomic_load_explicit(&lock->flag, memory_order_relaxed))
                ;
            want = false;
        }
    }
    
}
void unlock(struct spinlock *lock)
{
    atomic_store_explicit(&lock->flag, false, memory_order_release);
}