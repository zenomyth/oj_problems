#include <iostream>
#include <vector>

using namespace std;

void init(std::vector<std::vector<int>> arr);
int query(int a, int b, int c, int d);

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
    return 0;
}
