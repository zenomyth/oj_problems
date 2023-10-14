#include <iostream>
#include <algorithm>

#define N 600

using namespace std;

int t, n;
int a[N];

int main()
{
    cin >> t;
    do {
        cin >> n;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        if (n == 1) {
            cout << a[0] << endl;
            continue;
        }
        sort(a, a + n);
        if ((n & 1) == 0 && a[0] == a[n - 1]) {
            cout << -1 << endl;
            continue;
        }
        cout << a[n - 1] << " ";
        for (int i = 1; i < n - 1; ++i)
            cout << a[i] << " ";
        cout << a[0] << endl;
    } while (--t > 0);
    return 0;
}
