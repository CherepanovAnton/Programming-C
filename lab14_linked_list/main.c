#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Структура комнаты
typedef struct {
    char name[50];
    int level;
    int number;
    int resolution;
} room;

// Структура узла
typedef struct node {
    room data;
    struct node *next;
} node;

// Функция создания узла
node *newNode() {

    // Генерация случайного уровня
    int event = rand() % 10;
    char *event_name[] = {"Красная", "Синяя", "Зеленая", "Золотая", "Серебряная", "Темная", "Светлая", "Ледяная", "Огненная", "Лабиринт"};
    int event_level[] = {3, 5, 2, 8, 4, 7, 1, 6, 9, 5};
    int event_number[] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
    int event_resolution[] = {25, 40, 30, 50, 35, 45, 20, 60, 55, 38};

    // Создание узла
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Ошибка выделения malloc\n");
        exit(1);
    }

    strcpy(new_node->data.name, event_name[event]);
    new_node->data.level = event_level[event];
    new_node->data.number = event_number[event];
    new_node->data.resolution = event_resolution[event];
    new_node->next = NULL;

    return new_node;
}


// Функция добавления узла в конец списка
node *appendBack(node *head) {

    node *new_node = newNode();

    // Обработка пустого списка
    if (head == NULL) {
        return new_node;
    } 

    node *cur = head; // Создание указателя cur, чтобы не потерять адрес начала списка
    
    // Процесс вставки
    while (cur->next != NULL) {
            cur = cur->next;
    }
    cur->next = new_node;

    return head; 
}

// Вывод односвязного списка
void printList(node *head) {

    node *cur = head; // Создание указателя cur, чтобы не потерять адрес начала списка
    if (cur != NULL) {
        printf("+--------------------------+\n");
        while (cur) {
            printf("    Комната %d - %s \n",  cur->data.number, cur->data.name);
            printf("    Площадь %d м^2 \n", cur->data.resolution);
            printf("    Сложность %d \n", cur->data.level);
            printf("+--------------------------+\n");
            cur = cur->next;
        }
    }
}

// Функция освобождения памяти после malloc
void freeList(node *head) {
    node *cur = head; // Создание указателя cur, чтобы не потерять адрес начала списка
    while (cur != NULL) {
        node *temp = cur; // temp - текущий узел
        cur = cur->next;
        free(temp);
    }
}

int main() {
    srand(time(NULL));
    
    // Ввод кол-ва комнат
    int n;
    printf("Введите кол-во комнат N = ");
    scanf("%d", &n);

    // Заполнения списка
    node *head = NULL;
    for (int i = 0; i < n; i++) {
        head = appendBack(head);
    }

    printList(head);
    
    freeList(head);

}