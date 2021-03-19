#include <stdio.h>

#define MAX_INPUT (1000)

int input[MAX_INPUT];
int input_count;

void down_heap(int *root, int index, int heap_size)
{
    int top_index;
    int swap;
    top_index = index;
    if (index * 2 + 1 < heap_size && root[index * 2 + 1] < root[top_index])
        top_index = index * 2 + 1;
    if (index * 2 + 2 < heap_size && root[index * 2 + 2] < root[top_index])
        top_index = index * 2 + 2;
    if (top_index != index) {
        swap = root[top_index];
        root[top_index] = root[index];
        root[index] = swap;
        down_heap(root, top_index, heap_size);
    }
}

void up_heap(int *root, int index)
{
    int top_index;
    int swap;
    if (index <= 0)
        return;
    top_index = (index - 1) / 2;
    if (root[index] < root[top_index]) {
        swap = root[top_index];
        root[top_index] = root[index];
        root[index] = swap;
        up_heap(root, top_index);
    }
}

void build_heap(int *root, int heap_size)
{
    int i;
    for (i = (heap_size - 2) / 2; i >= 0; --i)
        down_heap(root, i, heap_size);
}

int remove_top(int *root, int heap_size)
{
    if (heap_size <= 0)
        return heap_size;
    root[0] = root[heap_size - 1];
    down_heap(root, 0, heap_size - 1);
    return heap_size - 1;
}

int add_to_heap(int *root, int heap_size, int val)
{
    root[heap_size] = val;
    up_heap(root, heap_size);
    return heap_size + 1;
}

int main(void)
{
    int i;

    input_count = 0;
    while (scanf("%d", &input[input_count]) == 1)
        ++input_count;
    printf("input_count=%d\n", input_count);

    /* Build the heap with the first 50 items */
    build_heap(input, input_count / 2);

    /* Pop 10 items here */
    for (i = 0; i < 10; ++i) {
        printf("%d\n", input[0]);
        remove_top(input, input_count / 2 - i);
    }
    printf("====================\n");

    /* Add the rest 50 items to the heap */
    for (i = input_count / 2; i < input_count; ++i)
        add_to_heap(input, i - 10, input[i]);

    /* Pop all items */
    for (i = 0; i < input_count - 10; ++i) {
        printf("%d\n", input[0]);
        remove_top(input, input_count - 10 - i);
    }

    return 0;
}
