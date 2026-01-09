#include <iostream>
#include <vector>

using namespace std;

#define N 1000
#define L 10

void init(std::vector<std::vector<int>> arr);
int query(int a, int b, int c, int d);
extern int data_2d[N][N];
extern int n;
extern int pow2[];
extern int pow2_rmq[L][L][N][N];

void print_pow2_rmq()
{
    for (int i = 0; pow2[i] <= n; ++i)
        for (int j = 0; pow2[j] <= n; ++j)
            for (int l = 0; l < n; ++l)
                for (int m = 0; m < n; ++m) {
                    if (l + pow2[i] <= n && m + pow2[j] <= n)
                        cout << ">> " << i << " " << j << " " << l << " " << m << " " << pow2_rmq[i][j][l][m] << endl;
                }
}

int main()
{
    int n;
	cin >> n;
    vector<vector<int>> data(n, vector<int>(n));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> data[i][j];
    init(data);
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		cout << query(a, b, c, d) << endl;
	}
    // print_pow2_rmq();
    return 0;
}
