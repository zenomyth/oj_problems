#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#define N 1500
#define M 1500

using namespace std;

int n, m;
char chizu[2][N][M];

bool is_connected(int idx, int x, int y)
{
    if (x < 0 || y < 0)
        return false;
    // cout << x << " " << y << endl;
    // for (int i = 0; i < x; ++i) {
        // for (int j = 0; j < y; ++j)
            // cout << chizu[idx][i][j] << " ";
        // cout << endl;
    // }
    if(chizu[idx][0][0] == 'X' || chizu[idx][x - 1][y - 1] == 'X')
        return false;
    vector<vector<int>> visit(x, vector<int>(y, 0));
    queue<pair<int, int>> next;
    next.push(make_pair(0, 0));
    while (!next.empty()) {
        pair<int, int> top = next.front();
        next.pop();
        // cout << top.first << " " << top.second << endl;
        if ((top.first == x - 1 && top.second == y - 1) || (top.first == x - 1 && top.second == y - 2) || (top.first == x - 2 && top.second == y - 1))
            return true;
        int right = top.second + 1;
        if (right < y && visit[top.first][right] == 0 && chizu[idx][top.first][right] == 'O') {
            visit[top.first][right] = 1;
            next.push(make_pair(top.first, right));
        }
        int down = top.first + 1;
        if (down < x && visit[down][top.second] == 0 && chizu[idx][down][top.second] == 'O') {
            visit[down][top.second] = 1;
            next.push(make_pair(down, top.second));
        }
        int up = top.first - 1;
        if (up >= 0 && visit[up][top.second] == 0 && chizu[idx][up][top.second] == 'O') {
            visit[up][top.second] = 1;
            next.push(make_pair(up, top.second));
        }
        int left = top.second - 1;
        if (left >= 0 && visit[top.first][left] == 0 && chizu[idx][top.first][left] == 'O') {
            visit[top.first][left] = 1;
            next.push(make_pair(top.first, left));
        }
    }
    return false;
}

int find_max_balloons()
{
    int count = 0;
    int idx = 0, idx2 = 1;
    do {
        if (!is_connected(idx, n - count, m - count))
            break;
        ++count;
        for (int i = 0; i < n - count; ++i)
            for (int j = 0; j < m - count; ++j) {
                if (chizu[idx][i][j] == 'X' || chizu[idx][i][j + 1] == 'X' || chizu[idx][i + 1][j] == 'X' || chizu[idx][i + 1][j + 1] == 'X')
                    chizu[idx2][i][j] = 'X';
                else
                    chizu[idx2][i][j] = 'O';
            }
        idx ^= 1;
        idx2 ^= 1;
    } while (count < m && count < n);
    return count;
}

int find_max_balloons_2()
{
    if (!is_connected(0, n, m))
        return 0;
    int idx = 0, idx2 = 1;
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < m - 1; ++j) {
            if (chizu[idx][i][j] == 'X' || chizu[idx][i][j + 1] == 'X' || chizu[idx][i + 1][j] == 'X' || chizu[idx][i + 1][j + 1] == 'X')
                chizu[idx2][i][j] = 'X';
            else
                chizu[idx2][i][j] = 'O';
        }
    idx ^= 1;
    idx2 ^= 1;
    if (!is_connected(idx, n - 1, m - 1))
        return 1;
    int inc = 1;
    while (true) {
        for (int i = 0; i < n - inc; ++i)
            for (int j = 0; j < m - inc; ++j) {
                if (chizu[idx][i][j] == 'X' || chizu[idx][i][j + inc] == 'X' || chizu[idx][i + inc][j] == 'X' || chizu[idx][i + inc][j + inc] == 'X')
                    chizu[idx2][i][j] = 'X';
                else
                    chizu[idx2][i][j] = 'O';
            }
        idx ^= 1;
        idx2 ^= 1;
        if (!is_connected(idx, n - inc * 2, m - inc * 2)) {
            idx ^= 1;
            idx2 ^= 1;
            break;
        }
        inc *= 2;
    }
    int inc1 = inc / 2;
    while (inc1 > 0) {
        for (int i = 0; i < n - inc1; ++i)
            for (int j = 0; j < m - inc1; ++j) {
                if (chizu[idx][i][j] == 'X' || chizu[idx][i][j + inc1] == 'X' || chizu[idx][i + inc1][j] == 'X' || chizu[idx][i + inc1][j + inc1] == 'X')
                    chizu[idx2][i][j] = 'X';
                else
                    chizu[idx2][i][j] = 'O';
            }
        idx ^= 1;
        idx2 ^= 1;
        if (is_connected(idx, n - inc - inc1, m - inc - inc1))
            inc += inc1;
        else {
            idx ^= 1;
            idx2 ^= 1;
        }
        inc1 /= 2;
    }
    return inc + 1;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> chizu[0][i][j];
    cout << find_max_balloons_2() << endl;
    return 0;
}
