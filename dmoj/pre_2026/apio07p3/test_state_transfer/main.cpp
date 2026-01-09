#include <cstdio>

using namespace std;

int n, e;
int res[2][16][32];
int ce = 0;
int cr = 0, nx = 1;

void test_print_selected_state()
{
    for (int i = 0; i < 32; ++i)
        printf("ce#%d:%d%d%d%d%d=%d\n", ce, i & 1, (i >> 1) & 1, (i >> 2) & 1, (i >> 3) & 1, (i >> 4) & 1, res[cr][0][i]);
    for (int i = 0; i < 32; ++i)
        printf("e#%d:%d%d%d%d%d=%d\n", e, i & 1, (i >> 1) & 1, (i >> 2) & 1, (i >> 3) & 1, (i >> 4) & 1, res[nx][0][i]);
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
        // printf("m=%d\n", m);
        for (int j = 0; j < (1 << r); ++j) {
            int ns = (j << (5 - r)) | i;
            if (is_state_compatible(s, ns, e))
                res[nx][s][ns] = m;
        }
    }
}

int main()
{
    // n = 12;
    // e = 7;
    // ce = 5;
    // res[cr][0][1] = 1;
    // res[cr][0][16] = 1;
    // state_transfer(0);
    // test_print_selected_state();
    n = 10;
    printf("%d\n", is_state_compatible(2, 0, 10));
    return 0;
}
