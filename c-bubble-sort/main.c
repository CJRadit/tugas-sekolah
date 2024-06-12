#include <stdio.h>

void bubble_sort(int *numbers, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (numbers[j] <= numbers[j + 1])
                continue;
            int tmp = numbers[j];
            numbers[j] = numbers[j + 1];
            numbers[j + 1] = tmp;
        }
    }
}

int main() {
    // Gk harus keep nomor awal sih sebenarnya ...
    int numbers[] = {5, 2, 1, 4, 8};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int *sorted = numbers;

    bubble_sort(sorted, length);

    for (int i = 0; i < length; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    return 0;
}