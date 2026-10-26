#include "file.h"

// Функция вывода массива структур
void print(parallelogram *arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Фигура %d: ", (i+1));
        printf("a, b = %d, %d alpha = %d\n", arr[i]->a, arr[i]->b , arr[i]->alpha);
    }
}

// Функция по поиску квадратов
void kvadrat(parallelogram *arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if ((arr[i]->a == arr[i]->b) && (arr[i]->alpha == 90)) {
            printf("Фигура %d - КВАДРАТ\n", (i+1));
            count++;
        } 
    }
    printf("Кол-во квадратов - %d\n", count);  
}

// Функция по поиску прямоугольников
void pramoygolnik(parallelogram *arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if ((arr[i]->a != arr[i]->b) && (arr[i]->alpha == 90)) {
            printf("Фигура %d - ПРЯМОУГОЛЬНИК\n", (i+1));
            count++;
        } 
    }
    printf("Кол-во прямоугольников - %d\n", count);  
}