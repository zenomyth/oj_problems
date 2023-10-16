#include <iostream>
#include <map>

#define N 1000000

using namespace std;

int n, t;
int a[N];
int b[N], c[N];

void preprocess()
{
    map<int, int> last_idx_with_val;
    last_idx_with_val[a[0]] = 0;
    int start = 0, start_last = -1;
    for (int i = 1; i < n; ++i) {
        auto search = last_idx_with_val.find(a[i]);
        if (search != last_idx_with_val.end() && search->second >= start) {
            for (int j = start + 1; j <= search->second; ++j)
                b[j] = start;
            c[start] = i - 1;
            b[start] = start_last;
            start_last = start;
            start = search->second + 1;
        }
        last_idx_with_val[a[i]] = i;
    }
    for (int i = start + 1; i < n; ++i)
        b[i] = start;
    c[start] = n - 1;
    b[start] = start_last;
    // for (int i = 0; i < n; ++i)
        // cout << b[i] << " " << c[i] << endl;
}

int find_max_length(int l, int r)
{
    int ans = r - l + 1;
    int start;
    if (c[l] == 0)
        start = b[l];
    else
        start = l;
    while (start != -1 && c[start] >= r) {
        if (c[start] - start + 1 > ans)
            ans = c[start] - start + 1;
        start = b[start];
    }
    return ans;
}

int main()
{
    cin >> n >> t;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    preprocess();
    int ans = 0;
    for (int i = 0; i < t; ++i) {
        int p, q;
        cin >> p >> q;
        ans = find_max_length((p ^ ans) - 1, (q ^ ans) - 1);
        cout << ans << endl;
    }
    return 0;
}
