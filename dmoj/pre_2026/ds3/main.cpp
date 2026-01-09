#include <cstdio>
#include <algorithm>

#define N 100000

using namespace std;

int n, m;
int a[N + 1];
struct data {
    int m;
    int g;
    int q;
} st[4 * N];

data make_data(int i)
{
    data ret;
    ret.m = i;
    ret.g = i;
    ret.q = 1;
    return ret;
}

int gcd(int a, int b)
{
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

data combine(data l, data r)
{
    data ret;
    ret.m = min(l.m, r.m);
    ret.g = gcd(l.g, r.g);
    ret.q = 0;
    if (ret.g == l.g)
        ret.q += l.q;
    if (ret.g == r.g)
        ret.q += r.q;
    return ret;
}

void build_segment_tree(int v, int l, int r)
{
    // printf("%d %d %d\n", v, l, r);
    if (l == r) {
        st[v] = make_data(a[l]);
        return;
    }
    int mid = l + (r - l) / 2;
    build_segment_tree(v * 2, l, mid);
    build_segment_tree(v * 2 + 1, mid + 1, r);
    st[v] = combine(st[v * 2], st[v * 2 + 1]);
    // printf("st[%d, %d, %d] = %d, %d, %d\n", v, l, r, st[v].m, st[v].g, st[v].q);
}

void update_segment_tree(int v, int l, int r, int pos, int nv)
{
    if (l == r) {
        st[v] = make_data(nv);
        return;
    }
    int mid = l + (r - l) / 2;
    if (pos <= mid)
        update_segment_tree(v * 2, l, mid, pos, nv);
    else
        update_segment_tree(v * 2 + 1, mid + 1, r, pos, nv);
    st[v] = combine(st[v * 2], st[v * 2 + 1]);
}

data query_segment_tree(int v, int l, int r, int lq, int rq)
{
    if (l == lq && r == rq)
        return st[v];
    int mid = l + (r - l) / 2;
    if (rq <= mid)
        return query_segment_tree(v * 2, l, mid, lq, rq);
    if (lq > mid)
        return query_segment_tree(v * 2 + 1, mid + 1, r, lq, rq);
    return combine(query_segment_tree(v * 2, l, mid, lq, mid), query_segment_tree(v * 2 + 1, mid + 1, r, mid + 1, rq));
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    build_segment_tree(1, 1, n);
    for (int i = 0; i < m; ++i) {
        char op[2];
        scanf("%s", op);
        // printf("%s\n", op);
        if (op[0] == 'C') {
            int x, v;
            scanf("%d %d", &x, &v);
            update_segment_tree(1, 1, n, x, v);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            data ret = query_segment_tree(1, 1, n, l, r);
            switch (op[0]) {
                case 'M':
                    printf("%d\n", ret.m);
                    break;
                case 'G':
                    printf("%d\n", ret.g);
                    break;
                case 'Q':
                    printf("%d\n", ret.q);
                    break;
            }
        }
    }
    return 0;
}
