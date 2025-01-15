#include <cstdio>

using namespace std;

#define N 500

struct main_street {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct main_street m[N];

int main()
{
    int a, b;
    int n;
    scanf("%d %d", &a, &b);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d %d %d %d", &m[i].x1, &m[i].y1, &m[i].x2, &m[i].y2);
    return 0;
}
