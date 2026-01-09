#include <iostream>
#include <algorithm>

#define N 4000

using namespace std;

int n;
int a[N];
int m = 0, b[N], c[N];

int find_max_bow()
{
    if (n == 2) {
        if ((a[0] + a[1]) & 1)
            return 1;
        else
            return 2;
    }
    sort(&a[0], &a[n]);
    b[0] = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] == b[m])
            ++c[m];
        else
            b[++m] = a[i];
    }
    int mc = c[0];
    for (int i = 1; i <= m; ++i) {
        if (mc < c[i])
            mc = c[i];
    }
    int mc2 = mc;
    for (int i = 0; i <= m; ++i) {
        if (c[i] + 2 <= mc)
            continue;
        int j1 = i - 1, j2 = i + 1;
        int ct = 0;
        while (j1 >= 0 && j2 <= m) {
            if (b[j1] + b[j2] == b[i] * 2) {
                ct = 2;
                break;
            }
            if (b[j1] + b[j2] > b[i] * 2)
                --j1;
            else
                ++j2;
        }
        if (ct == 0) {
            if (i < m || b[i - 2] + b[i - 1] >= b[i] || (c[i - 1] > 0 && b[i - 1] * 2 >= b[i]))
                ct = 1;
        }
        if (c[i] + ct > mc2)
            mc2 = c[i] + ct;
    }
    return mc2 + 1;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cout << find_max_bow() << endl;
    return 0;
}
