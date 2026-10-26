/*
Вариант 25
Создайте структуру Параллелограмм с элементами a, b – стороны
параллелограмма и a - угол между сторонами. Для К заданных фигур
определить k1 – количество квадратов и k2 – количество прямоугольников.
*/

#include "file.h"

int main() {
    int k;
    printf("Введите кол-во фигур ");
    scanf("%d", &k);
    parallelogram *figures[k];
    for (int i = 0; i < k; i++) {
        figures[i] = malloc(sizeof(parallelogram));
    }

    for (int i = 0; i < k; i++) {
        printf("Введите размер стороны a: ");
        scanf("%d", &(figures[i]->a));
        printf("Введите размер стороны b: ");
        scanf("%d", &(figures[i]->b));
        printf("Введите размер угла alpha: ");
        scanf("%d", &(figures[i]->alpha));
    }
    printf("\n===== ФИГУРЫ =====\n");
    print(figures, k);
    printf("===== Квадраты =====\n");
    kvadrat(figures, k);
    printf("===== Прямоугольники =====\n");
    pramoygolnik(figures, k);

    for (int i = 0; i < k; i++) {
        free(figures[i]);
    }
}