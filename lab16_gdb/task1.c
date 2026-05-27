#include <stdio.h>
#include <stdlib.h>

// Segmentation fault (core dumped)
// gdb показал место возникновение ошибки:
//22              printf("%d\n", arr[i]);
// В функции init создается копия int *arr, соответственно, для 
// указателя arr в main не выделяется память

void init(int **arr, int *n) { 
    *arr = malloc(*n * sizeof(int));
    for (long i = 0; i < n; ++i) { 
        (*arr)[i] = i;    
    }
    *n = 5;
}

int main() {
    int *arr = NULL;
    int n = 10;

    init(&arr, &n);
    // n = ?
    for (int i = 0; i < n; ++i) {
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}
