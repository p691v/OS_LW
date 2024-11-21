#ifndef OS_LABS_UTILS_H
#define OS_LABS_UTILS_H

#include <pthread.h>
#pragma once


struct Circle {
    float radius;
    long* successful_n;
    long iterations;
    pthread_mutex_t mutex;
};

void* oneRound(void *arg);

double Area (long threads_num, float radius, long precision);

#endif //OS_LABS_UTILS_H
