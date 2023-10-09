#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int n;
vector<pair<int, int>> alpacas;

int main()
{
    cin >> n;
    alpacas.reserve(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        alpacas.push_back(make_pair(a, b));
    }
    sort(alpacas.begin(), alpacas.end());
    // for (auto &it: alpacas)
        // cout << it.first << " " << it.second << endl;
    vector<int> dp;
    dp.reserve(n);
    dp[0] = 1;
    int ans = 1;
    for (int i = 1; i < n; ++i) {
        int cc = 0;
        for (int j = 0; j < i; ++j) {
            if (alpacas[i].first - alpacas[j].first >= max(alpacas[i].second, alpacas[j].second) && cc < dp[j])
                cc = dp[j];
        }
        dp[i] = cc + 1;
        if (ans < dp[i])
            ans = dp[i];
        // cout << dp[i] << endl;
    }
    cout << ans << endl;
    return 0;
}
