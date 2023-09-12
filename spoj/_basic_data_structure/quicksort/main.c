#include <stdio.h>

#define MAX_INPUT (1000)

int input[MAX_INPUT];
int input_count;

void swap(int *p1, int *p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

/* Hoare partition scheme with median-of-three pivot selection */
int partition(int *input, int lo, int hi)
{
    int pivot;
    int i, j;
    pivot = input[(lo + hi) / 2];
    if (pivot < input[lo] && pivot < input[hi])
        pivot = input[lo] < input[hi] ? input[lo] : input[hi];
    else if (input[lo] < pivot && input[hi] < pivot)
        pivot = input[lo] < input[hi] ? input[hi] : input[lo];
    i = lo - 1;
    j = hi + 1;
    while (1) {
        do ++i; while (input[i] < pivot);
        do --j; while (pivot < input[j]);
        if (i < j)
            swap(&input[i], &input[j]);
        else
            return j;
    }
}

void quicksort(int *input, int lo, int hi)
{
    int p;
    if (lo < hi) {
        p = partition(input, lo, hi);
        quicksort(input, lo, p);
        quicksort(input, p + 1, hi);
    }
}

int main(void)
{
    int i;

    input_count = 0;
    while (scanf("%d", &input[input_count]) == 1)
        ++input_count;
    printf("input_count=%d\n", input_count);
    quicksort(input, 10, input_count - 11);
    for (i = 0; i < input_count; ++i)
        printf("%d\n", input[i]);

    return 0;
}
