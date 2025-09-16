#include <cstdio>
#include <cstdint>
#include <cinttypes>
#include <climits>

using namespace std;

int main()
{
    int r, c, m;
    scanf("%d %d %d", &r, &c, &m);
    // printf("%d%d%d\n", r, c, m);
    int64_t cost[2][20000];
    int curr = 0, next = 1;
    for (int i = 0; i < c; ++i)
        cost[curr][i] = 0;
    int64_t start = 1;
    for (int iter = 0; iter < r; ++iter) {
        int64_t cell_val = start;
        for (int i = 0; i < c; ++i) {
            int64_t sub_min = cost[curr][i];
            if (i - 1 >= 0 && cost[curr][i - 1] < sub_min)
                sub_min = cost[curr][i - 1];
            if (i + 1 <= c - 1 && cost[curr][i + 1] < sub_min)
                sub_min = cost[curr][i + 1];
            cost[next][i] = cell_val + sub_min;
            ++cell_val;
            if (cell_val > m)
                cell_val = 1;
        }
        start = cell_val;
        curr ^= 1;
        next ^= 1;
    }
    int64_t final_min = INT64_MAX;
    for (int i = 0; i < c; ++i) {
        if (final_min > cost[curr][i])
            final_min = cost[curr][i];
    }
    printf("%" PRId64 "\n", final_min);
    return 0;
}
