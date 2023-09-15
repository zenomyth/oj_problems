#include <vector>

#define N 1000
#define INF 1000000001  // 10^9 + 1
#define L 10

using namespace std;

int range[N][N];
int n;
int l;
int intervals[L] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
int calc[N][N][L][L];

void init(std::vector<std::vector<int>> arr)
{
    n = arr.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            range[i][j] = arr[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            min = INF;
            for(int k = 0, l = 0; j + intervals[l] < n; ++k) {
                if (k == intervals[l])
                    calc[i][j][0][l++] = min;
                if (arr[i][j + k] < min)
                    min = arr[i][j + k];
            }
        }
}

int query(int a, int b, int c, int d)
{
    int min = INF;
    for (int i = a; i <= b; ++i)
        for (int j = c; j <= d; ++j)
            if (range[i][j] < min)
                min = range[i][j];
    return min;
}
