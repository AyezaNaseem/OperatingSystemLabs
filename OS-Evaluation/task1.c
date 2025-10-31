//Write a C program that uses threads to perform operations on shared variables:
//.  Create two global variables:
  //initialized to 0
  //initialized to 0
//2.  Create 3 threads:
    //Thread 1: Adds all of the numbers between 1 to 100 to 100 times
   //Thread 2: Adds all of the numbers between 101 to 200 to 100 times
   //Thread 3: Adds all of the numbers between 201 to 300 to 100 times
//3.  Use mutex to protect access to both shared variables
//4.  Each thread prints when it starts and finishes
//5.  Main thread prints final results:
  //Total sum (should be 45150, which is sum of 1 to 300)   Total count (should be 300)
#include <stdio.h>
#include <pthread.h>

int total_sum = 0;   // shared variable 1
int total_count = 0; // shared variable 2
pthread_mutex_t lock; // creating mutex for shared variables

void* add_numbers(void* arg) {
    int start = ((int*)arg)[0];
    int end = ((int*)arg)[1];
    int sum = 0, count = 0;

    printf("Thread for range %d-%d started.\n", start, end);

    for (int t = 0; t < 100; t++) {
        for (int i = start; i <= end; i++) {
            sum += i;
            count++;
        }
    }

    pthread_mutex_lock(&lock);
    total_sum += sum;
    total_count += count;
    pthread_mutex_unlock(&lock);

    printf("Thread for range %d-%d started.\n" , start,end);
}
int main() {
    pthread_t t1, t2, t3;
    int range1[2] = {1, 100};
    int range2[2] = {101, 200};
    int range3[2] = {201, 300};

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, add_numbers, (void*)range1);
    pthread_create(&t2, NULL, add_numbers, (void*)range2);
    pthread_create(&t3, NULL, add_numbers, (void*)range3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&lock);

    printf("\nFinal Results:\n");
    printf("Total Sum: %d\n", total_sum / 100);   
    printf("Total Count: %d\n", total_count / 100);

    return 0;
}
    


