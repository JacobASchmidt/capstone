#pragma once
#include "spinlock.h"

struct atomic_double {
    struct spinlock spinlock;
    double d;
};

double atomic_double_unchecked_load(const struct atomic_double *ad);
void atomic_double_unchecked_store(struct atomic_double *ad, double val);

double atomic_double_load(struct atomic_double *ad);
double atomic_double_store(struct atomic_double *ad, double val);

double atomic_double_fetch_add(struct atomic_double *ad, double delta);
void atomic_double_update(struct atomic_double *ad, double (*f)(double));

void atomic_double_unchecked_update(struct atomic_double *ad, double (*f)(double));

