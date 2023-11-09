#include <cstdio>
#include <queue>

#define N 2000
#define INF 2001

using namespace std;

short n, m;
char chizu[N + 1][N + 1];
short canoe_len_support[N];
short unresolved_count;
short max_water_len = 0;
struct link {
    short n;
    short e;
    short s;
    short w;
} chizua[N][N];
short visit[N][N];
short visit_flag = 1;

void calc_access()
{
    for (short i = 0; i < n; ++i) {
        short j = 0;
        while (j < m && chizu[i][j] == '.')
            ++j;
        if (j == m)
            continue;
        chizua[i][j].w = INF;
        while (j < m) {
            short pos = j + 1;
            while (pos < m && chizu[i][pos] == '.')
                ++pos;
            if (pos == m) {
                chizua[i][j].e = INF;
                break;
            }
            else {
                chizua[i][j].e = pos;
                chizua[i][pos].w = j;
                if (pos - j - 1 > max_water_len)
                    max_water_len = pos - j - 1;
                j = pos;
            }
        }
    }
    for (short i = 0; i < m; ++i) {
        short j = 0;
        while (j < n && chizu[j][i] == '.')
            ++j;
        if (j == n)
            continue;
        chizua[j][i].n = INF;
        while (j < n) {
            short pos = j + 1;
            while (pos < n && chizu[pos][i] == '.')
                ++pos;
            if (pos == n) {
                chizua[j][i].s = INF;
                break;
            }
            else {
                chizua[j][i].s = pos;
                chizua[pos][i].n = j;
                if (pos - j - 1 > max_water_len)
                    max_water_len = pos - j - 1;
                j = pos;
            }
        }
    }
}

void add_to_visit_queue(queue<pair<short, short>> &todo, short x, short y)
{
    todo.push(make_pair(x, y));
    visit[x][y] = visit_flag;
}

void check_connection(short canoe_len)
{
    queue<pair<short, short>> todo;
    for (short i = 0; i < m; ++i) {
        if (chizu[0][i] == '#')
            add_to_visit_queue(todo, 0, i);
    }
    while (!todo.empty()) {
        pair<short, short> top = todo.front();
        todo.pop();
        if (chizua[top.first][top.second].n != INF && visit[chizua[top.first][top.second].n][top.second] != visit_flag) {
            short water_len = top.first - chizua[top.first][top.second].n - 1;
            if (water_len == 0 || water_len >= canoe_len)
                add_to_visit_queue(todo, chizua[top.first][top.second].n, top.second);
        }
        if (chizua[top.first][top.second].e != INF && visit[top.first][chizua[top.first][top.second].e] != visit_flag) {
            short water_len = chizua[top.first][top.second].e - top.second - 1;
            if (water_len == 0 || water_len >= canoe_len)
                add_to_visit_queue(todo, top.first, chizua[top.first][top.second].e);
        }
        if (chizua[top.first][top.second].s != INF && visit[chizua[top.first][top.second].s][top.second] != visit_flag) {
            short water_len = chizua[top.first][top.second].s - top.first - 1;
            if (water_len == 0 || water_len >= canoe_len)
                add_to_visit_queue(todo, chizua[top.first][top.second].s, top.second);
        }
        if (chizua[top.first][top.second].w != INF && visit[top.first][chizua[top.first][top.second].w] != visit_flag) {
            short water_len = top.second - chizua[top.first][top.second].w - 1;
            if (water_len == 0 || water_len >= canoe_len)
                add_to_visit_queue(todo, top.first, chizua[top.first][top.second].w);
        }
    }
    for (short i = 0; i < m; ++i) {
        if (canoe_len_support[i] == -1 && visit[n - 1][i] == visit_flag) {
            canoe_len_support[i] = canoe_len;
            --unresolved_count;
        }
    }
    ++visit_flag;
}

int main()
{
    scanf("%hd %hd", &n, &m);
    for (short i = 0; i < n; ++i)
        scanf("%s", chizu[i]);
    unresolved_count = m;
    for (short i = 0; i < m; ++i) {
        canoe_len_support[i] = -1;
        if (chizu[n - 1][i] == '.')
            --unresolved_count;
    }
    calc_access();
    check_connection(INF);
    for (short try_len = max_water_len; unresolved_count > 0 && try_len > 0; --try_len)
        check_connection(try_len);
    for (short i = 0; i < m; ++i)
        printf("%d%c", canoe_len_support[i] == INF ? 0 : canoe_len_support[i], i == m - 1 ? '\n' : ' ');
    return 0;
}
