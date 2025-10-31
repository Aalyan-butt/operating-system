#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
   (void)arg;
   printf("New Thread is running\n");
   printf("Thread ID: %lu\n", (unsigned long)pthread_self());
   return NULL;
}
int main() {
   pthread_t thread_id;
   printf("Main Thread is running\n");
   printf("Main Thread ID: %lu\n", pthread_self());
   
   pthread_create(&thread_id, NULL, thread_function, NULL);
   
   pthread_join(thread_id, NULL);
   printf("Main Thread is exiting....\n");
   return 0;
}