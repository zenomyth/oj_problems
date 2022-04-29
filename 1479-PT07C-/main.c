#include <stdio.h>

#define N 200
#define M 20000
#define INF (1 << 29)

struct edge {
    int s;
    int t;
    int w;
};

struct edge e[M];
int a[N][N];
int d[N][N];
int s[N][N];
int t[N][2];
struct edge mdst[N];
int h[N * 2];
int t2[N][3];

void print_matrix(int x[][N], int n)
{
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j)
            printf("%d ", x[i][j]);
        printf("\n");
    }
}

void floyd_warshall(int aa[][N], int dd[][N], int n)
{
    int i, j, k;
    for (i = 0; i < n; ++i)
        for(j = 0; j < n; ++j)
            dd[i][j] = aa[i][j];
    for (k = 0; k < n; ++k)
        for (i = 0; i < n; ++i)
            for(j = 0; j < n; ++j) {
                if (dd[i][j] > dd[i][k] + dd[k][j])
                    dd[i][j] = dd[i][k] + dd[k][j];
            }
}

int less_than(int p1[], int p2[])
{
    if (p2[0] < p1[0]) /* Reverse order */
        return 1;
    return 0;
}

void swap(int p1[], int p2[])
{
    int temp;
    int i;
    for (i = 0; i < 2; ++i) {
        temp = p1[i];
        p1[i] = p2[i];
        p2[i] = temp;
    }
}

/* Hoare partition scheme with median-of-three pivot selection */
int partition(int input[][2], int lo, int hi)
{
    int *pivot;
    int i, j;
    pivot = input[(lo + hi) / 2];
    if (less_than(pivot, input[lo]) && less_than(pivot, input[hi]))
        pivot = less_than(input[lo], input[hi]) ? input[lo] : input[hi];
    else if (less_than(input[lo], pivot) && less_than(input[hi], pivot))
        pivot = less_than(input[lo], input[hi]) ? input[hi] : input[lo];
    i = lo - 1;
    j = hi + 1;
    while (1) {
        do ++i; while (less_than(input[i], pivot));
        do --j; while (less_than(pivot, input[j]));
        if (i < j)
            swap(input[i], input[j]);
        else
            return j;
    }
}

void quicksort(int input[][2], int lo, int hi)
{
    int p;
    if (lo < hi) {
        p = partition(input, lo, hi);
        quicksort(input, lo, p);
        quicksort(input, p + 1, hi);
    }
}

void calculate_farthest_ordering_matrix(int dd[][N], int ss[][N], int n)
{
    int i, j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            t[j][0] = dd[i][j];
            t[j][1] = j;
        }
        quicksort(t, 0, n - 1);
        for (j = 0; j < n; ++j)
            ss[i][j] = t[j][1];
    }
}

void calculate_vertex_one_center(struct edge *ee, int dd[][N], int ss[][N], int n, int m, struct edge *ce, int *offset, int *diameter)
{
    int es, et, ew;
    int x, y;
    int x1, y1;
    int i, j;
    int *v;
    int vp;

    *offset = 0;
    *diameter = INF;
    for (i = 0; i < m; ++i) {
        es = ee[i].s - 1;
        et = ee[i].t - 1;
        ew = ee[i].w;
        if ((dd[et][ss[es][0]] + ew + dd[es][ss[et][0]]) / 2 > *diameter) /* Halpern bound?? */
            continue;
        v = ss[es];
        vp = 0;
        x = 0;
        y = dd[es][v[vp]];
        for (j = 1; j < n; ++j) {
            if (dd[et][v[j]] > dd[et][v[vp]]) { /* Pruning to remove vertices whose distance is smaller to both s and t. */
                x1 = (dd[et][v[vp]] + ew - dd[es][v[j]]) / 2;
                y1 = (dd[et][v[vp]] + ew + dd[es][v[j]]) / 2;
                if (y1 < y) {
                    y = y1;
                    x = x1;
                }
                vp = j;
            }
        }
        if (dd[et][v[vp]] < y) {
            y = dd[et][v[vp]];
            x = ew;
        }
        if (y < *diameter) {
            *diameter = y;
            *offset = x;
            *ce = ee[i];
        }
    }
}

