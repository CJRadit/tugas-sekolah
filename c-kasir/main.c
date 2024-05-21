#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

// Kenapa I/O Windows berbeda ...
// Dan aku tahu aku bisa pakai 1 dan 0 daripada true dan false
// Tapi aku cuma butuh 2^1 untuk beberapa tempat

struct User
{
    char username[32];
    char password[256];
    int is_admin;
};

struct Item
{
    char name[32];
    int price;
    int inventory;
};

int users_size, users_max_size;
struct User *users;
int current_user_index;

int items_size, items_max_size;
struct Item *items;

bool show_login()
{
    struct User user;
    int c = 0;

    printf("========= LOGIN ========\n");
    printf("Username: ");
    scanf ("%32s", user.username);
    while ((c = fgetc(stdin)) != '\n' && c != EOF);
    c = 0;
    printf("Password: ");
    scanf ("%256s", user.password);
    while ((c = fgetc(stdin)) != '\n' && c != EOF);

    printf("========================");
    for (int i = 0; i < users_size; i++)
    {
        if (strcmp(users[i].username, user.username) != 0) // strcmp() return 0 if true?
            continue;
        if (strcmp(users[i].password, user.password) != 0)
            continue;
        current_user_index = i;
        printf("\n\n");
        return true;
    }
    return false;
}

bool insert_item(struct Item item)
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

    if (items == NULL)
    {
        printf("Alokasi memori untuk items di insert_item() gagal.\n");
        return false;
    }

    items[items_size] = item;
    items_size++;
    return true;
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

bool check_item_inventory(int item_index, int qty)
{
    if (item_index < 0 || item_index >= items_max_size)
        return false;

    if (items[item_index].inventory < qty)
        return false;

    return true;
}

bool increase_item_inventory(int item_index, int qty)
{
    if (item_index < 0 || item_index >= items_max_size)
        return false;

    items[item_index].inventory += qty;
    return true;
}

bool decrease_item_inventory(int item_index, int qty)
{
    if (item_index < 0 || item_index >= items_max_size)
        return false;

    if (items[item_index].inventory < qty)
        return false;

    items[item_index].inventory -= qty;
    return true;
}

int show_menu()
{
    int choice = -1;
    int max_menu = 2;
    if (users[current_user_index].is_admin == 1)
        max_menu = 4;

    printf("========= MENU =========\n");
    printf("1. Kasir\n");
    printf("2. Lihat daftar item\n");
    if (users[current_user_index].is_admin == 1)
    {
        printf("3. Tambah item\n");
        printf("4. Hapus item\n");
    }
    printf("0. Keluar\n");
    printf("------------------------\n");
    printf("\n");
    while (choice < 0 || choice > max_menu)
    {
        printf("\033[F");
        printf("Pilih (0-%d): ", max_menu);
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
        printf("%d. %s (%'d/kg) (%'dkg)\n", ++number, items[i].name, items[i].price, items[i].inventory);
    }
}

