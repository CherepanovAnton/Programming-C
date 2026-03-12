#include "FuncLab12.h"


// Функция вывода массива структур
void Output(car afto[], int c) {
    for (int i = 0; i < c; i++) {
        printf("Марка: %s\n", afto[i].mark);
        printf("Год выпуска: %d г.\n", afto[i].release);
        printf("Мощность (л.с.): %d\n", afto[i].power);
        printf("Цена: %d руб.\n", afto[i].price);
        printf("\n");
    }

}

// Функция заполнения массива структур случайными данными
void fill(car afto[], int c) {
    char marks[][100] = { "Audi Q7", "BMW X7", "Mercedes GLS", "Toyota Camry", "Honda Accord" };
    int releases[] = { 2021, 2020, 2022, 2019, 2021 };
    int powers[] = { 252, 340, 330, 150, 192 };
    int prices[] = { 4700000, 7600000, 8200000, 2200000, 2500000 };

    srand(time(NULL));
    for (int i = 0; i < c; i++) {
        int slot = rand() % 5;

        strcpy(afto[i].mark, marks[slot]);
        afto[i].release = releases[slot];
        afto[i].power = powers[slot];
        afto[i].price = prices[slot];
    }

}

// Функция сортировки по цене a < b
int SortPrice(car mashin1, car mashin2) {
    if (mashin1.price < mashin2.price) return 1;
    return 0;
}

// Функция сортировки по алфавиту a < b
int SortAlph(car mashin1, car mashin2) {
    if (mashin1.mark[0] < mashin2.mark[0]) return 1;
    return 0;
}

// Функция сортировки по мощности a < b
int SortPower(car mashin1, car mashin2) {
    if (mashin1.power < mashin2.power) return 1;
    return 0;
}

// Функция сортировки по релизу a < b
int SortRelease(car mashin1, car mashin2) {
    if (mashin1.release < mashin2.release) return 1;
    return 0;
}


// Функция сортировки методом SelectSort по цене
void SelectSort(car afto[], int c, int (*callback)(car, car)) {
    for (int i = 0; i < (c - 1); i++) {
        int k = i;
        for (int j = (i + 1); j < c; j++) {
            if (callback(afto[j], afto[k])) {
                k = j;
            }
        }
        car swap = afto[i];
        afto[i] = afto[k];
        afto[k] = swap;
    }
}