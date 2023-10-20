#include <cstdio>

#define N 200000

using namespace std;

int n, q, x, xa[N];
struct list_item {
    int v;
    struct list_item *next;
};
struct list_item *al[N + 1], pool[N * 2], *wm = pool;
int parent[N + 1];
int has_child[N + 1];
int tp[N + 1];

void assign_parent(int r)
{
    struct list_item *p = al[r];
    while (p != NULL) {
        if (p->v != 1 && parent[p->v] == 0) {
            parent[p->v] = r;
            has_child[r] = 1;
            assign_parent(p->v);
        }
        p = p->next;
    }
}

void preprocess()
{
    assign_parent(1);
    // for (int i = 1; i <= n; ++i)
        // printf("%d -> %d\n", i, parent[i]);
}

int find_min_time_naive()
{
    int t = 2147483647;
    for (int i = 1; i <= n; ++i) {
        if (has_child[i])
            continue;
        int tt = 0;
        for (int j = i; j != 1; j = parent[j])
            tp[j] = 1;
        for (int j = 0; j < x; ++j) {
            if (xa[j] == 1)
                continue;
            for (int k = xa[j]; k != 1; k = parent[k]) {
                if (tp[k] == 1)
                    break;
                ++tt;
            }
            if (tt >= t)
                break;
        }
        for (int j = i; j != 1; j = parent[j])
            tp[j] = 0;
        if (tt < t)
            t = tt;
        if (t == 0)
            break;
    }
    return t;
}

int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n - 1; ++i) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        wm->v = v2;
        wm->next = al[v1];
        al[v1] = wm;
        ++wm;
        wm->v = v1;
        wm->next = al[v2];
        al[v2] = wm;
        ++wm;
    }
    preprocess();
    for (int i = 0; i < q; ++i) {
        scanf("%d", &x);
        for (int j = 0; j < x; ++j)
            scanf("%d", &xa[j]);
        printf("%d\n", find_min_time_naive());
    }
    return 0;
}
