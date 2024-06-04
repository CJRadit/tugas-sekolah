#include <stdio.h>

void bubble_sort(int *numbers, int length) {
    int is_swapped = 0;
    for (int i = 0; i < length - 1; i++) {
        if (numbers[i] <= numbers[i + 1])
            continue;
        int tmp = numbers[i];
        numbers[i] = numbers[i + 1];
        numbers[i + 1] = tmp;
        is_swapped = 1;
    }
    if (is_swapped = 1)
        bubble_sort(numbers, length);
    // for (int i = 0; i < length - 1; i++) {
    //     if (numbers[i] <= numbers[i + 1])
    //         continue;
    //     bubble_sort(numbers, length);
    //     return;
    // }
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

    return 0;
}