void run_cashier()
{
    // Metode cart saat ini butuh banyak memori jika punya banyak item di items
    int *cart;
    cart = (int *)malloc(items_max_size * sizeof(int));
    if (cart == NULL)
    {
        printf("Alokasi memori untuk cart di run_cashier() gagal.\n");
        return;
    }
    // Why, Windows? Why?
    for (int i = 0; i < items_max_size; i++)
        cart[i] = 0;

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
            printf("Pilih (0-%'d): ", items_size);
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

            if (check_item_inventory(choice, qty) == false)
            {
                printf("\033[A");
                printf("Berat (%'dkg) melebihi kuantitas item (%'dkg).\n\n", qty, items[choice].inventory);
                qty = 0;
            }
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
            printf("Pilih (1-3): ");
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
                printf("%d. %s => %'dkg\n", ++number, items[i].name, cart[i]);
            }
            printf("========================\n\n");
            goto label_checkout; // Mungkin aku akan buat function terpisah ...
        }
        if (checkout == 3) finished = 1;
    } while (finished != 1);

    // Kurangi

    int total_price = 0;
    for (int i = 0; i < items_max_size; i++)
    {
        if (cart[i] <= 0)
            continue;
        total_price += items[i].price * cart[i];
    }

    char use_discount;
    int final_price = total_price,
        received_money = 0,
        exchanged_money = 0;

    // Pembayaran
    int discount = 0;
    printf("====== PEMBAYARAN ======\n");
    printf("Harga: %'d\n", total_price);
    printf("------------------------\n");
    while (1)
    {
        printf("Tambah diskon? (Y/n): ");
        scanf (" %c", &use_discount);
        if (
            use_discount == 'Y' ||
            use_discount == 'y' ||
            use_discount == 'N' ||
            use_discount == 'n'
            // use_discount == 0x0A // ini Enter
        ) break;
    }
    if (
        use_discount == 'Y' ||
        use_discount == 'y' ||
        use_discount == 0x0A
    )
    {
        while (discount <= 0)
        {
            printf("Diskon: ");
            scanf("%d", &discount);
        }
        if (total_price > discount)
            final_price = total_price - discount;
        else
            final_price = 0;
    }
    printf("------------------------\n");
    printf("Total: %'d\n", final_price);
    printf("------------------------\n");
    if (final_price > 0)
    {
        printf("Bayar: ");
        scanf ("%d", &received_money);
        while(received_money < final_price)
        {
            printf("Uang tidak mencukupi!\n");
            printf("Bayar: ");
            scanf ("%d", &received_money);
        }
        printf("------------------------\n");
    }
    exchanged_money = received_money - final_price;
    printf("Kembali: %'d\n", exchanged_money);
    printf("========================\n\n");

    // NOTA
    printf("========= NOTA =========\n");
    for (int i = 0; i < items_max_size; i++)
    {
        if (cart[i] <= 0)
            continue;
        printf("%s => %'dkg\n", items[i].name, cart[i]);
        printf("> %'d x %'d = %'d\n", items[i].price, cart[i], items[i].price * cart[i]);
    }
    printf("------------------------\n");
    printf("Harga:   %'d\n", total_price);
    printf("Diskon:  %'d\n", discount);
    printf("Total:   %'d\n", final_price);
    printf("------------------------\n");
    printf("Bayar:   %'d\n", received_money);
    printf("Kembali: %'d\n", exchanged_money);
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
        fprintf(file, "%s => %'dkg\n", items[i].name, cart[i]);
        fprintf(file, "> %'d x %'d = %'d\n", items[i].price, cart[i], items[i].price * cart[i]);
    }
    fprintf(file, "------------------------\n");
    fprintf(file, "Harga:   %'d\n", total_price);
    fprintf(file, "Diskon:  %'d\n", discount);
    fprintf(file, "Total:   %'d\n", final_price);
    fprintf(file, "------------------------\n");
    fprintf(file, "Bayar:   %'d\n", received_money);
    fprintf(file, "Kembali: %'d\n", exchanged_money);
    fprintf(file, "========================\n");
    // fprintf(file, "    Terima kasih! :)\n");
    fclose(file);

    free(cart);
}

// Ini bukan aplikasi produksi, jadi aku gk perlu cek admin di sini, atau di atas
void show_insert_item()
{
    struct Item item;

    printf("====== TAMBAH ITEM =====\n");

    int c;
    printf("Nama: ");
    scanf ("%32s", item.name);
    while ((c = fgetc(stdin)) != '\n' && c != EOF); // Ini perlu untuk flush input dari scanf

    printf("Harga (/kg): ");
    scanf ("%d", &item.price);

    printf("Kuantitas (kg): ");
    scanf ("%d", &item.inventory);

    printf("------------------------\n");
    printf("Nama: %s\n", item.name);
    printf("Harga: %'d/kg\n", item.price);
    printf("Kuantitas: %'dkg\n", item.inventory);
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
    if (save == 1 && insert_item(item) == true)
    {
        printf("------------------------\n");
        printf("Item tersimpan!\n");
    }
    printf("========================\n");
}

void show_delete_item()
{
    int i = -1;

    printf("====== DELETE ITEM =====\n");
    show_items();
    printf("0. Keluar\n");
    printf("------------------------\n\n");

    do {
        printf("\033[A");
        printf("Pilih (0-%'d): ", items_size);
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
    setlocale(LC_NUMERIC, "");

    users_size = 2;
    users_max_size = 2;
    users = (struct User *)malloc(users_size * sizeof(struct User));
    if (users == NULL)
    {
        printf("Alokasi memori untuk items gagal.\n");
        return 1;
    }

    users[0] = (struct User){.username = "admin", .password = "admin", .is_admin = 1};
    users[1] = (struct User){.username = "kasir", .password = "12345678", .is_admin = 0};

    int login;
    if ((login = show_login()) != true)
        return 0;

    items_size = 4;
    items_max_size = 4;
    items = (struct Item *)malloc(items_size * sizeof(struct Item));
    if (items == NULL)
    {
        printf("Alokasi memori untuk items gagal.\n");
        return 1;
    }

    items[0] = (struct Item){.name = "Apel", .price = 50000, .inventory = 100};
    items[1] = (struct Item){.name = "Tomat", .price = 10000, .inventory = 100};
    items[2] = (struct Item){.name = "Wortel", .price = 12000, .inventory = 100};
    items[3] = (struct Item){.name = "Cabai", .price = 75000, .inventory = 100};

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