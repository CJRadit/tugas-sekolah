#include <stdio.h>
int main()
{
    char tambah_diskon;
    int diskon = 0;
    printf("====== PEMBAYARAN ======\n");
    while (1)
    {
        printf("Tambah diskon? (Y/n): ");
        tambah_diskon = getc(stdin);
        fflush(stdin);
        if (
            tambah_diskon == 'Y' ||
            tambah_diskon == 'y' ||
            tambah_diskon == 'N' ||
            tambah_diskon == 'n' ||
            tambah_diskon == 0x0A // ini Enter
        ) break;
    }
    printf("Akhir [%c]\n", tambah_diskon);
}