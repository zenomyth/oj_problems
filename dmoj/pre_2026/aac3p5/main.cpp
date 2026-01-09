#include <cstdio>
#include <algorithm>

#define N 2000
#define INF 2001

using namespace std;

int n, m;
char chizu[N + 1][N + 1];
int canoe_len_support[N];
int unresolved_count;
struct vertex {
    int x;
    int y;
};
struct edge {
    vertex v1;
    vertex v2;
    int len;
} edges[N * N * 2];
int edges_size = 0;
vertex dsu_parent[N][N];
int dsu_size[N][N];
int start_pos;

void find_all_edges()
{
    start_pos = 0;
    while (start_pos < m && chizu[0][start_pos] == '.')
        ++start_pos;
    if (start_pos == m)
        return;
    while (start_pos < m) {
        int pos = start_pos + 1;
        while (pos < m && chizu[0][pos] == '.')
            ++pos;
        if (pos == m)
            break;
        edges[edges_size].v1.x = 0;
        edges[edges_size].v1.y = start_pos;
        edges[edges_size].v2.x = 0;
        edges[edges_size].v2.y = pos;
        edges[edges_size].len = INF;
        ++edges_size;
        start_pos = pos;
    }
    for (int i = 1; i < n; ++i) {
        int j = 0;
        while (j < m && chizu[i][j] == '.')
            ++j;
        while (j < m) {
            int pos = j + 1;
            while (pos < m && chizu[i][pos] == '.')
                ++pos;
            if (pos == m)
                break;
            edges[edges_size].v1.x = i;
            edges[edges_size].v1.y = j;
            edges[edges_size].v2.x = i;
            edges[edges_size].v2.y = pos;
            edges[edges_size].len = pos - j == 1 ? INF : pos - j - 1;
            ++edges_size;
            j = pos;
        }
    }
    for (int i = 0; i < m; ++i) {
        int j = 0;
        while (j < n && chizu[j][i] == '.')
            ++j;
        while (j < n) {
            int pos = j + 1;
            while (pos < n && chizu[pos][i] == '.')
                ++pos;
            if (pos == n)
                break;
            edges[edges_size].v1.x = j;
            edges[edges_size].v1.y = i;
            edges[edges_size].v2.x = pos;
            edges[edges_size].v2.y = i;
            edges[edges_size].len = pos - j == 1 ? INF : pos - j - 1;
            ++edges_size;
            j = pos;
        }
    }
    struct {
        bool operator()(const edge &a, const edge &b) const { return a.len > b.len; }
    } order_edge_by_len_rev;
    sort(&edges[0], &edges[edges_size], order_edge_by_len_rev);
    // for (int i = 0; i < edges_size; ++i)
        // printf("%d(%d): %d %d <> %d %d\n", i, edges[i].len, edges[i].v1.x, edges[i].v1.y, edges[i].v2.x, edges[i].v2.y);
}

void dsu_make_set(vertex v)
{
    dsu_parent[v.x][v.y] = v;
    dsu_size[v.x][v.y] = 1;
}

vertex dsu_find_set(vertex v)
{
    if (dsu_parent[v.x][v.y].x == v.x && dsu_parent[v.x][v.y].y == v.y)
        return v;
    return dsu_parent[v.x][v.y] = dsu_find_set(dsu_parent[v.x][v.y]);
}

void dsu_union_sets(vertex v1, vertex v2)
{
    v1 = dsu_find_set(v1);
    v2 = dsu_find_set(v2);
    if (v1.x != v2.x || v1.y != v2.y) {
        if (dsu_size[v1.x][v1.y] < dsu_size[v2.x][v2.y])
            swap(v1, v2);
        dsu_parent[v2.x][v2.y] = v1;
        dsu_size[v1.x][v1.y] += dsu_size[v2.x][v2.y];
    }
}

void query_connectivity(int conoe_len)
{
    vertex vs = dsu_find_set({0, start_pos});
    for (int i = 0; i < m; ++i) {
        if (chizu[n - 1][i] == '.' || canoe_len_support[i] != -1)
            continue;
        vertex vi = dsu_find_set({n - 1, i});
        if (vi.x == vs.x && vi.y == vs.y) {
            canoe_len_support[i] = conoe_len;
            --unresolved_count;
        }
    }
}

void build_and_query_dsu()
{
    unresolved_count = m;
    for (int i = 0; i < m; ++i) {
        canoe_len_support[i] = -1;
        if (chizu[n - 1][i] == '.')
            --unresolved_count;
    }
    if (unresolved_count == 0 || start_pos == m)
        return;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            dsu_make_set({i, j});
    int cur_len = edges[0].len;
    for (int i = 0; i < edges_size; ++i) {
        if (edges[i].len != cur_len) {
            query_connectivity(cur_len);
            if (unresolved_count == 0)
                return;
            cur_len = edges[i].len;
        }
        dsu_union_sets(edges[i].v1, edges[i].v2);
    }
    query_connectivity(cur_len);
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%s", chizu[i]);
    find_all_edges();
    build_and_query_dsu();
    for (int i = 0; i < m; ++i)
        printf("%d%c", canoe_len_support[i] == INF ? 0 : canoe_len_support[i], i == m - 1 ? '\n' : ' ');
    return 0;
}
