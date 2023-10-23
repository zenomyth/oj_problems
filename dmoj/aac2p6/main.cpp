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
int tp[N + 1];

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
    // for (int i = 1; i <= n; ++i)
        // printf("%d\n", flat[i]->v);
}

int find_min_time_naive()
{
    int t = 2147483647;
    for (int i = 1; i <= n; ++i) {
        if (flat[i]->c != NULL)
            continue;
        int tt = 0;
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
