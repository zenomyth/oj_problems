#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    string line;
    vector< vector<int> > data;
    while (getline(cin, line)) {
        stringstream ss(line);
        int cell;
        vector<int> vdata;
        while (ss >> cell)
            vdata.push_back(cell);
        data.push_back(vdata);
    }
    for (vector< vector<int> >::iterator it = data.begin(); it != data.end(); ++it) {
        for (vector<int>::iterator it2 = it->begin(); it2 != it->end(); ++it2)
            cout << *it2 << " ";
        cout << endl;
    }
    return 0;
}
