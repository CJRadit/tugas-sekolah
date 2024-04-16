#include <stdio.h>

int main() {
    double DATA[10];
    int i, jumlah_data = 0;
    char jawaban;

    for (i = 0; i < jumlah_data; i++) {
        printf("Masukkan nomor: ");
        scanf("%Id", &DATA[i]);

        jumlah_data = i + 1;
        
        if (i == 9) break;

        int c = 0;
        while (c != 1) {
            printf("Ingin lanjut? (Y/n) ");
            jawaban = getchar();
            if (
                jawaban == 'y' ||
                jawaban == 'Y' ||
                jawaban == 'n' ||
                jawaban == 'N' ||
                jawaban == '\n'
            ) c = 1;
            if (jawaban == 'n' || jawaban == 'N') break;
        }
    }
}