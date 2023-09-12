#include <stdio.h>
#include <string.h>

struct Node {
    int child[256];
};

struct Node nodes[500000];
int new_node_index;

void count_substr(const char *str)
{
    int i, j;
    int cur_node;
    int count = 0;

    memset(&nodes[0], 0, sizeof(struct Node));
    new_node_index = 1;
    for (i = 0; str[i] != '\0'; ++i) {
        cur_node = 0;
        for (j = i; str[j] != '\0'; ++j) {
            if (nodes[cur_node].child[(unsigned char)str[j]] == 0) {
                memset(&nodes[new_node_index], 0, sizeof(struct Node));
                nodes[cur_node].child[(unsigned char)str[j]] = new_node_index++;
                ++count;
            }
            cur_node = nodes[cur_node].child[(unsigned char)str[j]];
        }
    }
    printf("%d\n", count);
    /*printf("Node used = %d\n", new_node_index);*/
}

int main(void)
{
    int T;
    char str[1024];

    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", str);
        count_substr(str);
    }

    return 0;
}
