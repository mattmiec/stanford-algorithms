#include <stdlib.h>
#include <stdio.h>

long long quicksort(int* array, int length);
int partition(int* array, int length, int pivpos);
int pivpos(int* array, int length);

const char* filename = "QuickSort.txt";

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

    // read input list
    file = fopen(filename,"r");
    int* numbers = malloc(lines*sizeof(int));
    for (int i = 0; i < lines; ++i)
    {
        fscanf(file, "%d", numbers + i);
    }
    fclose(file);

    // sort and track comparisons
    long long comparisons = quicksort(numbers,lines);

    // print sorted list
    for (int i = 0; i < lines; ++i)
    {
        printf("%d\n",numbers[i]);
    }

    // print comparisons
    printf("# of comparisons is %lld\n",comparisons);

    return 0;
}

long long quicksort(int* array, int length)
{
    // base case
    if (length == 0)
    {
        return 0;
    }
    if (length == 1)
    {
        return 0;
    }


    int p = pivpos(array, length);
    int finalpivpos = partition(array, length, p);

    long long comparisons = length - 1;

    // recurse on part before index p
    comparisons += quicksort(array, finalpivpos);
    // recurse on part after index p
    comparisons += quicksort(array + finalpivpos + 1, length - finalpivpos - 1);

    return comparisons;
}

int partition(int* array, int length, int pivpos)
{
    // temporary variable for swapping
    int tmp;
    int pivot = array[pivpos];

    // put pivot in position 0
    tmp = array[0];
    array[0] = pivot;
    array[pivpos] = tmp;

    // compare elements 1 through length - 1
    int d = 1; // marks beginning of right partition
    for (int i = 1; i<length; ++i) // i is next element to be partitioned
    {
        if (array[i] < array[0])
        {
            tmp = array[d];
            array[d] = array[i];
            array[i] = tmp;
            d++;
        }
    }

    // move pivot to correct position
    tmp = array[d-1];
    array[d-1] = pivot;
    array[0] = tmp;

    // return correct pivot position
    return d-1;
}

int pivpos(int* array, int length)
{
    return length-1;
}
