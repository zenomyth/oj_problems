#include <stdio.h>

int main(void)
{
    int T;
    int N;
    int P[1000];
    int i;
    int j;
    int x[1000];
    int x1[1000];
    int x2[1000];
    int cost[2][1000];
    int idx_cur;
    int idx_next;

    scanf("%d", &T);
    do {
        scanf("%d", &N);
        for (i = 0; i < N; ++i)
            scanf("%d", &P[i]);
        idx_cur = 0;
        idx_next = 1;
        for (i = 0; i < N; ++i) {
            cost[idx_cur][i] = 0;
            x[P[i] - 1] = x1[P[i] - 1] = x2[P[i] - 1] = i + 1;
        }
        for (i = 1; i <= N; ++i) {
            for (j = 0; j < N - i + 1; ++j) {
                if (i == 1)
                    cost[idx_next][j] = i * x1[j];
                else
                    cost[idx_next][j] = cost[idx_cur][j + 1] + i * x1[j];
            }
            for (j = 0; j < N - i; ++j) {
                if (x[j + i] < x[j])
                    --x1[j];
            }
            for (j = i - 1; j < N; ++j) {
                if (cost[idx_next][j - i + 1] > cost[idx_cur][j - i + 1] + i * x2[j])
                    cost[idx_next][j - i + 1] = cost[idx_cur][j - i + 1] + i * x2[j];
            }
            for (j = i; j < N; ++j) {
                if (x[j - i] < x[j])
                    --x2[j];
            }
            idx_cur ^= 1;
            idx_next ^= 1;
        }
        printf("%d\n", cost[idx_cur][0]);
    } while (--T > 0);

    return 0;
}
