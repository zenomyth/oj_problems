#include <iostream>

using namespace std;

int main()
{
    int N, X;
    cin >> N >> X;
    if (((N - X) & 1) == 1)
        cout << -1 << endl;
    else {
        for (int i = 0; i < X; ++i)
            cout << i * 2 << (i == N - 1 ? '\n' : ' ');
        for (int i = X; i < N; ++i) {
            cout << i * 2 << ' ';
            ++i;
            cout << i * 2 + 1 << (i == N - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
