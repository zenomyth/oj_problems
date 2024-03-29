// Solution from https://github.com/spaghetti-source/Competitive-Programming/blob/master/SPOJ1479.cc
// SPOJ 1479: The GbAaY Kingdom
//
// Solution: Minimum Diameter Spanning Tree
//
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#define ALL(c) c.begin(), c.end()
#define FOR(i,c) for(typeof(c.begin())i=c.begin();i!=c.end();++i)
#define REP(i,n) for(int i=0;i<n;++i)

typedef pair<int,int> PII;
#define fst first
#define snd second

typedef int Weight;
const Weight INF = 1 << 28;
struct Graph {
  struct Edge {
    int s, t;
    Weight w;
    Edge(int s, int t, Weight w) : s(s), t(t), w(w) { }
  };
  int n;
  vector<Edge> edge; // edge list
  vector< vector<Weight> > A; // adj matrix

  Graph(int n) : n(n), A(n, vector<int>(n, INF)) {
    REP(u, n) A[u][u] = 0;
  }
  void addEdge(int s, int t, Weight w) {
    w *= 2; // because of half integrality
    if (w >= A[s][t]) return;
    A[s][t] = A[t][s] = w;
    edge.push_back(Edge(s, t, w));
  }

  vector<int> R; // radius from the absolute center
  vector<bool> visited;
  void traverse(int u, int sh = 0) { // explicit construction of sp-tree
    visited[u] = true;
    REP(v,n) if (R[v] == R[u] + A[u][v]) {
      if (!visited[v]) {
        printf("%d %d\n", u+1, v+1);
        traverse(v, sh+2);
      }
    }
  }
  vector< vector<Weight> > d;
  vector< vector<int> > L;
  void farthestOrdering () {
    L.assign(n, vector<int>(n)); d = A;
    REP(z,n) REP(x,n) REP(y,n)
      d[x][y] = min(d[x][y], d[x][z] + d[z][y]);
    REP(x,n) {
      vector<PII> aux;
      REP(y,n) aux.push_back(PII(-d[x][y], y));
      sort(ALL(aux));
      REP(k,n) L[x][k] = aux[k].snd; // farthest ordering
    }
  }
  Weight minimumDiameterSpanningTree() {
    farthestOrdering(); // preprocessing
    Weight h, D = INF;
    Edge &e = edge[0];
    FOR(it, edge) {
      int s = it->s, t = it->t; // for simplicity
      Weight w = it->w;
      if (d[s][L[t][0]] + d[t][L[s][0]] + w > 2*D) continue; // Halpern bound
      if (L[s][0] == L[t][0]) continue; // no-coincide condition

      vector<int> &v = L[s];
      int k = 0; // last active constraint
      Weight x = 0, y = min(d[s][v[0]], d[t][v[0]] + w), xi, yi;
      for (int i = 1; i < n; ++i) {
        if (d[t][v[k]] < d[t][v[i]]) { // i is active
          xi = (d[t][v[k]] - d[s][v[i]] + w) / 2;
          yi = xi + d[s][v[i]];
          if (yi < y) { y = yi; x = xi; }
          k = i;
        }
      }
      yi = min(d[s][v[k]]+w, d[t][v[k]]);
      if (yi < y) { y = yi; x = 1; }
      if (y < D) { D = y; h = x; e = *it; }
    }
    printf("%d\n", D);
    R.resize(n); // explicit reconstruction by DFS
    REP(u, n) R[u] = min(d[e.s][u]+h, d[e.t][u]+e.w-h);
    visited.assign(n, false);
    if (h > 0) traverse(e.t);
    if (e.w > h) {
      traverse(e.s);
      if (h > 0) printf("%d %d\n", e.s+1, e.t+1);
    }
  }
};

int main () {
  int n, m; scanf("%d%d", &n, &m);
  Graph G(n);

  while (m--) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    --a, --b;
    G.addEdge(a, b, c);
  }
  G.minimumDiameterSpanningTree();
}