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
};

void input()
{
    
}

int main()
{
    struct List list;

    for (int i = 0; i < 15; i++)
    {
        printf("Input angka ke-%d: ", i + 1);
        scanf("%d", &angka[i]);
        asc[i] = angka[i];
        desc[i] = angka[i];
    }

    for (int i = 0; i < 15 - 1; i++)
    {
        for (int j = 0; j < 15 - 1 - i; j++)
        {
            // Ascending
            if (asc[j] > asc[j + 1])
            {
                int tmp = asc[j];
                asc[j] = asc[j + 1];
                asc[j + 1] = tmp;
            }
            // Descending
            if (desc[j] < desc[j + 1])
            {
                int tmp = desc[j];
                desc[j] = desc[j + 1];
                desc[j + 1] = tmp;
            }
        }
    }

    printf("Asc:");
    for (int i = 0; i < 15; i++)
    {
        printf(" %d", asc[i]);
    }
    printf("\nDesc:");
    for (int i = 0; i < 15; i++)
    {
        printf(" %d", desc[i]);
    }
    int sum = 0;
    for (int i = 0; i < 15; i++)
    {
        sum += angka[i];
    }
    float mean = (float) sum / 15.f;
    printf("\nSum: %d", sum);
    printf("\nMean: %f", mean);
}

