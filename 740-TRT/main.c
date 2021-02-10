#include <stdio.h>

int main(void)
{
    int N;
    int v[2000];
    int o[2][2001];
    int i;
    int j;
    int k1, k2;

    scanf("%d", &N);
    for (i = 0; i < N; ++i)
        scanf("%d", &v[i]);
    o[0][0] = v[N - 1];
    o[0][1] = v[0];
    k1 = 0;
    k2 = 1;
    for (i = 2; i <= N; ++i) {
        for (j = 0; j <= i; ++j)
            o[k2][j] = 0;
        for (j = 0; j < i; ++j) {
            if (o[k2][j] < o[k1][j] + i * v[N - i + j])
                o[k2][j] = o[k1][j] + i * v[N - i + j];
            if (o[k2][j + 1] < o[k1][j] + i * v[j])
                o[k2][j + 1] = o[k1][j] + i * v[j];
        }
        k1 ^= 1;
        k2 ^= 1;
    }
    for (i = N - 1; i >= 0; --i) {
        if (o[k1][N] < o[k1][i])
            o[k1][N] = o[k1][i];
    }
    printf("%d\n", o[k1][N]);

    return 0;
}
