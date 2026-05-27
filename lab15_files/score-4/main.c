#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE_STR 100
#define COUNT_USERS 100

// Структура сотрудника
typedef struct {
    char name[SIZE_STR];
    char id[SIZE_STR];
    char level[SIZE_STR];
} user;

// Функция поиска по ID
void searchId(char *nameFile, char *id) {

    // Считываем данные с database.dat
    FILE *f = fopen(nameFile, "rb");
    user buf[COUNT_USERS];
    size_t read = fread(buf, sizeof(user), COUNT_USERS, f);
    if (read != COUNT_USERS) {
        printf("Error reading file %s\n", nameFile);
        abort();
    }

    // Линейный поиск сотрудника по ID
    bool flag = false;
    for (int i = 0; i < COUNT_USERS; i++) {
        if (strcmp(buf[i].id, id) == 0) {
            printf("%s %s %s\n", buf[i].name, buf[i].id, buf[i].level);
            flag = true;
            break;
        }
    }
    if (!flag) {
        printf("Сотрудник не найден\n");
        abort();
    }

}

int main(int argc, char *argv[]) {

    // Обработка ошибок и открытие текстового файла
    if (argc < 2) {
        printf("Programm start: %s <path to staff.csv> <path to database.dat>\n", argv[0]);
        exit(0);
    }
    FILE *file = NULL;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file %s\n", argv[1]);
        exit(0);
    }

    // Заполнение массива структур
    user users[COUNT_USERS];
    int i = 0;
    char line[SIZE_STR];
    while (fscanf(file, "%[^;];%[^;];%s\n", users[i].name, users[i].id, users[i].level) == 3) {
        i++;
    }
    
    fclose(file);

    // Открытие бинарного файла
    FILE *dataBase = NULL;
    dataBase = fopen(argv[2], "wb");
     if (file == NULL) {
        printf("Error opening file %s\n", argv[2]);
        exit(0);
    }

    // Запись в бинарный файл
    size_t write = fwrite(users, sizeof(user), COUNT_USERS, dataBase);
    if (write != COUNT_USERS) {
        printf("Error writing file %s\n", argv[2]);
    }

    fclose(dataBase);

    // Поиск сотрудника ID
    char keyID[SIZE_STR];
    printf("Input ID: ");
    scanf("%s", keyID);

    searchId(argv[2], keyID);
}