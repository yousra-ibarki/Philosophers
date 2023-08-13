#include <stdio.h>
#include <sys/time.h>

// int main() {
//     struct timeval tv;
//     if (gettimeofday(&tv, NULL) == 0) {
//         printf("Current time: %ld seconds, %d microseconds\n", tv.tv_sec, tv.tv_usec);
//     } else {
//         perror("gettimeofday");
//     }
//     return 0;
// }

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>


int main()
{
    struct timeval begin;
    int i = 0;
    int sum_millisecond;
    gettimeofday(&begin, NULL);
    sum_millisecond = ((begin.tv_sec / 1000) + (begin.tv_usec * 1000));
   printf("%d\n", sum_millisecond);

}

// void* thread_function(void* arg) {
//     int value = *(int*)arg;
//     printf("Thread started. Received value: %d\n", value);
//     return NULL;
// }

// int main() {
//     pthread_t thread_id;
//     int value = 42;

//     printf("Creating thread...\n");

//     // Create the thread and pass the value as an argument
//     int status = pthread_create(&thread_id, NULL, thread_function, &value);
//     int statuss = pthread_create(&thread_id, NULL, thread_function, &value);
//     if (status != 0) {
//         fprintf(stderr, "Error creating thread. Exiting.\n");
//         return 1;
//     }

//     // Wait for the thread to finish (synchronization point)
//     pthread_join(thread_id, NULL);
//     pthread_join(thread_id, NULL);

//     printf("Main thread finished.\n");
//     return 0;
// }


