/* 
Лаба 12
Многофайловый проект. Библиотеки
Оценка 5
StaticMain - исполняемый файл с статической библиотекой
DinamicMain - исполняемый файл с динамической библиотекой
*/

#include "FuncLab12.h"

int main() {
    printf("============== Исходный данные ==============\n");
    car Cars[N];
    fill(Cars, N);
    Output(Cars, N);
    printf("============== Сортировка ==============\n");
    SelectSort(Cars, N);
    Output(Cars, N);

    // Реализация на оценку 5
    struct timeval start;
    struct timeval end;
    long seconds = 0;
    long NanoSeconds = 0;

    int C[] = {100, 10000, 100000};
    for (int i = 0; i < 3; i++) {
        printf("%d\n", i);
        long seconds = 0;
        long NanoSeconds = 0;
        car *Afto = malloc(C[i] * sizeof(car));
        fill(Afto, C[i]);
        gettimeofday(&start, NULL);
        SelectSort(Afto, C[i]);
        gettimeofday(&end, NULL);
        seconds = end.tv_sec - start.tv_sec;
        if (end.tv_usec < start.tv_usec) {
            seconds--;
            NanoSeconds = end.tv_usec + 1000000 - start.tv_usec;
        } else {
            NanoSeconds = end.tv_usec - start.tv_usec; 
        }
        printf("N = %d\n", C[i]);
        printf("Time: %ld.%ld сек.\n", seconds, NanoSeconds);
        free(Afto);
        Afto = NULL;
    }
    
}