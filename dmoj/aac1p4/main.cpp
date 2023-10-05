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

int main()
{
    cin >> N >> Q;
    for (int i = 1; i <= N; ++i) {
        cin >> a;
        watermark->idx = i;
        watermark->next = ol[a];
        ol[a] = watermark;
        ++watermark;
    }
    do {
        cin >> l >> r >> x;
        struct occurrence_list *p = NULL;
        for (int f = 1; f * f < x; ++f) {
            int g = x / f;
            if (f * g != x)
                continue;
            p = ol[f];
            while (p != NULL) {
                if (p->idx >= l && p->idx <= r)
                    break;
                p = p->next;
            }
            if (p == NULL)
                continue;
            p = ol[g];
            while (p != NULL) {
                if (p->idx >= l && p->idx <= r)
                    break;
                p = p->next;
            }
            if (p != NULL)
                break;
        }
        if (p == NULL)
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    } while (--Q > 0);
    return 0;
}
