#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long count_inversions_sort(int* int_array, int n);
long long count_split_inversions_merge(int* a, int* b, int* c, int na, int nb);


const char* filename = "IntegerArray.txt";
const int length = 100000;

int main()
{
    FILE* file = fopen(filename,"r");

    // get number of lines in file

    int lines = 0;
    char ch;

    while (!feof(file))
    {
        ch = fgetc(file);
        if(ch == '\n')
        {
            lines++;
        }
    }

    fclose(file);

//    printf("# of lines: %d\n",lines);

    file = fopen(filename,"r");

    int numbers[lines];

    for (int i = 0; i < length; ++i)
    {
        fscanf(file, "%d", numbers + i);
        //printf("%d\n",numbers[i]);
    }

    long long inversions = count_inversions_sort(numbers, length);

    printf("# of inversions: %lli\n", inversions);

//    for (int i = 0; i < length; ++i)
//    {
//        printf("%d\n", numbers[i]);
//    }

    fclose(file);

    return 0;
}

long long count_inversions_sort(int* int_array, int n)
{
    // assume int_array is integer array of length n

    if (n == 0 || n == 1)
    {
        return 0;
    }

    int* a;
    int* b;
    int na = n/2;
    int nb = n - na;

    a = malloc(sizeof(int)*na);
    b = malloc(sizeof(int)*nb);

    memcpy(a, int_array, na*sizeof(int));
    memcpy(b, int_array + na, nb*sizeof(int));

    long long inversions_a = count_inversions_sort(a, na);
    long long inversions_b = count_inversions_sort(b, nb);

    long long inversions_split = count_split_inversions_merge(a, b, int_array, na, nb);

    return inversions_a + inversions_b + inversions_split;

}

long long count_split_inversions_merge(int* a, int* b, int* c, int na, int nb)
{
    // assume a, b are sorted arrays of length na, nb
    // c is output array of length na + nb

    int i = 0; //index a
    int j = 0; //index b

    long long count = 0;

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
            count += (na - i);
        }
    }

    // printf("%d\n",count);
    return count;
}
