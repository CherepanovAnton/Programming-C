#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define N 5
#define C 10


typedef struct {
    int num;
    char *msg;
} threadData;

void *thread_SleepSort(void *arg) {
    int num = *(int *)arg;
    sleep(num);
    printf("%d ", num);
    fflush(stdout);
}

void SleepSort(int arr[], int c_arr) {
    pthread_t tid[c_arr];
    for (int i = 0; i < c_arr; i++) {
        pthread_create(&tid[i], NULL, thread_SleepSort, &arr[i]);
    }
    
    for (int i = 0; i < c_arr; i++) {
        pthread_join(tid[i], NULL);
    }
}

void killThread(void *arg) {
    int num = *(int *)arg;

    printf("Pthread%d dead\n", num);
}

void *thread(void *argP) {
    threadData *d =  (threadData *)argP;
    pthread_cleanup_push(killThread, &(d->num));
    printf("Pthread%d: %s\n", d->num, d->msg);
    sleep(3);
    printf("Pthread%d: Succes\n", d->num);
    pthread_cleanup_pop(0);
}

int main() {
    pthread_t tid[N];
    threadData data[N];
    char *messages[] = {"msg1", "msg2", "msg3", "msg4", "msg5"};
    for (int i = 0; i < N; i++) {
        data[i].num = i + 1;
        data[i].msg = messages[i];
        pthread_create(&tid[i], NULL, thread, &data[i]);
    } 
    

    for (int i = 0; i < N; i++) {
         pthread_cancel(tid[i]);
    }

    for (int i = 0; i < N; i++) {
         pthread_join(tid[i], NULL);
    }
    
    for (int i = 1; i <= N; i++) {    
        printf("Main: msg%d\n", i);
    }

    int arr[] = {3, 1, 6, 8, 2, 3, 5, 8, 9, 2};
    printf("=========== Исходный массив =========\n");
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n=========== SleepSort =========\n");
    SleepSort(arr, 10);
    printf("\n");
}