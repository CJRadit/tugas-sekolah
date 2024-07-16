#include <stdio.h>

typedef struct List
{
    int angka[15];
    int sum;
    float mean;
    int asc[15];
    int desc[15];
    int min;
    int max;
} List;

void input(List *list)
{
    for (int i = 0; i < 15; i++)
    {
        printf("Input angka ke-%d: ", i + 1);
        scanf("%d", &list->angka[i]);
        list->asc[i] = list->angka[i];
        list->desc[i] = list->angka[i];
    }    
}

void sort(List *list)
{
    for (int i = 0; i < 15 - 1; i++)
    {
        for (int j = 0; j < 15 - 1 - i; j++)
        {
            // Ascending
            if (list->asc[j] > list->asc[j + 1])
            {
                int tmp = list->asc[j];
                list->asc[j] = list->asc[j + 1];
                list->asc[j + 1] = tmp;
            }
            // Descending
            if (list->desc[j] < list->desc[j + 1])
            {
                int tmp = list->desc[j];
                list->desc[j] = list->desc[j + 1];
                list->desc[j + 1] = tmp;
            }
        }
    }
}

void other_stuff(List *list)
{
    // int min = list->angka[0];
    // int max = list->angka[0];
    list->sum = 0;
    for (int i = 0; i < 15; i++)
    {
        // if (list->angka[i] < min)
        //     min = list->angka[i];
        // if (list->angka[i] > max)
        //     max = list->angka[i];
        list->sum += list->angka[i];
    }
    list->mean = (float)list->sum / 15.f;
    list->min = list->asc[0];
    list->max = list->desc[0];
}

int main()
{
    List *list, _list;
    list = &_list;
    input(list);
    sort(list);
    other_stuff(list);

    // Print stuff
    printf("\nAngka:");
    for (int i = 0; i < 15; i++)
    {
        printf(" %d", list->angka[i]);
    }

    printf("\nSum: %d", list->sum);
    
    printf("\nMean: %2f", list->mean);
    
    printf("\nAsc:");
    for (int i = 0; i < 15; i++)
    {
        printf(" %d", list->asc[i]);
    }

    printf("\nDesc:");
    for (int i = 0; i < 15; i++)
    {
        printf(" %d", list->desc[i]);
    }
    
    printf("\nMin: %d", list->min);
    
    printf("\nMax: %d", list->max);
}