void down_heap(int *root, int index, int heap_size)
{
    int top_index;
    int swap;
    top_index = index;
    if (index * 2 + 1 < heap_size && t2[root[index * 2 + 1]][0] < t2[root[top_index]][0])
        top_index = index * 2 + 1;
    if (index * 2 + 2 < heap_size && t2[root[index * 2 + 2]][0] < t2[root[top_index]][1])
        top_index = index * 2 + 2;
    if (top_index != index) {
        t2[root[top_index]][1] = index;
        t2[root[index]][1] = top_index;
        swap = root[top_index];
        root[top_index] = root[index];
        root[index] = swap;
        down_heap(root, top_index, heap_size);
    }
}

void up_heap(int *root, int index)
{
    int top_index;
    int swap;
    if (index <= 0)
        return;
    top_index = (index - 1) / 2;
    if (t2[root[index]][0] < t2[root[top_index]][0]) {
        t2[root[top_index]][1] = index;
        t2[root[index]][1] = top_index;
        swap = root[top_index];
        root[top_index] = root[index];
        root[index] = swap;
        up_heap(root, top_index);
    }
}

int add_to_heap(int *root, int heap_size, int v, int val, int from)
{
    root[heap_size] = v;
    t2[v][0] = val;
    t2[v][1] = heap_size;
    t2[v][2] = from;
    up_heap(root, heap_size);
    return heap_size + 1;
}

int remove_top(int *root, int heap_size)
{
    if (heap_size <= 0)
        return heap_size;
    root[0] = root[heap_size - 1];
    t2[root[0]][1] = 0;
    down_heap(root, 0, heap_size - 1);
    return heap_size - 1;
}

/* Build minimum diameter spanning tree using Dijkstra’s algorithm */
void build_mdst(int es, int et, int ew, int offset, int n, int aa[][N], struct edge *st, int *output_count)
{
    int h_size = 0;
    int top_v;
    int i;
    *output_count = 0;
    for (i = 0; i < n; ++i)
        t2[i][0] = INF;
    if (offset == 0)
        h_size = add_to_heap(h, h_size, es, 0, -1);
    else if (offset == ew)
        h_size = add_to_heap(h, h_size, et, 0, -1);
    else {
        h_size = add_to_heap(h, h_size, es, offset, -1);
        h_size = add_to_heap(h, h_size, et, ew - offset, -1);
        st[*output_count].s = es;
        st[*output_count].t = et;
        *output_count += 1;
    }
    while (h_size > 0) {
        top_v = h[0];
        h_size = remove_top(h, h_size);
        if (t2[top_v][2] != -1) {
            st[*output_count].s = t2[top_v][2];
            st[*output_count].t = top_v;
            *output_count += 1;
        }
        for (i = 0; i < n; ++i) {
            if (top_v == i)
                continue;
            if (aa[top_v][i] < INF) {
                if (t2[i][0] == INF)
                    h_size = add_to_heap(h, h_size, i, t2[top_v][0] + aa[top_v][i], top_v);
                else if (t2[top_v][0] + aa[top_v][i] < t2[i][0]) {
                    t2[i][0] = t2[top_v][0] + aa[top_v][i];
                    t2[i][2] = top_v;
                    up_heap(h, t2[i][1]);
                }
            }
        }
    }
}

int main(void)
{
    int n, m;
    int i, j;
    int offset, diameter;
    struct edge ce;
    int output_count;

    scanf("%d %d", &n, &m);
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            a[i][j] = i == j ? 0 : INF;
    for (i = 0; i < m; ++i) {
        scanf("%d %d %d", &e[i].s, &e[i].t, &e[i].w);
        e[i].w *= 2; /* So that radius becomes diameter in future calculation */
        if (e[i].w < a[e[i].s - 1][e[i].t - 1])
            a[e[i].s - 1][e[i].t - 1] = a[e[i].t - 1][e[i].s - 1] = e[i].w;
    }

    floyd_warshall(a, d, n);
    calculate_farthest_ordering_matrix(d, s, n);
    calculate_vertex_one_center(e, d, s, n, m, &ce, &offset, &diameter);
    build_mdst(ce.s - 1, ce.t - 1, ce.w, offset, n, a, mdst, &output_count);

    // print_matrix(a, n);
    // print_matrix(d, n);
    // print_matrix(s, n);
    printf("s=%d, t=%d, w=%d, offset=%d\n", ce.s, ce.t, ce.w, offset);
    // printf("%d\n", output_count);
    printf("%d\n", diameter);
    for (i = 0; i < output_count; ++i) {
        if (mdst[i].s < mdst[i].t)
            printf("%d %d\n", mdst[i].s + 1, mdst[i].t + 1);
        else
            printf("%d %d\n", mdst[i].t + 1, mdst[i].s + 1);
    }

    return 0;
}
