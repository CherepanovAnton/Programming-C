/*
Вариант 25
Создайте структуру Параллелограмм с элементами a, b – стороны
параллелограмма и a - угол между сторонами. Для К заданных фигур
определить k1 – количество квадратов и k2 – количество прямоугольников.
*/
#include <stdio.h>

typedef struct {
        int a;
        int b;
        int alpha;
} parallelogram;

// Функция вывода массива структур
void print(parallelogram arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Фигура %d: ", (i+1));
        printf("a, b = %d, %d alpha = %d\n", arr[i].a, arr[i].b , arr[i].alpha);
    }
}

// Функция по поиску квадратов
void kvadrat(parallelogram arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if ((arr[i].a == arr[i].b) && (arr[i].alpha == 90)) {
            printf("Фигура %d - КВАДРАТ\n", (i+1));
            count++;
        } 
    }
    printf("Кол-во квадратов - %d\n", count);  
}

// Функция по поиску прямоугольников
void pramoygolnik(parallelogram arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if ((arr[i].a != arr[i].b) && (arr[i].alpha == 90)) {
            printf("Фигура %d - ПРЯМОУГОЛЬНИК\n", (i+1));
            count++;
        } 
    }
    printf("Кол-во прямоугольников - %d\n", count);  
}

int main() {
    int k;
    printf("Введите кол-во фигур ");
    scanf("%d", &k);
    parallelogram figures[k];
    for (int i = 0; i < k; i++) {
        printf("Введите размер стороны a: ");
        scanf("%d", &figures[i].a);
        printf("Введите размер стороны b: ");
        scanf("%d", &figures[i].b);
        printf("Введите размер угла alpha: ");
        scanf("%d", &figures[i].alpha);
    }
    printf("\n===== ФИГУРЫ =====\n");
    print(figures, k);
    printf("===== Квадраты =====\n");
    kvadrat(figures, k);
    printf("===== Прямоугольники =====\n");
    pramoygolnik(figures, k);
}