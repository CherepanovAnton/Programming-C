/*Упр. 7*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define N 5

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;  
int flag = 1;

typedef struct {
    int num;
    char *msg;
} threadData;

void killThread(void *arg) {
    int num = *(int *)arg;
    printf("Pthread%d dead\n", num);
}

void *thread(void *argP) {
    threadData *d =  (threadData *)argP;
    pthread_mutex_lock(&mtx);
    while (flag) {
        pthread_cond_wait(&cond, &mtx);
    }
    printf("Pthread%d: %s\n", d->num, d->msg);
    flag = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mtx);
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
    
    
    for (int i = 1; i <= N; i++) {
            pthread_mutex_lock(&mtx);
            while (!flag) pthread_cond_wait(&cond, &mtx);
            printf("Main: msg%d\n", i);
            flag = 0;
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&mtx);
    }

    for (int i = 0; i < N; i++) {
         pthread_join(tid[i], NULL);
    }
}
