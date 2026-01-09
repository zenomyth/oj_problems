#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<ll> bit; // 1..n used internally
    Fenwick(int n = 0) : n(n), bit(n + 1, 0) {}

    // Add val to position idx (0-based). Internal uses 1..n
    void add_idx(int idx, ll val) {
        // idx must be in [0, n-1]
        for (int i = idx + 1; i <= n; i += i & -i) bit[i] += val;
    }

    // Sum of prefix [0..idx] (0-based). If idx < 0 -> 0.
    ll sum_idx(int idx) const {
        if (idx < 0) return 0;
        ll res = 0;
        for (int i = idx + 1; i > 0; i -= i & -i) res += bit[i];
        return res;
    }
};

// Attenuation structure using two Fenwicks:
// - cnt: range-add + point-query (counts how many updates cover i)
// - sumSK: range-add + point-query (sum of (s+k) for updates covering i)
struct Attenuation {
    int n;
    Fenwick cnt, sumSK;
    Attenuation(int n = 0) : n(n), cnt(n), sumSK(n) {}

    // add attenuating sequence k, k-1, ..., 1 starting at s
    void attenuate_add(int s, int k) {
        if (k <= 0) return;
        int l = s;
        int r = s + k - 1;
        if (l >= n) return;
        if (r >= n) r = n - 1;

        // range-add +1 to cnt on [l..r]
        cnt.add_idx(l, 1);
        if (r + 1 < n) cnt.add_idx(r + 1, -1);

        // range-add +(s+k) to sumSK on [l..r]
        ll sk = (ll)s + (ll)k;
        sumSK.add_idx(l, sk);
        if (r + 1 < n) sumSK.add_idx(r + 1, -sk);
    }

    // revert the attenuation starting at s with length k
    // (apply the negative of the original update)
    void attenuate_revert(int s, int k) {
        if (k <= 0) return;
        int l = s;
        int r = s + k - 1;
        if (l >= n) return;
        if (r >= n) r = n - 1;

        // range-add -1 to cnt on [l..r]
        cnt.add_idx(l, -1);
        if (r + 1 < n) cnt.add_idx(r + 1, +1);

        // range-add -(s+k) to sumSK on [l..r]
        ll sk = (ll)s + (ll)k;
        sumSK.add_idx(l, -sk);
        if (r + 1 < n) sumSK.add_idx(r + 1, +sk);
    }

    // get value at position i
    ll point_query(int i) const {
        ll c = cnt.sum_idx(i);
        ll sk = sumSK.sum_idx(i);
        return sk - (ll)i * c;
    }

    // naive range sum (calls point_query for each index in range)
    // O((r-l+1) * log n). If you need many range-sums, we can make an O(log n) variant.
    ll range_sum_naive(int l, int r) const {
        if (l > r) return 0;
        ll s = 0;
        for (int i = l; i <= r; ++i) s += point_query(i);
        return s;
    }
};

struct TaskIndexMapping {
    int n;
    Fenwick mapping;
    int next_task;
    int gap;
    TaskIndexMapping(int n = 0) : n(n), mapping(n), next_task(0) {}

    void add_task() {
        mapping.add_idx(next_task, 1);
        ++next_task;
    }

    void delete_task(int idx) {
        mapping.add_idx(idx - 1, 1);
        mapping.add_idx(--next_task, -1);
    }

    int get_raw_index(int idx) {
        return (int)mapping.sum_idx(idx - 1);
    }
};

void test_attenuation()
{
    int n = 10;
    Attenuation ft(n);

    // your example
    ft.attenuate_add(0, 2); // -> [2,1,0,0,...]
    ft.attenuate_add(3, 3); // -> [2,1,0,3,2,1,0,...]
    ft.attenuate_add(1, 2); // -> [2,3,1,3,2,1,0,...]
    ft.attenuate_revert(1, 2);

    for (int i = 0; i < n; ++i) {
        cout << ft.point_query(i) << (i + 1 == n ? '\n' : ' ');
    }
    // prints: 2 3 1 3 2 1 0 0 0 0
}

void test_task_labeling()
{
    TaskIndexMapping tim(10);
    for (int i = 0; i < 6; ++i)
        tim.add_task();
    tim.delete_task(2);
    tim.add_task();
    tim.delete_task(6);
    tim.add_task();
    for (int i = 1; i <= 10; ++i)
        printf("%d%c", tim.get_raw_index(i), i == 10 ? '\n' : ' ');
}

int main()
{
    int q;
    scanf("%d", &q);
    q = 3;
    vector<pair<int, int>> tasks;
    tasks.reserve(q);
    //! It seems naive decay mechanism doesn't work
    Attenuation task_time(1000001);
    multiset<int> start_time;
    ll ans = 0;
    TaskIndexMapping task_map(q);
    while (q-- > 0) {
        char op;
        scanf(" %c", &op);
        if (op == 'A') {
            int s, t;
            scanf("%d %d", &s, &t);
            s = (int)((s + ans) % 1000003);
            t = (int)((t + ans) % 1000003);
            tasks.push_back({s, t});
            task_time.attenuate_add(s, t);
            start_time.insert(s);
            task_map.add_task();
        }
        else {
            int i;
            scanf("%d", &i);
            i = (int)((i + ans) % 1000003);
            int raw_idx = task_map.get_raw_index(i) - 1;
            printf("i=%d %d\n", i, raw_idx);
            task_map.delete_task(i);
            int s = tasks[raw_idx].first;
            int t = tasks[raw_idx].second;
            start_time.erase(start_time.find(s));
            task_time.attenuate_revert(s, t);
        }
        int latest_start_time = *start_time.rbegin();
        ans = latest_start_time + task_time.point_query(latest_start_time) - 1;
        printf("%lld\n", ans);
        for (int i = 1; i <= 20; ++i)
            printf("%lld%c", task_time.point_query(i), i == 20 ? '\n' : ' ');
    }
}
