#include <cstdio>

using namespace std;

#define N 10000
#define C 50000

int main()
{
    int n, c;
    int e, f, l;
    int fl;
    char fll[5];
    int res[2][32];
    int cr = 0, nx = 1;
    int ce = 0;
    for (int i = 0; i < 32; ++i)
        res[cr][i] = 0;
    scanf("%d %d", &n, &c);
    for (int i = 0; i < c; ++i) {
        scanf("%d %d %d", &e, &f, &l);
        for (int j = 0; j < 5; ++j)
            fll[j] = 'n';
        for (int j = 0; j < f; ++j) {
            scanf("%d", &fl);
            if (fl >= e)
                fll[fl - e] = 'f';
            else
                fll[fl + n - e - 1] = 'f';
        }
        for (int j = 0; j < l; ++j) {
            scanf("%d", &fl);
            if (fl >= e)
                fll[fl - e] = 'l';
            else
                fll[fl + n - e - 1] = 'l';
        }
        int r = e - ce < 5 ? e - ce : 5;
        for (int j = 0; j < (1 << r); ++j) {
            int m = 0;
            for (int k = 0; k < (1 << (5 - r)); ++k) {
                if (res[cr][k | (j << (5 - r))] > m)
                    m = res[cr][k | (j << (5 - r))];
            }
            for (int k = 0; k < (1 << (5 - r)); ++k)
                res[nx][j | (k << r)] = m;
        }
        for (int j = 0; j < 32; ++j) {
            int st = j;
            for (int k = 0; k < 5; ++k) {
                if (st & 1) {
                    if (fll[k] == 'l') {
                        ++res[nx][j];
                        break;
                    }
                }
                else {
                    if (fll[k] == 'f') {
                        ++res[nx][j];
                        break;
                    }
                }
                st >>= 1;
            }
        }
        cr ^= 1;
        nx ^= 1;
    }
    int ans = 0;
    for (int i = 0; i < 32; ++i) {
        if (res[cr][i] > ans)
            ans = res[cr][i];
    }
    printf("%d\n", ans);
    return 0;
}
