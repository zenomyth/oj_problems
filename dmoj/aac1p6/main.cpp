#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <tuple>

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

void find_participants_compress_axis()
{
    vector<tuple<int, int, int>> coor_list;
    coor_list.reserve(n * 3);
    for (int i = 0; i < n; ++i) {
        coor_list.push_back(make_tuple(alpacas[i].first, i, 0));
        coor_list.push_back(make_tuple(alpacas[i].first < alpacas[i].second ? 0 : alpacas[i].first - alpacas[i].second, i, 1));
        coor_list.push_back(make_tuple(alpacas[i].first + alpacas[i].second, i, 2));
    }
    sort(coor_list.begin(), coor_list.end());
    // for (auto &it: coor_list)
        // cout << get<0>(it) << " " << get<1>(it) << " " << get<2>(it) << endl;
    vector<int> idx_map(n, -1);
    int idx_next = 0;
    for (auto &it: coor_list) {
        if (get<2>(it) != 0)
            continue;
        idx_map[get<1>(it)] = idx_next++;
    }
    vector<vector<int>> ar(n, vector<int>(3, 0));
    int last_coor = 0;
    int coor_next = 1;
    for (auto &it: coor_list) {
        if (last_coor != get<0>(it)) {
            ++coor_next;
            last_coor = get<0>(it);
        }
        ar[idx_map[get<1>(it)]][get<2>(it)] = coor_next;
    }
    // for (auto &it: ar)
        // cout << it[0] << " " << it[1] << " " << it[2] << endl;
    dp.reserve(n + 1);
    int ans = 1;
    fenwick.resize(coor_next + 1, 0);
    for (int i = 0; i < n; ++i) {
        while (!waiting_list.empty()) {
            const pair<int, int> &top = waiting_list.top();
            if (top.first > ar[i][0])
                break;
            fenwick_insert(ar[top.second][0], dp[top.second]);
            // cout << top.first << " " << top.second << endl;
            waiting_list.pop();
        }
        dp[i] = fenwick_query(ar[i][1]) + 1;
        if (ans < dp[i])
            ans = dp[i];
        waiting_list.push(make_pair(ar[i][2], i));
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
    // find_participants();
    find_participants_compress_axis();
    // test_fenwick();
    // test_priority_queue();
    return 0;
}
