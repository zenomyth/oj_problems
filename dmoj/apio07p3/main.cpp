#include <cstdio>

using namespace std;

#define N 10000
#define C 50000

int n, e;
char fll[5];
int res[2][16][32];
int ce = 0;
int cr = 0, nx = 1;

// Still can't find logic error. Maybe print all the decision process to debug

void test_print_selected_state(int s)
{
    for (int i = 0; i < 32; ++i)
        printf("ce#%d:%d%d%d%d%d=%d\n", ce, i & 1, (i >> 1) & 1, (i >> 2) & 1, (i >> 3) & 1, (i >> 4) & 1, res[cr][s][i]);
    for (int i = 0; i < 32; ++i)
        printf("e#%d:%d%d%d%d%d=%d\n", e, i & 1, (i >> 1) & 1, (i >> 2) & 1, (i >> 3) & 1, (i >> 4) & 1, res[nx][s][i]);
}

bool is_state_compatible(int s, int ns, int ee)
{
    if (ee < 5) {
        int overlap = 5 - ee;
        int s_expected = s >> (4 - overlap);
        int s_actual = ns & ((1 << overlap) - 1);
        return s_expected == s_actual;
    }
    if (ee > n - 4) {
        int overlap = ee - (n - 4);
        int s_expected = s & ((1 << overlap) - 1);
        int s_actual = ns >> (5 - overlap);
        return s_expected == s_actual;
    }
    return true;
}

void state_transfer(int s)
{
    int r = e - ce < 5 ? e - ce : 5;
    for (int i = 0; i < (1 << (5 - r)); ++i) {
        int m = 0;
        for (int j = 0; j < (1 << r); ++j) {
            int ns = i << r | j;
            if (res[cr][s][ns] > m)
                m = res[cr][s][ns];
        }
        for (int j = 0; j < (1 << r); ++j) {
            int ns = (j << (5 - r)) | i;
            if (is_state_compatible(s, ns, e))
                res[nx][s][ns] = m;
        }
    }
}

void progress_with_initial_state(int s)
{
    int st[5];
    for (int i = e; i <= 4; ++i)
        st[i - e] = (s >> (i - 1)) & 1;
    for (int i = e + 4; i > n; --i)
        st[i - e] = (s >> (i - n - 1)) & 1;
    /* Selectable animals are in [beg, end) */
    int beg = e > 4 ? 0 : 5 - e;
    int end = n - e + 1 > 4 ? 5 : n - e + 1;
    // printf("beg=%d,end=%d\n", beg, end);
    state_transfer(s);
    // if (s == 2)
        // test_print_selected_state(s);
    /* Evaluate current child */
    for (int i = 0; i < (1 << (end - beg)); ++i) {
        for (int j = 0; j < end - beg; ++j)
            st[beg + j] = ((i >> j) & 1);
        int ns = 0;
        for (int j = 0; j < 5; ++j)
            ns |= (st[j] << j);
        for (int j = 0; j < 5; ++j) {
            if (st[j] == 1) {
                if (fll[j] == 'l') {
                    ++res[nx][s][ns];
                    // printf("res[%d][%d][%d]=%d\n", nx, s, ns, res[nx][s][ns]);
                    break;
                }
            }
            else {
                if (fll[j] == 'f') {
                    ++res[nx][s][ns];
                    // printf("res[%d][%d][%d]=%d\n", nx, s, ns, res[nx][s][ns]);
                    break;
                }
            }
        }
    }
}

void  prepare_next_state()
{
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 32; ++j)
            res[nx][i][j] = 0;
}

int main()
{
    int c, f, l;
    int fl;
    scanf("%d %d", &n, &c);
    for (int i = 0; i < c; ++i) {
        scanf("%d %d %d", &e, &f, &l);
        for (int j = 0; j < 5; ++j)
            fll[j] = 'n';
        for (int j = 0; j < f; ++j) {
            scanf("%d", &fl);
            if (fl >= e)
                fll[fl - e] = 'f';
            else
                fll[fl + n - e] = 'f';
        }
        for (int j = 0; j < l; ++j) {
            scanf("%d", &fl);
            if (fl >= e)
                fll[fl - e] = 'l';
            else
                fll[fl + n - e] = 'l';
        }
        for (int j = 0; j < 16; ++j)
            progress_with_initial_state(j);
        cr ^= 1;
        nx ^= 1;
        ce = e;
        prepare_next_state();
    }
    int ans = 0;
    // int mi = -1, mj = -1;
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 32; ++j) {
            if (res[cr][i][j] > ans)
                ans = res[cr][i][j];
                // ans = res[cr][mi = i][mj = j];
        }
    printf("%d\n", ans); // n = 9999, c = 49999
    // printf("s=%d, ns=%d\n", mi, mj);
    return 0;
}
