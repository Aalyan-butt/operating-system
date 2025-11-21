 #include <stdio.h>
 #include <pthread.h>
 #include <unistd.h>

 int turn;
 int flag[2] = {0, 0};
 int counter = 0; // Shared resource

 void* process(void* arg) {
    int id = *(int*)arg;
    int other = 1- id;

     for (int i = 0; i < 5; i++) {
         // Entry section
        flag[id] = 1;
        turn = other;
        while (flag[other] && turn == other);

         // Critical section
        counter++;
        printf("Thread %d in critical section | Counter = %d\n", id,
 counter);
         sleep(1);
          // Exit section
         flag[id] = 0;
         sleep(1);
   }
    return NULL;
 }

 int main() {
     pthread_t t1, t2;
     int id1 = 0, id2 = 1;
     
     pthread_create(&t1, NULL, process, &id1);
     pthread_create(&t2, NULL, process, &id2);
     
     pthread_join(t1, NULL);
     pthread_join(t2, NULL);
     
     printf("Final Counter Value: %d\n", counter);
     return 0;

}

