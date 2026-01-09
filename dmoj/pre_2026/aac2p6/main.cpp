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
long long fenwick1[N];
long long fenwick2[N];

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

template<class T>
void fenwick_add(T *fw, int start, int len, int idx, T val)
{
    T *fw1 = fw + start - 1;
    int idx1 = idx - start + 1;
    while (idx1 <= len) {
        *(fw1 + idx1) += val;
        idx1 += idx1 & -idx1;
    }
}

template<class T>
T fenwick_query(T *fw, int start, int idx)
{
    T val = T(0);
    T *fw1 = fw + start - 1;
    int idx1 = idx - start + 1;
    while (idx1 > 0) {
        val += *(fw1 + idx1);
        idx1 -= idx1 & -idx1;
    }
    return val;
}

template<class T>
void fenwick_add_range(T *fw1, T *fw2, int start, int len, int l, int r, T val)
{
    fenwick_add(fw1, start, len, l, val);
    fenwick_add(fw1, start, len, r + 1, T(-val));
    fenwick_add(fw2, start, len, l, T(val * (l - 1)));
    fenwick_add(fw2, start, len, r + 1, T(-val * r));
}

template<class T>
T fenwick_query_range(T *fw1, T *fw2, int start, int idx)
{
    return fenwick_query(fw1, start, idx) * idx - fenwick_query(fw2, start, idx);
}

void hld_add(int v, long long val)
{
    int h = head[v];
    while (h != 1) {
        fenwick_add_range(fenwick1, fenwick2, pos[h], len_from_head[h], pos[h], pos[v], val);
        v = parent[h];
        h = head[v];
    }
}

long long hld_query(int v)
{
    long long val = 0;
    int h = head[v];
    while (h != 1) {
        val += fenwick_query_range(fenwick1, fenwick2, pos[h], pos[v]);
        v = parent[h];
        h = head[v];
    }
    return val;
}

long long query_min_time()
{
    long long t = 0, ts = 0;
    for (int i = 0; i < x; ++i) {
        t += (long long)depth[xa[i]];
        hld_add(xa[i], 1);
    }
    // for (int i = 0; i < n; ++i)
        // printf("f[%d]=%d\n", i, fenwick[i]);
    for (int i = 0; i < x; ++i) {
        long long ts1 = hld_query(xa[i]);
        if (ts1 > ts)
            ts = ts1;
    }
    // printf("%lld %lld\n", t, ts);
    for (int i = 0; i < x; ++i)
        hld_add(xa[i], -1);
    return t - ts;
}

void fenwick_range_op_test()
{
    long long a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int dim = int(sizeof(a) / sizeof(a[0]));
    long long fa[20], fb[20];
    for (int i = 0; i < dim; ++i)
        fa[i] = fb[i] = 0;
    // for (int i = 0; i < dim; ++i)
        // fenwick_add(fa, 0, dim, i, a[i]);
    for (int i = 0; i < dim; ++i)
        fenwick_add_range(fa, fb, 0, dim, i, i, a[i]);
    fenwick_add_range(fa, fb, 0, dim, 0, 9, (long long)100);
    printf("sum=%lld\n", fenwick_query_range(fa, fb, 0, 9));
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
    // fenwick_range_op_test();
    return 0;
}
