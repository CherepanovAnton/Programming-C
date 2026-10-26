#include "include.h"

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