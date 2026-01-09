#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

#define N 500000

using namespace std;

int n, m;
vector<pair<int, int>> a(N, make_pair(0, 0)), b(N, make_pair(0, 0));

int main()
{
    scanf("%d %d", &n, &m);
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        int ai;
        scanf("%d", &ai);
        if (ai != -1) {
            a[pos].first = ai - i;
            a[pos].second = i;
            ++pos;
        }
    }
    n = pos;
    pos = 0;
    for (int i = 0; i < m; ++i) {
        int bi;
        scanf("%d", &bi);
        if (bi != -1) {
            b[pos].first = bi - i;
            b[pos].second = i;
            ++pos;
        }
    }
    m = pos;
    sort(a.begin(), a.begin() + n);
    sort(b.begin(), b.begin() + m);
    int ans = 0;
    for (int i = 0, j = 0; i < n && j < m;) {
        if (a[i].first == b[j].first) {
            ++ans;
            ++i;
            ++j;
        }
        else if (a[i].first < b[j].first)
            ++i;
        else
            ++j;
    }
    printf("%d\n", ans);
    return 0;
}
