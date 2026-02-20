#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Для рандома
#include <sys/time.h> // Это библиотека перносима только на UNIX/Linux, time.h на любые и с ней работает suseconds_t
#define N 4



// Структура автомобиля
typedef struct {
    char mark[100];
    int release;
    int power;
    int price;
} car;

void Output(car afto[], int c);
void fill(car afto[], int c);
void SelectSort(car afto[], int c);