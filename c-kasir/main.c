#include <stdio.h>
#include <stdbool.h>

// Aku tidak pandai memberi nama ...

bool isDuplicate(int choice, int choices[]) {
    for (int i = 0; i < 4; i++) {
        if (choices[i] == choice) return true;
    }
    return false;
}

int getChoice(int selectedChoices[]) {
    int choice = 0;

    printf("========================\n");
    printf("       Buah-buahan      \n");
    printf("1. Apel (50000/kg)\n");
    printf("2. Tomat (10000/kg)\n");
    printf("3. Wortel (12000/kg)\n");
    printf("4. Cabai (75000/kg)\n");
    printf("========================\n");

    bool duped = false;
    while (
        choice > 4 ||
        choice <= 0 ||
        duped == false
    ) {
        printf("Nomor buah: ");
        scanf("%d", &choice);
        if (choice > 4 || choice <= 0) {
            // printf("Pilihan invalid.\n");
            continue;
        }
        duped = isDuplicate(choice, selectedChoices);
        if (duped == true) {
            printf("Pilihan duplikat.\n")
        }
    }
    return choice;
}