#include <stdio.h>
#include <string.h>

#define N 10000
// #define M 20000

// int edges[M][2];
int reached[N + 1];

int main(void)
{
    int c_nodes;
    int c_edges;
    int node1;
    int node2;
    int c_reached_nodes;
    int i;
    if (scanf("%d %d", &c_nodes, &c_edges) != 2)
        return 1;
    // printf("%d %d\n", c_nodes, c_edges);
    memset(&reached[1], 0, c_nodes);
    c_reached_nodes = 0;
    for (i = 0; i < c_edges; ++i) {
        // if (scanf("%d %d", &edges[i][0], &edges[i][1]) != 2)
            // return 1;
        // printf("%d %d\n", edges[i][0], edges[i][1]);
        if (scanf("%d %d", &node1, &node2) != 2)
            return 1;
        if (reached[node1] == 0) {
            ++c_reached_nodes;
            reached[node1] = 1;
        }
        if (reached[node2] == 0) {
            ++c_reached_nodes;
            reached[node2] = 1;
        }
    }
    if (c_nodes == c_edges + 1 && (c_nodes == 1 || c_reached_nodes == c_nodes))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
