#include <stdio.h>

int main() {
    char V[] = { 10, 4, 2, 5, 23, 8, 9, 2, 19, 5 };
    int terbesar = V[0];
    int i = 0;

    do
    {
        if (V[i] > terbesar) terbesar = V[i];
        i++;
    } while (i < 10);
    printf("Terbesar: %d", terbesar);

    return 0;
}