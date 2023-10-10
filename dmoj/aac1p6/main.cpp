#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>

using namespace std;

int n;
vector<pair<int, int>> alpacas;
vector<int> dp;
vector<int> fenwick;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> waiting_list;

void fenwick_insert(int pos, int val)
{
    int size = (int)fenwick.size();
    while (pos < size) {
        if (fenwick[pos] < val)
            fenwick[pos] = val;
        pos += pos & (-pos);
    }
}

int fenwick_query(int pos)
{
    int val = 0;
    while (pos > 0) {
        if (val < fenwick[pos])
            val = fenwick[pos];
        pos -= pos & (-pos);
    }
    return val;
}

void find_participants()
{
    sort(alpacas.begin(), alpacas.end());
    // for (auto &it: alpacas)
        // cout << it.first << " " << it.second << endl;
    dp.reserve(n + 1);
    int ans = 1;
    fenwick.resize(alpacas[n - 1].first + 1, 0);
    for (int i = 0; i < n; ++i) {
        // cout << alpacas[i].first << " " << alpacas[i].second << endl;
        while (!waiting_list.empty()) {
            const pair<int, int> &top = waiting_list.top();
            if (top.first > alpacas[i].first)
                break;
            fenwick_insert(alpacas[top.second].first, dp[top.second]);
            // cout << top.first << " " << top.second << endl;
            waiting_list.pop();
        }
        dp[i] = fenwick_query(alpacas[i].first - alpacas[i].second) + 1;
        if (ans < dp[i])
            ans = dp[i];
        waiting_list.push(make_pair(alpacas[i].first + alpacas[i].second, i));
        // cout << dp[i] << endl;
    }
    cout << ans << endl;
}

void test_fenwick()
{
    fenwick.resize(11, 0);
    fenwick_insert(3, 7);
    fenwick_insert(2, 5);
    fenwick_insert(5, 5);
    for (int i = 1; i < (int)fenwick.size(); ++i)
        cout << fenwick[i] << " " << fenwick_query(i) << endl;
}

void test_priority_queue()
{
    waiting_list.push(make_pair(5, 1));
    waiting_list.push(make_pair(3, 2));
    waiting_list.push(make_pair(6, 3));
    waiting_list.push(make_pair(2, 4));
    while (!waiting_list.empty()) {
        cout << waiting_list.top().first << " " << waiting_list.top().second << endl;
        waiting_list.pop();
    }
}

int main()
{
    cin >> n;
    alpacas.reserve(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        alpacas.push_back(make_pair(a, b));
    }
    find_participants();
    // test_fenwick();
    // test_priority_queue();
    return 0;
}
