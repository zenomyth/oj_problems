#include <stdio.h>
#include <string.h>

#define N 10000
// #define M 20000

// int edges[M][2];
int connected_node[N + 1];

int main(void)
{
    int c_nodes;
    int c_edges;
    int node1;
    int node2;
    int base1;
    int base2;
    int c_connected_areas;
    int i;
    if (scanf("%d %d", &c_nodes, &c_edges) != 2)
        return 1;
    // printf("%d %d\n", c_nodes, c_edges);
    memset(&connected_node[1], 0, c_nodes);
    c_connected_areas = c_nodes;
    for (i = 0; i < c_edges; ++i) {
        // if (scanf("%d %d", &edges[i][0], &edges[i][1]) != 2)
            // return 1;
        // printf("%d %d\n", edges[i][0], edges[i][1]);
        if (scanf("%d %d", &node1, &node2) != 2)
            return 1;
        if (connected_node[node1] == 0 && connected_node[node2] == 0) {
            if (node1 < node2)
                connected_node[node1] = connected_node[node2] = node1;
            else
                connected_node[node1] = connected_node[node2] = node2;
            --c_connected_areas;
        }
        else if (connected_node[node1] == 0) {
            connected_node[node1] = connected_node[node2];
            --c_connected_areas;
        }
        else if (connected_node[node2] == 0) {
            connected_node[node2] = connected_node[node1];
            --c_connected_areas;
        }
        else {
            do {
                base1 = connected_node[node1];
            } while (base1 != connected_node[base1]);
            do {
                base2 = connected_node[node2];
            } while (base2 != connected_node[base2]);
            if (base1 != base2) {
                if (base1 < base2)
                    connected_node[base2] = base1;
                else
                    connected_node[base1] = base2;
                --c_connected_areas;
            }
        }
    }
    if (c_nodes == c_edges + 1 && c_connected_areas == 1)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
