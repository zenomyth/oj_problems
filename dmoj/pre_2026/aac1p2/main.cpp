#include <iostream>
#include <cmath>

#define MAX_N (1000000)

using namespace std;

double AI[MAX_N];

int main()
{
    double N, D, X, P;
    int K;
    cin >> N >> D >> K >> X;
    for (int i = 0; i < N; ++i)
        cin >> AI[i];
    cin >> P;
    for (int i = 0; i < N; ++i) {
        if (P <= AI[i]) {
            if (X == 100)
                --K;
            else if(P == AI[i])
                --K;
            else {
                // double k = (log(P) - log(AI[i])) / (log(100 - X) - log(100)); // TLE
                // double k = (log(P / AI[i])) / (log((100 - X) / 100)); // WA
                double k = (log(P) - log(AI[i])) / (log((100 - X) / 100));
                double k1 = floor(k);
                if (k == k1)
                    k1 += 1;
                K -= (int)k1;
            }
            if (K < 0)
                break;
        }
    }
    if (K < 0)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
    return 0;
}
