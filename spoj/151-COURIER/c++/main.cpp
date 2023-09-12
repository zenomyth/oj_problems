#include <iostream>

using namespace std;

#define N 100 // Maximum number of cities
#define M 10000 // Maximum number of roads
#define Z 5 // Maximum number of transfer requests
#define B 12 // Maximum number of total parcels
#define D 10000 // Maximun road length
#define D_MAX (20 * N * D) // Maximum distance

int t; // Test cases
int n; // Number of cities
int m; // Number of roads
int b; // Courier's home city
int z; // Number of transfer requests
int bb; // Total parcels

int am[N + 1][N + 1]; // Adjacency matrix -> Short paths matrix
int as[M][3]; // Adjacency set
int req[Z][3]; // Transfer requests

int state[Z + 1]; // Expanded DP state. Number of delivered parcels + current location
int l_enc[N + 1]; // Encrypt current location
int l_dec[Z + 1]; // Decrypt current location

int st[B + 1][1 << (B + 3)]; // States after each DP iteration. 3 = ceil(log(Z + 1))

void Floyd_Warshall()
{
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) {
                if (am[i][j] > am[i][k] + am[k][j])
                    am[i][j] = am[i][k] + am[k][j];
            }
}

int save_state()
{
    int s = 0;
    s = l_enc[state[z]];
    for (int i = z - 1; i >= 0; --i) {
        s <<= req[i][2];
        s |= state[i];
    }
    return s;
}

void load_state(int s)
{
    for (int i = 0; i < z; ++i) {
        state[i] = (s >> req[i][2] << req[i][2]) ^ s;
        s >>= req[i][2];
    }
    state[z] = l_dec[s];
}

int main(void)
{
    cin >> t;
    while (t--) {
        cin >> n >> m >> b;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                am[i][j] = i == j ? 0 : D_MAX;
        for (int i = 1; i <= n; ++i)
            am[i][i] = 0;
        for (int i = 0; i < m; ++i) {
            cin >> as[i][0] >> as[i][1] >> as[i][2];
            if (as[i][2] < am[as[i][0]][as[i][1]])
                am[as[i][0]][as[i][1]] = am[as[i][1]][as[i][0]] = as[i][2];
        }
        cin >> z;
        int bb = 0;
        for (int i = 0; i < z; ++i) {
            cin >> req[i][0] >> req[i][1] >> req[i][2];
            bb += req[i][2];
        }
        for (int i = 0; i < bb + 1; ++i)
            for (int j = 0; j < (1 << (bb + 3)); ++j)
                st[i][j] = D_MAX;
        st[0][0] = 0; // The courier is at home
        Floyd_Warshall();
        // for (int i = 1; i <= n; ++i) {
            // for (int j = 1; j <= n; ++j)
                // cout << am[i][j] << " ";
            // cout << endl;
        // }
        l_dec[0] = b;
        l_enc[b] = 0;
        for (int i = 0, ii = 1; i < z; ++i) {
            bool new_loc = true;
            for (int j = 0; j < ii; ++j) {
                if (l_dec[j] == req[i][1]) {
                    new_loc = false;
                    break;
                }
            }
            if (new_loc) {
                l_dec[ii] = req[i][1];
                l_enc[req[i][1]] = ii;
                ++ii;
            }
        }
        // z = 5;
        // req[0][2] = 1;
        // req[1][2] = 2;
        // req[2][2] = 4;
        // req[3][2] = 1;
        // req[4][2] = 4;
        // state[0] = 1;
        // state[1] = 2;
        // state[2] = 4;
        // state[3] = 0;
        // state[4] = 3;
        // state[5] = 99;
        // l_enc[99] = 5;
        // l_dec[5] = 99;
        // int x = save_state();
        // cout << "x=" << x << endl;
        // load_state(x);
        // for (int i = 0; i < z + 1; ++i)
            // cout << state[i] << endl;
        // x = save_state();
        // cout << "x=" << x << endl;
        for (int i = 0; i < bb; ++i) {
        // for (int i = 0; i < 2; ++i) {
            // cout << "=======" << endl;
            for (int j = 0; j < (1 << (bb + 3)); ++j) {
                if (st[i][j] < D_MAX) {
                    load_state(j);
                    for (int k = 0; k < z; ++k) {
                        if (state[k] == req[k][2])
                            continue;
                        ++state[k];
                        int loc_save = state[z];
                        state[z] = req[k][1];
                        int new_state = save_state();
                        --state[k];
                        state[z] = loc_save;
                        int d_new_state = st[i][j] + am[state[z]][req[k][0]] + am[req[k][0]][req[k][1]];
                        // cout << "From city " << state[z] << " via city " << req[k][0] << " to city " << req[k][1] << ": " << d_new_state
                            // << ", " << st[i][j] << ", " << state[0] << state[1] << state[2] << state[3] << state[4] << " " << st[i][j] << endl;
                        if (d_new_state < st[i + 1][new_state])
                            st[i + 1][new_state] = d_new_state;
                    }
                }
            }
        }
        int ans = D_MAX;
        for (int i = 0; i < (1 << (bb + 3)); ++i) {
            if (st[bb][i] < D_MAX) {
                load_state(i);
                int cand = st[bb][i] + am[state[z]][b];
                if (cand < ans)
                    ans = cand;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
