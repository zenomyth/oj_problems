#include <cstdio>
#include <utility>
#include <cstdlib>

using namespace std;

#define N 500

struct main_street {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct main_street m[N];

bool check_access(int d, int a, int b, int n)
{
    bool v[N];
    for (int i = 0; i < n; ++i)
        v[i] = false;
    int ax1 = -d, ax2 = d, ay1 = -d, ay2 = d;
    for (int i = 0; i < n; ++i) {
        bool updated = false;
        for (int j = 0; j < n; ++j) {
            // printf("process(j=%d, v=%d, points=%d,%d,%d,%d)\n", j, v[j], m[j].x1, m[j].y1, m[j].x2, m[j].y2);
            if (v[j])
                continue;
            if (m[j].x1 == m[j].x2) {
                if (m[j].x1 <= ax1 || m[j].x1 >= ax2)
                    continue;
                // printf(">>---\n");
                if (m[j].y1 <= ay1 && m[j].y2 > ay1) {
                    v[j] = true;
                    ay1 = m[j].y1 - 1;
                    updated = true;
                    // printf("ay1->%d from (%d %d %d %d)\n", ay1, m[j].x1, m[j].y1, m[j].x2, m[j].y2);
                    break;
                }
                else if (m[j].y1 < ay2 && m[j].y2 >= ay2) {
                    v[j] = true;
                    ay2 = m[j].y2 + 1;
                    updated = true;
                    break;
                }
                else if (m[j].y1 > ay1 && m[j].y2 < ay2)
                    v[j] = true;
            }
            else { // m[j].y1 == m[j].y2
                if (m[j].y1 <= ay1 || m[j].y1 >= ay2)
                    continue;
                // printf(">>|||\n");
                if (m[j].x1 <= ax1 && m[j].x2 > ax1) {
                    v[j] = true;
                    ax1 = m[j].x1 - 1;
                    updated = true;
                    break;
                }
                else if (m[j].x1 < ax2 && m[j].x2 >= ax2) {
                    v[j] = true;
                    ax2 = m[j].x2 + 1;
                    updated = true;
                    break;
                }
                else if (m[j].x1 > ax1 && m[j].x2 < ax2)
                    v[j] = true;
            }
        }
        if (!updated)
            break;
    }
    // printf("%d %d %d %d\n", ax1, ax2, ay1, ay2);
    if (a > ax1 && a < ax2 && b > ay1 && b < ay2)
        return true;
    else
        return false;
}

int calc_max_square(int a, int b, int n)
{
    int d = abs(a);
    if (d < abs(b))
        d = abs(b);
    bool access;
    access = check_access(d, a, b, n);
    if (!access)
        return d;
    access = check_access(1, a, b, n);
    if (access)
        return 0;
    int dh = d;
    int dl = 1;
    while (true) {
        d = (dh + dl) / 2;
        if (d == dl)
            break;
        access = check_access(d, a, b, n);
        // printf("%d->%d\n", d, access);
        if (access)
            dh = d;
        else
            dl = d;
    }
    return d;
}

int main()
{
    int a, b;
    int n;
    scanf("%d %d", &a, &b);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &m[i].x1, &m[i].y1, &m[i].x2, &m[i].y2);
        if (m[i].x1 == m[i].x2 && m[i].y1 > m[i].y2)
            swap(m[i].y1, m[i].y2);
        if (m[i].y1 == m[i].y2 && m[i].x1 > m[i].x2)
            swap(m[i].x1, m[i].x2);
    }
    int ans = calc_max_square(a, b, n);
    printf("%d\n", ans);
    return 0;
}
