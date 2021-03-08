#include <stdio.h>

int main(void)
{
    int T;
    int N;
    int P[1000];
    int i;
    int j;
    int k;
    int x;
    int cost[2][1001];
    int idx_cur;
    int idx_next;

    scanf("%d", &T);
    do {
        scanf("%d", &N);
        for (i = 0; i < N; ++i)
            scanf("%d", &P[i]);
        idx_cur = 0;
        idx_next = 1;
        for (i = 0; i <= N; ++i)
            cost[idx_cur][i] = 0;
        for (i = 1; i <= N; ++i) {
            for (j = 0; j < N - i + 1; ++j) {
                for (k = 0, x = 1; k < N; ++k) {
                    if (P[k] < j + 1 || P[k] > j + i)
                        ++x;
                    if (P[k] == j + 1)
                        break;
                }
                cost[idx_next][j] = cost[idx_cur][j + 1] + i * x;
            }
            for (j = i - 1; j < N; ++j) {
                for (k = 0, x = 1; k < N; ++k) {
                    if (P[k] < j - i + 2 || P[k] > j + 1)
                        ++x;
                    if (P[k] == j + 1)
                        break;
                }
                if (cost[idx_next][j - i + 1] > cost[idx_cur][j - i + 1] + i * x)
                    cost[idx_next][j - i + 1] = cost[idx_cur][j - i + 1] + i * x;
            }
            idx_cur ^= 1;
            idx_next ^= 1;
        }
        printf("%d\n", cost[idx_cur][0]);
    } while (--T > 0);

    return 0;
}
