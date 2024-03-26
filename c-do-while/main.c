#include <stdio.h>

int main()
{
    int max_number = 7, number = 1;

    do {
        printf("Nomor %d\n", number);
        number++;
    } while (number <= max_number);

    return 0;
}