#include <vector>
#include <algorithm>

#define N 1000
#define INF 1000000001  // 10^9 + 1
#define L 10

using namespace std;

int n;
int pow2[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
int pow2_rmq[L][L][N][N];

void init(vector<vector<int>> arr)
{
    n = arr.size();
    int i = 0;
    for (auto& itvv : arr) {
        int j = 0;
        for (auto& it : itvv) {
            pow2_rmq[0][0][i][j] = it;
            ++j;
        }
        ++i;
    }
    for (int l = 0; pow2[l + 1] <= n; ++l)
    for (int i = 0; i < n; ++i)
    for (int j = 0; j + pow2[l] < n; ++j)
        pow2_rmq[0][l + 1][i][j] = min(pow2_rmq[0][l][i][j], pow2_rmq[0][l][i][j + pow2[l]]);
    for (int l = 0; pow2[l] <= n; ++l)
    for (int m = 0; pow2[m + 1] <= n; ++m)
    for (int j = 0; j < n; ++j)
    for (int i = 0; i + pow2[m] < n; ++i)
        pow2_rmq[m + 1][l][i][j] = min(pow2_rmq[m][l][i][j], pow2_rmq[m][l][i + pow2[m]][j]);

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
    int sw = pow2_rmq[hh][ww][a][c];
    int nw = pow2_rmq[hh][ww][b - pow2[hh] + 1][c];
    int ne = pow2_rmq[hh][ww][b - pow2[hh] + 1][d - pow2[ww] + 1];
    int se = pow2_rmq[hh][ww][a][d - pow2[ww] + 1];
    return min({sw, nw, ne, se});
}
