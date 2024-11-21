#include "../include/utils.h"
#include <pthread.h>
#include <random>

//pthread_mutex_t mutex;

void *oneRound(void *arg) {
    auto *data = (Circle *)arg;
    int local_count = 0;
    std::mt19937 rng(time(nullptr));
    std::uniform_real_distribution<float> dist(-(data->radius), data->radius);
    for (int i = 0; i < data->iterations; ++i) {
        float x = dist(rng), y = dist(rng);
        if (x * x + y * y <= (data->radius) * (data->radius))
            ++local_count;
    }
    pthread_mutex_lock(&(data->mutex));
    (*data->successful_n) += local_count;
    pthread_mutex_unlock(&(data->mutex));

    return nullptr;
}


double Area(long threads_num, float radius, long precision) {
    pthread_t threads[threads_num];
    long successful_n = 0;
    float default_area = (radius * 2) * (radius * 2);
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, nullptr);
    if (threads_num > precision) {
        threads_num = 1;
    }
    long iterations_per_thread = precision / threads_num;

    for (int i = 0; i < threads_num; ++i) {
        Circle c = {radius, &successful_n, iterations_per_thread, mutex};
        pthread_create(&threads[i], nullptr, oneRound, &c);

    }
    for (int i = 0; i < threads_num; ++i) {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);
    return static_cast<double> (successful_n) / precision * default_area;
}