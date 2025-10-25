#include <stdio.h>
#include <pthread.h>

// Thread function
void* double_cgpa(void* arg) {
    double cgpa = *(double*)arg;  // void* ko double* me cast karke value lo
    printf("Thread received CGPA: %.2f\n", cgpa);
    printf("Double CGPA: %.2f\n", cgpa * 2);
    return NULL;
}

int main() {
    pthread_t thread_id;
    double cgpa = 2.8;

    printf("Creating thread with CGPA: %.2f\n", cgpa);

    // Thread create karo aur CGPA ka address pass karo
    pthread_create(&thread_id, NULL, double_cgpa, &cgpa);

    pthread_join(thread_id, NULL);

    printf("Main thread done.\n");
    return 0;
}
