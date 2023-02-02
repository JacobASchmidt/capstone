#include "atomic_double.h"

double atomic_double_unchecked_load(const struct atomic_double *ad)
{
    return ad->d;
}

void atomic_double_unchecked_store(struct atomic_double *ad, double val)
{
    ad->d = val;
}

double atomic_double_load(struct atomic_double *ad)
{
    double ret;
    lock(&ad->spinlock);
    ret = ad->d;
    unlock(&ad->spinlock);
    return ret;
}

double atomic_double_store(struct atomic_double *ad, double val)
{
    double ret;
    lock(&ad->spinlock);
    ret = ad->d;
    ad->d = val;
    unlock(&ad->spinlock);
    return ret;
}

double atomic_double_fetch_add(struct atomic_double *ad, double delta)
{
    double ret;
    lock(&ad->spinlock);
    ret = ad->d;
    ad->d += delta;
    unlock(&ad->spinlock);
    return ret;
}

void atomic_double_update(struct atomic_double *ad, double (*f)(double))
{
    lock(&ad->spinlock);
    ad->d = f(ad->d);
    unlock(&ad->spinlock);
}


void atomic_double_unchecked_update(struct atomic_double *ad, double (*f)(double))
{
    ad->d = f(ad->d);
}
