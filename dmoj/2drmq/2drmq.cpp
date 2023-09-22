#include <iostream>
#include <vector>
#include <algorithm>

#define N 1000
#define INF 1000000001  // 10^9 + 1
#define L 10

using namespace std;

int n;
int pow2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
int pow2_rmq[N][N][L][L];

void calc_pow2_rmq_1d(const std::vector<std::vector<int>>& arr, int idx1, int idx2)
{
    int min_val = INF;
    int pow2_idx = 0;
    for (int i = idx2; i < n; ++i) {
        if (arr[idx1][i] < min_val)
            min_val = arr[idx1][i];
        if (i - idx2 + 1 == pow2[pow2_idx]) {
            pow2_rmq[idx1][idx2][0][pow2_idx] = min_val;
            if (idx2 + pow2[++pow2_idx] > n)
                break;
        }
    }
}

void pow2_rmq_v_popu(int idx1, int idx2) {
    int pow2_idx2 = 0;
    do {
        int min_val = INF;
        int pow2_idx = 0;
        for (int i = idx1; i < n; ++i) {
            if (pow2_rmq[i][idx2][0][pow2_idx2] < min_val)
                min_val = pow2_rmq[i][idx2][0][pow2_idx2];
            if (i - idx1 + 1 == pow2[pow2_idx]) {
                pow2_rmq[idx1][idx2][pow2_idx][pow2_idx2] = min_val;
                if (idx1 + pow2[++pow2_idx] > n)
                    break;
            }
        }
        ++pow2_idx2;
    } while (idx2 + pow2[pow2_idx2] <= n);
}

void init(std::vector<std::vector<int>> arr)
{
    n = arr.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            calc_pow2_rmq_1d(arr, i, j);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            pow2_rmq_v_popu(i, j);
}

int query(int a, int b, int c, int d)
{
    int h = b - a + 1;
    int w = d - c + 1;
    int hh = 0;
    int ww = 0;
    while (pow2[hh + 1] < h)
        ++hh;
    while (pow2[ww + 1] < w)
        ++ww;
    int sw = pow2_rmq[a][c][hh][ww];
    int nw = pow2_rmq[b - pow2[hh] + 1][c][hh][ww];
    int ne = pow2_rmq[b - pow2[hh] + 1][d - pow2[ww] + 1][hh][ww];
    int se = pow2_rmq[a][d - pow2[ww] + 1][hh][ww];
    return min({sw, nw, ne, se});
}

// int query2(int a, int b, int c, int d)
// {
    // int min_val = INF;
    // for (int i = a; i <= b; ++i)
        // for (int j = c; j <= d; ++j)
            // if (range[i][j] < min_val)
                // min_val = range[i][j];
    // return min_val;
// }
