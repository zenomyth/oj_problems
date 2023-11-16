#include <cstdio>
#include <algorithm>

#define N 1000000

using namespace std;

int r, c, n, m;
int a[N], b[N];
int ta[N], tb[N];
int v[N];

int main()
{
    scanf("%d %d %d %d", &r, &c, &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; ++i)
        scanf("%d", &b[i]);
    int *p1, *p2;
    int n1, n2;
    int *t1, *t2;
    int diff, t;
    if (r < c) {
        p1 = b;
        p2 = a;
        n1 = m;
        n2 = n;
        t1 = tb;
        t2 = ta;
        diff = c - r;
        t = c + 1;
    }
    else {
        p1 = a;
        p2 = b;
        n1 = n;
        n2 = m;
        t1 = ta;
        t2 = tb;
        diff = r - c;
        t = r + 1;
    }
    v[0] = 1;
    for (int i = 1; i < n2; ++i) {
        if (p2[i] == p2[i - 1] + 1)
            v[i] = v[i - 1] + 1;
        else
            v[i] = 1;
    }
    int idx1 = 0, idx2 = 0;
    bool added_total_time = false;
    while (idx1 < n1 && idx2 < n2) {
        if (p1[idx1] == p2[idx2]) {
            if (v[idx2] <= diff) {
                t1[idx1] += v[idx2];
                ++idx1;
                ++idx2;
            }
            else {
                added_total_time = true;
                break;
            }
        }
        else if (p1[idx1] < p2[idx2])
            ++idx1;
        else
            ++idx2;
    }
    if (added_total_time) {
        ++t;
        /* Have to reassign parity from the beginning */
        for (int i = 0; i < n1; ++i)
            t1[i] = p1[i] & 1;
        for (int i = 0; i < n2; ++i)
            t2[i] = (p2[i] & 1) ^ 1;
    }
    printf("%d\n", t);
    for (int i = 0; i < n; ++i)
        printf("%d%c", ta[i], i == n - 1 ? '\n' : ' ');
    for (int i = 0; i < m; ++i)
        printf("%d%c", tb[i], i == m - 1 ? '\n' : ' ');

    return 0;
}
