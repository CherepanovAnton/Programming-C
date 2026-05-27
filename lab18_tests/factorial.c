#include "factorial.h"

int safe_factorial(int n) {
    if (n < 0) return -1; 
    if (n > 12) return 0; 
    
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}