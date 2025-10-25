#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITERATIONS 1000000

int count = 10;
pthread_mutex_t mutex;

void critical_section(int process) {
    if (process == 0) {
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count--;
    } 
    else if (process == 1) {
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count++;
    } 
    else if (process == 2) {
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count += 2;
    }
    else if (process == 3) {
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count -= 2;
    }
}

void *process0(void *arg) {
    pthread_mutex_lock(&mutex);
    critical_section(0);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *process1(void *arg) {
    pthread_mutex_lock(&mutex);
    critical_section(1);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *process2(void *arg) {
    pthread_mutex_lock(&mutex);
    critical_section(2);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *process3(void *arg) {
    //pthread_mutex_lock(&mutex);  // commented — unsafe intentionally
    critical_section(3);
    //pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread0, thread1, thread2, thread3;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread0, NULL, process0, NULL);
    pthread_create(&thread1, NULL, process1, NULL);
    pthread_create(&thread2, NULL, process2, NULL);
    pthread_create(&thread3, NULL, process3, NULL); // 🔹 Added this

    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    pthread_mutex_destroy(&mutex);

    printf("Final count: %d\n", count);
    return 0;
}
