#include <stdio.h>
#include <stdlib.h>
#define SIZE_STR 100
#define COUNT_USERS 100

typedef struct {
    char name[SIZE_STR];
    char id[SIZE_STR];
    char level[SIZE_STR];
} user;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Programm start: %s <path to file>\n", argv[0]);
        exit(0);
    }
    FILE *file = NULL;
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file %s\n", argv[1]);
        exit(0);
    }

    user users[COUNT_USERS];
    int i = 0;
    char line[SIZE_STR];
    while (fscanf(file, "%[^;];%[^;];%s\n", users[i].name, users[i].id, users[i].level) == 3) {
        i++;
    }

    printf("Имя         ID  Уровень\n");
    for (int j = 0; j < i; j++) {
        printf("%-10s %-s %s\n", users[j].name, users[j].id, users[j].level);
    }

    fclose(file);
}