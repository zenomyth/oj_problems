#include <iostream>

#define MAX_N 1000000
#define MAX_A 100000

using namespace std;

int N, Q, a, l, r, x;
struct occurrence_list {
    int idx;
    struct occurrence_list *next;
} pool[MAX_N];
struct occurrence_list *watermark = pool;
struct occurrence_list *ol[MAX_A + 1];
int val[MAX_A];
int val_len = 0;
int pool_linear[MAX_N + 1];
int watermark_linear = 1;
struct {
    int beg;
    int end;
} ol_linear[MAX_A + 1];

int main()
{
    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        cin >> a;
        watermark->idx = i;
        watermark->next = ol[a];
        if (ol[a] == NULL)
            val[val_len++] = a;
        ol[a] = watermark;
        ++watermark;
    }
    for (int i = 0; i < val_len; ++i) {
        a = val[i];
        struct occurrence_list *p = ol[a];
        ol_linear[a].beg = watermark_linear;
        while (p != NULL) {
            pool_linear[watermark_linear++] = p->idx;
            p = p->next;
        }
        ol_linear[a].end = watermark_linear;
    }
    do {
        cin >> l >> r >> x;
        bool match_found = false;
        for (int f = 1; f * f < x; ++f) {
            int g = x / f;
            if (f * g != x)
                continue;
            for (int i = ol_linear[f].beg; i < ol_linear[f].end; ++i) {
                if (pool_linear[i] >= l && pool_linear[i] <= r) {
                    match_found = true;
                    break;
                }
            }
            if (!match_found)
                continue;
            match_found = false;
            for (int i = ol_linear[g].beg; i < ol_linear[g].end; ++i) {
                if (pool_linear[i] >= l && pool_linear[i] <= r) {
                    match_found = true;
                    break;
                }
            }
            if (match_found)
                break;
        }
        if (match_found)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    } while (--Q > 0);
    return 0;
}
