#include <stdlib.h>
#include <stdbool.h>

struct Item
{
  char name[32];
  int price;
  int inventory;
};

struct ItemData
{
  int arr_size;
  int arr_max_size;
  struct Item *items;
};

bool insert_item(struct ItemData d, struct Item item)
{
    // Menurut orang di internet, mengubah alokasi memori setiap kali
    // array diubah akan tidak baik untuk performa, karena harus dijalankan
    // setiap kali.
    // Hence we double it! ;)
    if (d.arr_size >= d.arr_max_size)
    {
      d.arr_max_size *= 2;
      d.items = (struct Item *)realloc(d.items, d.arr_max_size * sizeof(struct Item));
    }

    if (d.items == NULL)
    {
        // printf("Alokasi memori untuk d.items di insert_item() gagal.\n");
        return false;
    }

    d.items[d.arr_size] = item;
    d.arr_size++;
    return true;
}

void delete_item(struct ItemData d, int i)
{
    // Cek kalau index gk out-of-bounds
    if (i >= 0 || i < d.arr_max_size)
    {
        // Geser element lain ke kiri ...
        for (; i < d.arr_size - 1; i++)
        {
            d.items[i] = d.items[i + 1];
        }
        d.arr_size--;

        if (d.arr_size < (d.arr_max_size / 2))
        {
            d.arr_max_size /= 2;
            d.items = (struct Item *)realloc(
                d.items,
                d.arr_max_size * sizeof(struct Item));
        }
    }
}

bool check_item_inventory(struct ItemData d, int i, int qty)
{
    if (i < 0 || i >= d.arr_max_size)
        return false;

    if (d.items[i].inventory < qty)
        return false;

    return true;
}

bool increase_item_inventory(struct ItemData d, int i, int qty)
{
    if (i < 0 || i >= d.arr_max_size)
        return false;

    d.items[i].inventory += qty;
    return true;
}

bool decrease_item_inventory(struct ItemData d, int i, int qty)
{
    if (i < 0 || i >= d.arr_max_size)
        return false;

    if (d.items[i].inventory < qty)
        return false;

    d.items[i].inventory -= qty;
    return true;
}