#include <stdio.h>
#include <string.h>
#include "factorial.h"

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    if (strcmp(argv[1], "DefaultUse") == 0) {
        if (safe_factorial(5) != 120) return 1;
        if (safe_factorial(0) != 1) return 1;
        return 0;
    }

    if (strcmp(argv[1], "NegativeDgt") == 0) {
        if (safe_factorial(-5) != -1) return 1;
        return 0;
    }

    if (strcmp(argv[1], "Overflow") == 0) {
        if (safe_factorial(15) != 0) return 1;
        return 0;
    }

    return 1;
}