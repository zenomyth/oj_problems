#include <bits/stdc++.h>

using namespace std;

void output_result(int64_t total_maxima, const multiset<int>& col_maxima, const multiset<int>& unused_val)
{
    int64_t total_val = total_maxima;
    int min_maxima = *col_maxima.begin();
    int max_unused = unused_val.empty() ? 0 : *unused_val.rbegin();
    if (min_maxima < max_unused)
        total_val += max_unused - min_maxima;
    printf("%" PRId64 "\n", total_val);
}

void erase_val(vector<multiset<int>>& col_val, multiset<int>& col_maxima, multiset<int>& unused_val, int64_t& total_maxima, int col, int val)
{
    int old_max = *col_val[col].rbegin();
    col_val[col].erase(col_val[col].find(val));
    int new_max = col_val[col].empty() ? 0 : *col_val[col].rbegin();
    if (old_max > new_max) {
        total_maxima = total_maxima - old_max + new_max;
        col_maxima.erase(col_maxima.find(old_max));
        if (new_max != 0) {
            col_maxima.insert(new_max);
            unused_val.erase(unused_val.find(new_max));
        }
    }
    else
        unused_val.erase(unused_val.find(val));
}

void insert_val(vector<multiset<int>>& col_val, multiset<int>& col_maxima, multiset<int>& unused_val, int64_t& total_maxima, int col, int val)
{
    int old_max = col_val[col].empty() ? 0 : *col_val[col].rbegin();
    col_val[col].insert(val);
    int new_max = *col_val[col].rbegin();
    if (old_max < new_max) {
        total_maxima = total_maxima - old_max + new_max;
        if (old_max != 0) {
            col_maxima.erase(col_maxima.find(old_max));
            unused_val.insert(old_max);
        }
        col_maxima.insert(new_max);
    }
    else
        unused_val.insert(val);
}

int main()
{
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    vector<int> col(n + 1), val(n + 1);
    vector<multiset<int>> col_val(m + 1);
    multiset<int> col_maxima;
    multiset<int> unused_val;
    for (int i = 1; i <= n; ++i) {
        scanf("%d %d", &col[i], &val[i]);
        col_val[col[i]].insert(val[i]);
    }
    int64_t total_maxima = 0;
    for (int i = 1; i <= m; ++i) {
        for (auto it = col_val[i].rbegin(); it != col_val[i].rend(); ++it) {
            if (it == col_val[i].rbegin()) {
                total_maxima += *it;
                col_maxima.insert(*it);
            }
            else
                unused_val.insert(*it);
        }
    }
    output_result(total_maxima, col_maxima, unused_val);
    for (int i = 0; i < q; ++i) {
        int type, idx, data;
        scanf("%d %d %d", &type, &idx, &data);
        if (type == 1) { // Color change
            erase_val(col_val, col_maxima, unused_val, total_maxima, col[idx], val[idx]);
            insert_val(col_val, col_maxima, unused_val, total_maxima, data, val[idx]);
            col[idx] = data;
            output_result(total_maxima, col_maxima, unused_val);
        }
        else { // Pretty value change
            erase_val(col_val, col_maxima, unused_val, total_maxima, col[idx], val[idx]);
            insert_val(col_val, col_maxima, unused_val, total_maxima, col[idx], data);
            val[idx] = data;
            output_result(total_maxima, col_maxima, unused_val);
        }
    }
    return 0;
}
