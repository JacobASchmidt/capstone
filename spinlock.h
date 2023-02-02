#pragma once

#include <stdatomic.h>
#include "common.h"

struct spinlock {
    atomic_bool flag;
};

#define SPINLOCK_INIT (struct spinlock) {.flag = ATOMIC_FLAG_INIT}

void lock(struct spinlock *lock);
void unlock(struct spinlock *lock);
