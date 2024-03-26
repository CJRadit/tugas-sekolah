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
        duped == true
    ) {
        printf("Nomor buah: ");
        scanf("%d", &choice);
        if (choice > 4 || choice <= 0) {
            // printf("Pilihan invalid.\n");
            continue;
        }
        duped = isDuplicate(choice, selectedChoices);
        if (duped == true) {
            printf("Pilihan duplikat.\n");
        }
    }
    return choice;
}

int getQty() {
    int qty = 0;
    while (qty <= 0) {
        printf("Jumlah kilogram: ");
        scanf("%d", &qty);
    }
    return qty;
}

int calcPrice(int choice, int qty) {
    int itemPrice;
    switch (choice) {
        case 1:
            itemPrice = 50000;
            break;
        case 2:
            itemPrice = 10000;
            break;
        case 3:
            itemPrice = 12000;
            break;
        default:
            itemPrice = 75000;
    }
    return itemPrice * qty;
}

bool confirmCheckout() {
    bool checkout = true;
    int choice = 0;

    printf("\n========================\n");
    printf("Pesanan tercatat. Apakah Anda ingin tetap berbelanja?\n");
    printf("1. Ya\n");
    printf("Lainnya tidak\n");
    printf("------------------------\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    printf("========================\n\n");

    if (choice == 1) checkout = false;
    return checkout;
}

int main() {
    int choices[4] = { 0, 0, 0, 0 };
    int totalPrice = 0;
    int i = 0;
    bool checkout = false;

    while (checkout != true && i < 4) {
        int choice = getChoice(choices);
        printf("------------------------\n");
        int qty = getQty();
        printf("========================\n");
        totalPrice += calcPrice(choice, qty);
        choices[i] = choice;
        i++;
        checkout = confirmCheckout();
    }

    printf("========================\n");
    printf("Total harga:  %d", totalPrice);
}