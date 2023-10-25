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
int heavy[N + 1];
int depth[N + 1];
int head[N + 1];
int len_from_head[N + 1];
int pos[N], next_pos = 0;
int fenwick[N];

int calc_weight_and_depth(int v)
{
    int size = 1, hc = 0, hc_size = 0;
    for (struct list_item *c = al[v]; c != NULL; c = c->next) {
        if (c->v == parent[v])
            continue;
        parent[c->v] = v;
        depth[c->v] = depth[v] + 1;
        int size1 = calc_weight_and_depth(c->v);
        if (size1 > hc_size) {
            hc_size = size1;
            hc = c->v;
        }
        size += size1;
    }
    if (2 * hc_size >= size)
        heavy[v] = hc;
    return size;
}

void build_hld(int v, int h)
{
    head[v] = h;
    ++len_from_head[h];
    pos[v] = next_pos++;
    if (heavy[v] != 0)
        build_hld(heavy[v], h);
    for (struct list_item *c = al[v]; c != NULL; c = c->next) {
        if (c->v == parent[v] || c->v == heavy[v])
            continue;
        build_hld(c->v, c->v);
    }
}

void preprocess()
{
    calc_weight_and_depth(1);
    heavy[1] = 0;
    build_hld(1, 1);
    // for (int i = 1; i <= n; ++i)
        // printf("%d: d=%d, h=%d, p=%d, head=%d, pos=%d\n", i, depth[i], heavy[i], parent[i], head[i], pos[i]);
}

void fenwick_add(int v, int val)
{
    int h = head[v];
    while (true) {
        int beg = pos[h];
        int fpos = pos[v] - beg + 1;
        while (fpos > 0) {
            fenwick[beg - 1 + fpos] += val;
            fpos -= fpos & (-fpos);
        }
        if (h == 1)
            break;
        v = parent[h];
        h = head[v];
    }
}

int fenwick_query(int v)
{
    int val = 0;
    int h = head[v];
    int beg = pos[h];
    int fpos = pos[v] - beg + 1;
    while (fpos <= len_from_head[h]) {
        val += fenwick[beg - 1 + fpos];
        fpos += fpos & (-fpos);
    }
    // printf("query(%d)=%d\n", v, val);
    return val;
}

long long query_min_time()
{
    long long t = 0, ts = 0;
    for (int i = 0; i < x; ++i) {
        t += (long long)depth[xa[i]];
        fenwick_add(xa[i], 1);
    }
    // for (int i = 0; i < n; ++i)
        // printf("f[%d]=%d\n", i, fenwick[i]);
    for (int i = 0; i < x; ++i) {
        long long ts1 = 0;
        for (int v = xa[i]; v != 1; v = parent[v])
            ts1 += (long long)fenwick_query(v);
        if (ts1 > ts)
            ts = ts1;
    }
    // printf("%lld %lld\n", t, ts);
    for (int i = 0; i < x; ++i)
        fenwick_add(xa[i], -1);
    return t - ts;
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
        printf("%lld\n", query_min_time());
    }
    return 0;
}
