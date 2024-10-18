#include <stdio.h>

int main() {
    char V[] = { 10, 4, 2, 5, 23, 8, 9, 2, 19, 5 };
    int terbesar = V[0];

    for (int i = 0; i < 10; i++) {
        if (V[i] > terbesar) {
            terbesar = V[i];
        }
    }

    printf("Terbesar: %d", terbesar);

    return 0;
}