#include <bits/stdc++.h>

using namespace std;

struct orig_edge { int u, v, w; };
struct adj_edge { int t, w; };

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    vector<orig_edge> orig_graph;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        orig_graph.push_back({u, v, w});
    }
    // construct a line graph
    vector<vector<adj_edge>> adj(m + 2);
    // for (int i = 0; i < m; ++i) {
        // for (int j = i + 1; j < m; ++j) {
            // if (orig_graph[i].u == orig_graph[j].u || orig_graph[i].u == orig_graph[j].v ||
                // orig_graph[i].v == orig_graph[j].u || orig_graph[i].v == orig_graph[j].v) {
                // int w = abs(orig_graph[i].w - orig_graph[j].w);
                // adj[i].push_back({j, w});
                // adj[j].push_back({i, w});
            // }
        // }
        // if (orig_graph[i].u == 1 || orig_graph[i].v == 1) {
            // adj[m].push_back({i, orig_graph[i].w});
            // adj[i].push_back({m, orig_graph[i].w});
        // }
        // if (orig_graph[i].u == n || orig_graph[i].v == n) {
            // adj[m + 1].push_back({i, 0});
            // adj[i].push_back({m + 1, 0});
        // }
    // }
    vector<vector<int>> incident(n + 1);
    for (int i = 0; i < m; i++) {
        incident[orig_graph[i].u].push_back(i);
        incident[orig_graph[i].v].push_back(i);
    }
    // For each vertex, connect its incident edges
    // for (int v = 1; v <= n; v++) {
        // auto &edges = incident[v];
        // for (int i = 0; i < (int)edges.size(); i++) {
            // for (int j = i + 1; j < (int)edges.size(); j++) {
                // int ei = edges[i], ej = edges[j];
                // int w = abs(orig_graph[ei].w - orig_graph[ej].w);
                // adj[ei].push_back({ej, w});
                // adj[ej].push_back({ei, w});
            // }
        // }
    // }
    for (int v = 1; v <= n; v++) {
        auto &edges = incident[v];
        sort(edges.begin(), edges.end(), [&](int a, int b) {
            return orig_graph[a].w < orig_graph[b].w;
        });
        for (int i = 0; i + 1 < (int)edges.size(); i++) {
            int ei = edges[i], ej = edges[i+1];
            int w = abs(orig_graph[ei].w - orig_graph[ej].w);
            adj[ei].push_back({ej, w});
            adj[ej].push_back({ei, w});
        }
    }
    for(auto& e: incident[1]) {
        adj[m].push_back({e, orig_graph[e].w});
        adj[e].push_back({m, orig_graph[e].w});
    }
    for(auto& e: incident[n]) {
        adj[m + 1].push_back({e, 0});
        adj[e].push_back({m + 1, 0});
    }
    // Run Dijkstra
    vector<int64_t> dist(m + 2, INT64_MAX);
    dist[m] = 0;
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> pq;
    pq.push({0, m});
    while (!pq.empty()) {
        auto top = pq.top();
        int64_t d = top.first;
        int u = top.second;
        pq.pop();
        if (u == m + 1) {
            printf("%" PRId64 "\n", d);
            break;
        }
        if (d > dist[u])
            continue;
        for (auto& e: adj[u]) {
            if (d + e.w < dist[e.t]) {
                dist[e.t] = d + e.w;
                pq.push({dist[e.t], e.t});
            }
        }
    }
    return 0;
}
