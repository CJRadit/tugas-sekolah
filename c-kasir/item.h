#ifndef ITEM_H
#define ITEM_H

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

bool insert_item(struct ItemData *item_data, struct Item item      );
void delete_item(struct ItemData *item_data,         int item_index);

bool check_item_inventory   (struct ItemData *item_data, int index, int quantity);
bool increase_item_inventory(struct ItemData *item_data, int index, int quantity);
bool decrease_item_inventory(struct ItemData *item_data, int index, int quantity);

#endif /* ITEM_H */