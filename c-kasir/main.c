#include <stdio.h>
#include <stdbool.h>

// Aku tidak pandai memberi nama ...

int getChoice() {
    int choice = 0;

    printf("========================\n");
    printf("       Buah-buahan      \n");
    printf("1. Apel (50000/kg)\n");
    printf("2. Tomat (10000/kg)\n");
    printf("3. Wortel (12000/kg)\n");
    printf("4. Cabai (75000/kg)\n");
    printf("------------------------\n");

    printf("\n");
    do {
        // Referensi: ANSI code
        printf("\033[A");
        printf("Nomor buah: ");
        printf("    \b\b\b\b");
        scanf("%d", &choice);
    } while (choice > 4 || choice <= 0);

    return choice;
}

int getQty() {
    int qty = 0;

    printf("\n");
    do {
        printf("\033[A");
        printf("Berat (kg): ");
        printf("    \b\b\b\b");
        scanf("%d", &qty);
    } while (qty <= 0);

    return qty;
}

bool confirmCheckout() {
    bool checkout = true;
    int choice = 0;

    printf("\n========================\n");
    printf("Pesanan tercatat.\n");
    printf("Lanjut belanja?\n");
    printf("1. Ya\n");
    printf("Lainnya: Tidak\n");
    printf("------------------------\n");
    printf("Pilihan: ");
    scanf("%d", &choice);
    printf("========================\n\n");

    if (choice == 1) checkout = false;
    return checkout;
}

int main() {
    int choices[4] = { 0, 0, 0, 0 };
    bool checkout = false;

    while (checkout != true) {
        int choice = getChoice();
        int qty = getQty();
        printf("========================\n");

        choices[--choice] = qty;
        checkout = confirmCheckout();
    }

    int totalPrice;

    printf("========================\n");
    for (int i = 0; i < 4; i++) {
        if (choices[i] < 1) continue;

        int itemPrice;

        switch (i) {
            case 0:
                printf("Apel  ");
                itemPrice = 50000;
                break;
            case 1:
                printf("Tomat ");
                itemPrice = 10000;
                break;
            case 2:
                printf("Wortel");
                itemPrice = 12000;
                break;
            default:
                printf("Cabai ");
                itemPrice = 75000;
        }
        printf(" => %dkg\n", choices[i]);
        printf("  %d x %d = %d\n", itemPrice, choices[i], itemPrice * choices[i]);

        totalPrice += itemPrice * choices[i];
    }
    printf("------------------------\n");
    printf("Total harga: %d\n", totalPrice);
    printf("========================\n");

    return 0;
}