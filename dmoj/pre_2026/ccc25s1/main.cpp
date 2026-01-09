#include <cstdio>
#include <climits>

using namespace std;

int main()
{
    int l1, h1, l2, h2;
    scanf("%d %d %d %d", &l1, &h1, &l2, &h2);
    int c1 = 2 * (l1 + l2 + (h1 > h2 ? h1 : h2));
    int c2 = 2 * (h1 + h2 + (l1 > l2 ? l1 : l2));
    printf("%d\n", c1 < c2 ? c1 : c2);
    return 0;
}
