#include <iostream>
#include <vector>

using namespace std;

void test_vector_assign()
{
	int n = 10;
	vector< vector<int> > L;
	L.assign(n, vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << L[i][j] << '\t';
		cout << endl;
	}
	cout << "Hello" << endl;
}

int main(void)
{
	test_vector_assign();
    return 0;
}
