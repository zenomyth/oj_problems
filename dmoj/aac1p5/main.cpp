#include <iostream>

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
int visited[N + 1];
struct PathFromNode {
    int node;
    int odd;
    int even;
} q[N];
int head = 0;
int tail = 0;

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
    int odd = 0, even = 0;
    q[tail].node = 1;
    q[tail].odd = 0;
    q[tail].even = 0;
    ++tail;
    while (head != tail) {
        struct PathFromNode *top = &q[head++];
        visited[top->node] = 1;
        cout << top->node << " " << top->odd << " " << top->even << " " << endl;
        for (struct Node *p = conn[top->node]; p != NULL; p = p->next) {
            if (visited[p->dest])
                continue;
            q[tail].node = p->dest;
            if (p->parity) {
                q[tail].odd = top->even + 1;
                q[tail].even = top->odd;
            }
            else {
                q[tail].odd = top->odd;
                q[tail].even = top->even + 1;
            }
            odd += q[tail].odd;
            even += q[tail].even;
            ++tail;
        }
    }
    cout << odd << endl;
    cout << even << endl;
    return 0;
}
