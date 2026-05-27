#include <stdio.h>
#include <string.h>

// Проблема: number.num != 1025?
// Выдал gdb
// Breakpoint 2, format (number=0x7fffffffdba0) at task2.c:12
// 12          sprintf(number->str, "%3d", number->num);
// (gdb) p number.num
// $4 = 1025
// (gdb) next
// 13      }
// (gdb) p number.num
// $5 = 1024
// Ошибка происходит из-за того что не учли \0
// Из-за этого стерли 1 байт из number->num

typedef struct {
    char str[5];
    int num;
} NumberRepr;

void format(NumberRepr* number) {
    sprintf(number->str, "%3d", number->num);
}

int main() {
    NumberRepr number = { .num = 1025 };
    format(&number);
    printf("str: %s\n", number.str);
    printf("num: %d\n", number.num);
    return 0;
}
