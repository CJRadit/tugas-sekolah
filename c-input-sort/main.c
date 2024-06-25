#include <stdio.h>

#define SORT_ASC 1
#define SORT_DESC 2

#define LENGTH 7

void insert(int *list);
void sort_items(int *list, int *target, int sort_by);

int main()
{
    int _list[LENGTH], *list = _list;

    int confirm = 0;
    char jawaban;

    while (confirm != 1) {
        insert(list);

        while (1)
        {
            printf("Apakah Anda yakin? (Y/n) ");
            scanf("%c%c", &jawaban, &jawaban);
            if (jawaban == 'y' || jawaban == 'Y' || jawaban == '\n')
                confirm = 1;
            if (
                jawaban == 'y' ||
                jawaban == 'Y' ||
                jawaban == 'n' ||
                jawaban == 'N' ||
                jawaban == '\n'
            ) break;
        }
    }

    int _sorted_asc[LENGTH], *sorted_asc = _sorted_asc;
    int _sorted_desc[LENGTH], *sorted_desc = _sorted_desc;
    sort_items(list, sorted_asc, SORT_ASC);
    sort_items(list, sorted_desc, SORT_DESC);

    printf("ASC:  ");
    printf("[");
    for (int j = 0; j < LENGTH; j++)
    {
        printf("%d", sorted_asc[j]);
        if (j != LENGTH - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    printf("DESC: ");
    printf("[");
    for (int j = 0; j < LENGTH; j++)
    {
        printf("%d", sorted_desc[j]);
        if (j != LENGTH - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");

    return 0;
}

void insert(int *list)
{
    for (int i = 0; i < LENGTH; i++)
    {
        printf("Masukkan bilangan: ");
        scanf("%d", &list[i]);
    }

    // You can safely delete this
    printf("[");
    for (int j = 0; j < LENGTH; j++)
    {
        printf("%d", list[j]);
        if (j != LENGTH - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void sort_items(int *list, int *target, int sort_by)
{
    // Check apakah sort_by bukan SORT_ASC atau SORT_DESC
    if (sort_by != SORT_ASC && sort_by != SORT_DESC)
        return;
    // Mempopulasi target dengan list
    for (int i = 0; i < LENGTH; i++)
        target[i] = list[i];

    for (int i = 0; i < LENGTH - 1; i++)
    {
        for (int j = 0; j < LENGTH - i - 1; j++)
        {
            if (sort_by == SORT_ASC && target[j] <= target[j + 1])
                continue;
            else if (sort_by == SORT_DESC && target[j] > target[j + 1])
                continue;

            int tmp = target[j];
            target[j] = target[j + 1];
            target[j + 1] = tmp;
        }
    }
}