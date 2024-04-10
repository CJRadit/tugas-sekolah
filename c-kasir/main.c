#include <stdio.h>
#include <stdlib.h>

// Aku tidak pandai memberi nama ...

struct Item
{
    char name[32];
    int price;
};

int items_size, items_max_size;
struct Item *items;

void insert_item(struct Item item)
{
    // Menurut orang di internet, mengubah alokasi memori setiap kali
    // array diubah akan tidak baik untuk performa, karena harus dijalankan
    // setiap kali.
    // Hence we double it! ;)
    if (items_size >= items_max_size)
    {
        items_max_size *= 2;
        items = (struct Item *)realloc(items, items_max_size * sizeof(struct Item));
    }

    if (items != NULL)
    {
        items[items_size] = item;
        items_size++;
    }
    else
    {
        printf("Alokasi memori untuk items di insert_item() gagal.\n");
        // return 1;
    }
}

void delete_item(int item_index)
{
    // Cek kalau index gk out-of-bounds
    if (item_index >= 0 || item_index < items_max_size)
    {
        // Geser element lain ke kiri ...
        for (int i = item_index; i < items_size - 1; i++)
        {
            items[i] = items[i + 1];
        }
        items_size--;

        if (items_size < (items_max_size / 2))
        {
            items_max_size /= 2;
            items = (struct Item *)realloc(
                items,
                items_max_size * sizeof(struct Item));
        }
    }
}

int show_menu()
{
    int choice = -1;

    printf("========= MENU =========\n");
    printf("1. Kasir\n");
    printf("2. Lihat daftar item\n");
    printf("3. Tambah item\n");
    printf("4. Hapus item\n");
    printf("0. Keluar\n");
    printf("------------------------\n");
    printf("\n");
    while (choice < 0 || choice > 4)
    {
        printf("\033[F");
        printf("Pilih (0-4): ");
        printf("    \b\b\b\b");
        scanf("%d", &choice);
    }
    printf("========================");

    return choice;
}

void show_items()
{
    int number = 0;
    for (int i = 0; i < items_size; i++)
    {
        printf("%d. %s (%d/kg)\n", ++number, items[i].name, items[i].price);
    }
}

void run_cashier()
{
    int *cart;
    cart = (int *)malloc(items_max_size * sizeof(int));
    if (cart == NULL)
    {
        printf("Alokasi memori untuk cart di run_cashier() gagal.\n");
        return;
    }

    int finished = 0;
    do
    {
        int choice = 0;
        int qty = 0;

        printf("========= ITEM =========\n");
        show_items();
        printf("========================\n");
        printf("\033[F"); // Pindah kursor ke line sebelumnya
        printf("0. Keluar               \n");
        printf("------------------------\n\n");
        do
        {
            // Referensi: ANSI code
            printf("\033[A");
            printf("Pilih (0-%d): ", items_size);
            printf("    \b\b\b\b");
            scanf("%d", &choice);
        } while (choice < 0 || choice > items_size);
        if (choice == 0)
        {
            printf("========================\n");
            free(cart);
            return;
        }
        choice--;
        printf("\n");
        do
        {
            printf("\033[A");
            printf("Berat (kg): ");
            printf("    \b\b\b\b");
            scanf("%d", &qty);
        } while (qty <= 0);
        printf("========================\n\n");

        // Tambah ke cart
        cart[choice] = qty;

        int checkout = 0;
        // Ini bukan program untuk production, jadi ...
        label_checkout:
        printf("======= CHECKOUT =======\n");
        printf("Pesanan tercatat.\n");
        printf("1. Lanjut belanja\n");
        printf("2. Lihat keranjang\n");
        printf("3. Ke Pembayaran\n");
        printf("------------------------\n\n");
        do
        {
            printf("\033[A");
            printf("Pilih (0-3): ");
            printf("    \b\b\b\b");
            scanf("%d", &checkout);

        } while (checkout < 1 || checkout > 3);
        printf("========================\n\n");

        if (checkout == 2)
        {
            int number = 0;
            printf("========= CART =========\n");
            for (int i = 0; i < items_max_size; i++)
            {
                if (cart[i] <= 0)
                    continue;
                printf("%d. %s => %dkg\n", ++number, items[i].name, cart[i]);
            }
            printf("========================\n\n");
            goto label_checkout; // Mungkin aku akan buat function terpisah ...
        }
        if (checkout == 3) finished = 1;
    } while (finished != 1);

    // NOTA
    int total_price = 0;
    printf("========= NOTA =========\n");
    for (int i = 0; i < items_max_size; i++)
    {
        if (cart[i] <= 0)
            continue;

        total_price += items[i].price * cart[i];
        printf("%s => %dkg\n", items[i].name, cart[i]);
        printf("> %d x %d = %d\n", items[i].price, cart[i], items[i].price * cart[i]);
    }
    printf("------------------------\n");
    printf("Total: %d\n", total_price);
    printf("========================\n");
    printf("    Terima kasih! :)\n");

    // Simpan ke file
    FILE *file;
    file = fopen("nota.txt", "a+");
    fprintf(file, "========= NOTA =========\n");
    for (int i = 0; i < 4; i++)
    {
        if (cart[i] <= 0)
            continue;
        fprintf(file, "%s => %dkg\n", items[i].name, cart[i]);
        fprintf(file, "> %d x %d = %d\n", items[i].price, cart[i], items[i].price * cart[i]);
    }
    fprintf(file, "------------------------\n");
    fprintf(file, "Total: %d\n", total_price);
    fprintf(file, "========================\n");
    // fprintf(file, "    Terima kasih! :)\n");
    fclose(file);

    free(cart);
}

