#include <vector>

#define N 1000
#define INF 1000000001  // 10^9 + 1

using namespace std;

int range[N][N];
int n;

void init(std::vector<std::vector<int>> arr)
{
    n = arr.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            range[i][j] = arr[i][j];
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
