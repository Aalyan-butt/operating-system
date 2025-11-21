#include <stdio.h>
#include <pthread.h>
int counter = 0; // Shared resource
pthread_mutex_t lock; // Declare mutex
void* increment(void* arg) {
for (int i = 0; i < 100000; i++) {
pthread_mutex_lock(&lock); // Lock before accessing shared variable
counter++;
pthread_mutex_unlock(&lock); // Unlock after done
}
return NULL;
}
int main() {
pthread_t t1, t2;
pthread_mutex_init(&lock, NULL); // Initialize mutex
pthread_create(&t1, NULL, increment, NULL);
pthread_create(&t2, NULL, increment, NULL);
pthread_join(t1, NULL);
pthread_join(t2, NULL);
printf("Expected counter value: 200000\n");
printf("Actual counter value: %d\n", counter);
pthread_mutex_destroy(&lock); // Clean up
return 0;
}