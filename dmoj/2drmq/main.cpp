#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void init(std::vector<std::vector<int>> arr);
int query(int a, int b, int c, int d);

int main()
{
    string line;
    vector<vector<int>> data;
    while (getline(cin, line)) {
        stringstream ss(line);
        int cell;
        vector<int> vdata;
        while (ss >> cell)
            vdata.push_back(cell);
        data.push_back(vdata);
    }
    init(data);
    cout << query(0, 1, 0, 1) << endl;
    cout << query(1, 1, 0, 1) << endl;
    cout << query(0, 0, 1, 1) << endl;
    return 0;
}
