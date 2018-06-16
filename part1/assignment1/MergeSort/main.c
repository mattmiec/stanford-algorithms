#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge_sort(int* int_array, int n);
void merge(int* a, int* b, int* c, int na, int nb);


const char* filename = "IntegerArray.txt";
const int length = 100000;

int main()
{
    FILE* file = fopen(filename,"r");
    int numbers[length];

    for (int i = 0; i < length; ++i)
    {
        fscanf(file, "%d", numbers + i);
        //printf("%d\n",numbers[i]);
    }

    merge_sort(numbers, length);

    for (int i = 0; i < length; ++i)
    {
        printf("%d\n", numbers[i]);
    }

    return 0;
}

void merge_sort(int* int_array, int n)
{
    // assume int_array is integer array of length n

    if (n == 0 || n == 1)
    {
        return;
    }

    int* a;
    int* b;
    int na = n/2;
    int nb = n - na;

    a = malloc(sizeof(int)*na);
    b = malloc(sizeof(int)*nb);

    memcpy(a, int_array, na*sizeof(int));
    memcpy(b, int_array + na, nb*sizeof(int));

    merge_sort(a, na);
    merge_sort(b, nb);

    merge(a, b, int_array, na, nb);

    return;

}

void merge(int* a, int* b, int* c, int na, int nb)
{
    // assume a, b are sorted arrays of length na, nb
    // c is output array of length na + nb

    int i = 0; //index a
    int j = 0; //index b

    while (i + j < na + nb)
    {
        if (i == na)
        {
            c[i+j] = b[j];
            j++;
        }
        else if (j == nb)
        {
            c[i+j] = a[i];
            i++;
        }
        else if (a[i] <= b[j])
        {
            c[i+j] = a[i];
            i++;
        }
        else
        {
            c[i+j] = b[j];
            j++;
        }
    }

    return;
}
