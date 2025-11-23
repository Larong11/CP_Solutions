#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

tuple<int, int, int> cnt(int x) {
    int c1 = 0, c2 = 0, c3 = 0;
    while (int(x / 7) * 7 == x) {
        x /= 7;
        c1++;
    }
    while (int(x / 5) * 5 == x) {
        x /= 5;
        c2++;
    }
    while (int(x / 3) * 3  == x) {
        x /= 3;
        c3++;
    }
    return tuple<int, int, int>(c1, c2, c3);
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto &vec : a) {
        for (auto &i : vec) {
            cin >> i;
        }
    }
    vector<vector<vector<int>>> c(n, vector<vector<int>>(n, vector<int>(4)));
    vector<vector<int>> ans(n, vector<int>(n));
    // {
    //     auto x = cnt(a[0][0]);
    //     ans[1][1] += get<0>(x) + get<1>(x) + get<2>(x);
    //     c[0][0][1] = get<0>(x);
    //     c[0][0][2] = get<1>(x);
    //     c[0][0][3] = get<2>(x);
    // }
    int table[4][3][3] = {
        { 
            {1, 2, 3},
            {8, 0, 4},
            {7, 6, 5}
        }, {
            {7, 8, 1},
            {6, 0, 2},
            {5, 4, 3}
        }, {
            {5, 6, 7},
            {4, 0, 8},
            {3, 2, 1}
        }, {
            {3, 4, 5},
            {2, 0, 6},
            {1, 8, 7}
        }
    };
    for (int j = 0; j + 2 < n; j++) {
        for (int i = 0; i + 1 < n; i++) {
            int x = a[i][j];
            int newDel = 1;
            for (int k = 0; k < 4; k++) {
                for (int j1 = 0; j1 < 3; j1++) {
                    for (int i1 = 0; i1 < 3; i1++) {
                        if (i1 == 0 and j1 == 0) {
                            continue;
                        }
                        if (i1 == 1 and j1 == 0 and k == 0) {
                            continue;
                        }
                        if (i - i1 >= 0 and j - j1 >= 0 and table[k][i1][j1] != 0) {
                            for (int p = 0; p < c[i - i1][j - j1][k]; p++) {
                                newDel *= table[k][i1][j1];
                            }
                        }
                    }
                }
            }
            x /= newDel;
            if (i > 0) {
                while (int(x / 8) * 8 == x) {
                    x /= 8;
                    c[i - 1][j][0]++;
                    ans[i][j + 1]++;
                }
            }
            auto dels = cnt(x);
            c[i][j][1] = get<0>(dels);
            c[i][j][2] = get<1>(dels);
            c[i][j][3] = get<2>(dels);
            ans[i + 1][j + 1] = get<0>(dels) + get<1>(dels) + get<2>(dels); 
        }
    }

    for (auto &vec : ans) {
        for (auto &i : vec) {
            cout << i << ' ';
        }
        cout << '\n';
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
#endif
    while (q--) {
        solve();
    }
}