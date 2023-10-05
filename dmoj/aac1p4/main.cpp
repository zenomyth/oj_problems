#include <iostream>

#define MAX_N 1000000
#define MAX_A 100000

using namespace std;

int N, Q, l, r, x;
int arr[MAX_N + 1];
int val[MAX_A];
int val_len = 0;
struct {
    int beg;
    int len;
} ol[MAX_A + 1];
int pool[MAX_N];

bool find_matching_index(int a)
{
    // for (int i = 0; i < ol[a].len; ++i) {
    for (int i = ol[a].len - 1; i >= 0; --i) {
        if (pool[ol[a].beg + i] >= l && pool[ol[a].beg + i] <= r)
            return true;
    }
    return false;
}

int main()
{
    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        arr[i] = a;
        if (ol[a].len == 0)
            val[val_len++] = a;
        ++ol[a].len;
    }
    for (int i = 0, beg = 0; i < val_len; ++i) {
        int a = val[i];
        ol[a].beg = beg;
        beg += ol[a].len;
        ol[a].len = 0;
    }
    for (int i = 1; i <= N; ++i) {
        int a = arr[i];
        pool[ol[a].beg + ol[a].len++] = i;
    }
    do {
        cin >> l >> r >> x;
        bool match_found = false;
        for (int f = 1; f * f < x; ++f) {
            int g = x / f;
            if (f * g != x)
                continue;
            if (find_matching_index(f) && find_matching_index(g)) {
                match_found = true;
                break;
            }
        }
        if (match_found)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    } while (--Q > 0);
    return 0;
}