void show_insert_item() {
    struct Item item;

    printf("====== TAMBAH ITEM =====\n");

    int c;
    printf("Nama: ");
    scanf ("%32s", item.name);
    while ((c = fgetc(stdin)) != '\n' && c != EOF); // Ini perlu untuk flush input dari scanf

    printf("Harga/kg: ");
    scanf ("%d", &item.price);

    printf("------------------------\n");
    printf("Nama: %s\n", item.name);
    printf("Harga: %d\n", item.price);
    printf("Simpan item?\n");
    printf("1. Ya\n");
    printf("0. Tidak\n");
    printf("------------------------\n\n");
    int save = -1;
    do
    {
        printf("\033[A");
        printf("Pilih (0-1): ");
        printf("    \b\b\b\b");
        scanf("%d", &save);
    } while (save < 0 || save > 1);
    if (save == 1) {
        insert_item(item);
        printf("------------------------\n");
        printf("Item tersimpan!\n");
    }
    printf("========================\n");
}

void show_delete_item() {
    int i = -1;

    printf("====== DELETE ITEM =====\n");
    show_items();
    printf("0. Keluar\n");
    printf("------------------------\n\n");

    do {
        printf("\033[A");
        printf("Pilih (0-%d): ", items_size);
        printf("    \b\b\b\b");
        scanf ("%d", &i);
    } while (i < 0 || i > items_size);
    if (i == 0) {
        printf("========================\n");
        return;
    }
    i--;

    printf("------------------------\n");
    printf("Hapus item %s?\n", items[i].name);
    printf("1. Ya\n");
    printf("0. Tidak\n");
    printf("------------------------\n\n");

    int delete = -1;
    do
    {
        printf("\033[A");
        printf("Pilih (0-1): ");
        printf("    \b\b\b\b");
        scanf("%d", &delete);
    } while (delete < 0 || delete > 1);
    if (i == 0)
    {
        printf("========================\n");
        return;
    }
    delete_item(i);
    printf("------------------------\n");
    printf("Item dihapus!\n");

    printf("========================\n");
}

int main()
{
    items_size = 4;
    items_max_size = 4;
    items = (struct Item *)malloc(items_size * sizeof(struct Item));
    if (items == NULL)
    {
        printf("Alokasi memori untuk items gagal.\n");
        return 1;
    }

    items[0] = (struct Item){.name = "Apel", .price = 50000};
    items[1] = (struct Item){.name = "Tomat", .price = 10000};
    items[2] = (struct Item){.name = "Wortel", .price = 12000};
    items[3] = (struct Item){.name = "Cabai", .price = 75000};

    int menu = -1;
    do
    {
        menu = show_menu();
        if (menu != 0)
            printf("\n\n");

        switch (menu)
        {
        case 1:
            run_cashier();
            break;
        case 2:
            printf("========= ITEM =========\n");
            show_items();
            printf("========================\n");
            break;
        case 3:
            show_insert_item();
            break;
        case 4:
            show_delete_item();
            break;
        }

        printf("\n");
    } while (menu != 0);

    printf("      Sampai jumpa!\n\n");
    free(items);
    return 0;
}