#include <iostream>
#include <cstdint>

#define N 200000

using namespace std;

int n;
struct Node {
    int dest;
    int parity;
    struct Node *next;
};
struct Node *conn[N + 1];
struct Node pool[N * 2];
struct Node *watermark = pool;
struct PathFromNode {
    int64_t odd;
    int64_t even;
    int pass_in_parity;
} subpath[N + 1];

void find_path_from_node(int root, int parent, int parity)
{
    if (parity)
        subpath[root].odd += 1;
    else
        subpath[root].even += 1;
    for (struct Node *p = conn[root]; p != NULL; p = p->next) {
        if (p->dest == parent)
            continue;
        find_path_from_node(p->dest, root, p->parity ^ parity);
        subpath[root].odd += subpath[p->dest].odd;
        subpath[root].even += subpath[p->dest].even;
    }
}

int64_t calc_diff(int64_t odd, int64_t even) {
    int64_t t_odd = odd * even;
    int64_t t_even = (int64_t)n * ((int64_t)n - 1) / 2 - t_odd;
    return t_odd < t_even ? t_even - t_odd : t_odd - t_even;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        watermark->dest = v;
        watermark->parity = (w & 1);
        watermark->next = conn[u];
        conn[u] = watermark;
        ++watermark;
        watermark->dest = u;
        watermark->parity = (w & 1);
        watermark->next = conn[v];
        conn[v] = watermark;
        ++watermark;
    }
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    find_path_from_node(1, 0, 0);
    int64_t m = calc_diff(subpath[1].odd, subpath[1].even);
    for (int i = 2; i <= n; ++i) {
        int64_t odd = subpath[1].odd - subpath[i].odd + subpath[i].even;
        int64_t even = subpath[1].even - subpath[i].even + subpath[i].odd;
        int64_t m1 = calc_diff(odd, even);
        if (m1 < m)
            m = m1;
    }
    cout << m << endl;
    return 0;
}
