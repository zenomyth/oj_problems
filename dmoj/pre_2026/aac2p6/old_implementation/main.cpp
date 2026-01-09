#include <cstdio>

#define N 200000

using namespace std;

int n, q, x, xa[N];
struct list_item {
    int v;
    struct list_item *next;
};
struct list_item *al[N + 1], pool[N * 2], *wm = pool;
struct tree_node {
    int v;
    struct tree_node *p;
    struct tree_node *c;
    struct tree_node *s;
};
struct tree_node *root, pool_tree[N], *wm_tree = pool_tree, *flat[N + 1];

void build_tree(struct tree_node *r)
{
    struct list_item *e = al[r->v];
    while (e != NULL) {
        if (r->p == NULL || e->v != r->p->v) {
            struct tree_node *c = wm_tree++;
            c->v = e->v;
            c->p = r;
            c->c = NULL;
            c->s = r->c;
            r->c = c;
            flat[c->v] = c;
            build_tree(c);
        }
        e = e->next;
    }
}

void preprocess()
{
    root = wm_tree++;
    root->v = 1;
    root->p = NULL;
    root->c = NULL;
    root->s = NULL;
    flat[1] = root;
    build_tree(root);
}

long long find_min_time_naive()
{
    static int tp[N + 1];
    long long t = 2147483647;
    for (int i = 1; i <= n; ++i) {
        if (flat[i]->c != NULL)
            continue;
        long long tt = 0;
        for (struct tree_node *node = flat[i]; node != root; node = node->p)
            tp[node->v] = 1;
        for (int j = 0; j < x; ++j) {
            if (xa[j] == 1)
                continue;
            for (struct tree_node *node = flat[xa[j]]; node != root; node = node->p) {
                if (tp[node->v] == 1)
                    break;
                ++tt;
            }
            if (tt >= t)
                break;
        }
        for (struct tree_node *node = flat[i]; node != root; node = node->p)
            tp[node->v] = 0;
        if (tt < t)
            t = tt;
        if (t == 0)
            break;
    }
    return t;
}

void find_max_time_saved(int *fcnt, struct tree_node *r, long long t_sum, long long *t_saved)
{
    if (r->c == NULL || (r != root && fcnt[r->v] == 0)) {
        if (t_sum > *t_saved)
            *t_saved = t_sum;
        return;
    }
    for (struct tree_node *node = r->c; node != NULL; node = node->s)
        find_max_time_saved(fcnt, node, t_sum + (long long)fcnt[node->v],t_saved);
}

long long find_min_time_dfs()
{
    static int fcnt[N + 1];
    long long t = 0;
    for (int i = 1; i <= n; ++i)
        fcnt[i] = 0;
    for (int i = 0; i < x; ++i) {
        for (struct tree_node *node = flat[xa[i]]; node != root; node = node->p) {
            ++fcnt[node->v];
            ++t;
        }
    }
    long long t_saved = 0;
    find_max_time_saved(fcnt, root, 0, &t_saved);
    return t - t_saved;
}

void fill_in_feed_ground(struct tree_node *r, int *fcnt, long long *t, int level)
{
    if (fcnt[r->v] == 1)
        *t += (long long)level;
    for (struct tree_node *node = r->c; node != NULL; node = node->s) {
        fill_in_feed_ground(node, fcnt, t, level + 1);
        fcnt[r->v] += fcnt[node->v];
    }
}

long long find_min_time_dfs_2()
{
    static int fcnt[N + 1];
    long long t = 0;
    for (int i = 1; i <= n; ++i)
        fcnt[i] = 0;
    for (int i = 0; i < x; ++i)
        fcnt[xa[i]] = 1;
    fill_in_feed_ground(root, fcnt, &t, 0);
    long long t_saved = 0;
    find_max_time_saved(fcnt, root, 0, &t_saved);
    return t - t_saved;
}

long long process__partial_optimal(struct tree_node *r, int *fcnt, long long *t, int level)
{
    long long inc = 0;
    if (fcnt[r->v] == 1)
        *t += (long long)level;
    for (struct tree_node *node = r->c; node != NULL; node = node->s) {
        long long inc1 = process__partial_optimal(node, fcnt, t, level + 1);
        if (inc1 > inc)
            inc = inc1;
        fcnt[r->v] += fcnt[node->v];
    }
    return inc + (long long)fcnt[r->v];
}

long long find_min_time_partial_optimal()
{
    static int fcnt[N + 1];
    for (int i = 1; i <= n; ++i)
        fcnt[i] = 0;
    for (int i = 0; i < x; ++i)
        fcnt[xa[i]] = 1;
    long long t = 0, t_saved = 0;
    t_saved = process__partial_optimal(root, fcnt, &t, 0);
    return t - (t_saved - (long long)x);
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
        // printf("%lld\n", find_min_time_dfs_2());
        printf("%lld\n", find_min_time_partial_optimal());
    }
    return 0;
}
