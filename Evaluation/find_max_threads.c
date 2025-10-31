// Write a C program that finds the maximum value in an array using threads:

 

// 1.  Create an array of 20 integers with values: {45, 23, 67, 89, 12, 34, 78, 90, 56, 21, 38, 72,

// 44, 91, 15, 83, 29, 66, 54, 88}

// 2.  Create 4 threads, each finding maximum in 5 elements:   Thread 1: elements 0-4

//   Thread 2: elements 5-9

//   Thread 3: elements 10-14

//   Thread 4: elements 15-19

// 3.  Pass the starting index and count to each thread using a structure

// 4.  Each thread:

//   Finds maximum in its portion

//   Prints the maximum value it found   Returns the maximum value

// 5.  Main thread collects all return values and finds overall maximum

// -----------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// elemenets each threas has and number of threads
#define PART_SIZE 5
#define NUM_THREADS 4

// array of 20 inetegers values
int arr[20] = {45, 23, 67, 89, 12,
                34, 78, 90, 56, 21,
                38, 72, 44, 91, 15,
                83, 29, 66, 54, 88};

// create the struct which pass data to threads
struct ThreadData {
    int start;  
    int count;  
};

// create the function to find max in each thread
void* find_max(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    int start = data->start;
    int count = data->count;

    int max = arr[start];
    for (int i = start + 1; i < start + count; i++) {
        if (arr[i] > max)
            max = arr[i];
    }

    printf("Thread handling elements %d to %d found max = %d\n", start, start + count - 1, max);

    // Return result throught malloc which  free the main thread
    int* result = (int*)malloc(sizeof(int));
    *result = max;
    pthread_exit(result);
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct ThreadData tdata[NUM_THREADS];
    int* thread_result;
    int overall_max = 0;

    // create the threads here
    for (int i = 0; i < NUM_THREADS; i++) {
        tdata[i].start = i * PART_SIZE;
        tdata[i].count = PART_SIZE;
        pthread_create(&threads[i], NULL, find_max, &tdata[i]);
    }

    // get the results from each thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], (void**)&thread_result);

        if (i == 0 || *thread_result > overall_max)
            overall_max = *thread_result;

        free(thread_result); // free allocated memory
    }

    printf("\nOverall maximum value in array = %d\n", overall_max);

    return 0;
}

