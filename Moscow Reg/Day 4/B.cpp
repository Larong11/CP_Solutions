#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

bool checkOk(int i, int j, int dir1, int dir2, vector<vector<int>> &g) {
    return i + dir1 < 0 or i + dir1 >= (int)g.size() or j + dir2 < 0 or j + dir2 >= (int)g[i].size() or g[i + dir1][j + dir2] == 0;
}
pair<pair<int, int>, pair<int, int>> dirs[] = {
    make_pair(make_pair(0, -1), make_pair(0, 1)),
    make_pair(make_pair(-1, 0), make_pair(1, 0)),
    make_pair(make_pair(0, -1), make_pair(-1, 0)),
    make_pair(make_pair(-1, 0), make_pair(0, 1)),
    make_pair(make_pair(1, 0), make_pair(0, 1)),
    make_pair(make_pair(0, -1), make_pair(1, 0))
};

bool checkCon(int i, int j, int dir1, int dir2, vector<vector<int>> &g) {
    int i1 = i + dir1;
    int j1 = j + dir2;
    auto [dir11, dir12] = dirs[g[i1][j1] - 1].first;
    auto [dir21, dir22] = dirs[g[i1][j1] - 1].second;
    return (i == i1 + dir11 and j == j1 + dir12) or (i == i1 + dir21 and j == j1 + dir22);
}

bool dfs(int startFromi, int startFromj, int i, int j, int fromi, int fromj, vector<vector<int>> &g, vector<vector<int>> &used, int &s) {
    if ((i == -1 and j == -1) or used[i][j] == s) {
        bool can = true;
        if (i != -1 or j != -1) {
            // cout << "ENDED AT " << i << ' ' << j << '\n';
            // for (auto &vec : g) {
            //     for (auto &i : vec) {
            //         cout << i << ' ';
            //     }
            //     cout << '\n';
            // }
            auto [dir1, dir2] = dirs[g[fromi][fromj] - 1].first;
            auto [dir11, dir22] = dirs[g[fromi][fromj] - 1].second;
            can = !checkOk(fromi, fromj, dir1, dir2, g) and !checkOk(fromi, fromj, dir11, dir22, g);
            if (!can) {
                return false;
            }
            can = checkCon(fromi, fromj, dir1, dir2, g) and checkCon(fromi, fromj, dir11, dir22, g);
            if (!can) {
                return false;
            }

        }
        int start = s;
        ++s;
        for (int i1 = startFromi; i1 < (int)g.size(); i1++) {
            for (int j1 = startFromj; j1 < (int)g[i1].size(); j1++) {
                if (g[i1][j1] == 0 or used[i1][j1]) {
                    continue;
                } else {
                    if (g[i1][j1] == 1 or g[i1][j1] == 2) {
                        bool flag = false;
                        if (i1 > 0) {
                            flag = dfs(i1, j1, i1, j1, i1 - 1, j1, g, used, s);
                        }
                        if (!flag and j1 > 0) {
                            flag = dfs(i1, j1, i1, j1, i1, j1 - 1, g, used, s);
                        }
                        can = flag;
                    } else {
                        bool flag = false;
                        if (i1 > 0) {
                            flag = dfs(i1, j1, i1, j1, i1 - 1, j1, g, used, s);
                        }
                        if (!flag and i1 < (int)g.size()) {
                            flag = dfs(i1, j1, i1, j1, i1 + 1, j1, g, used, s);
                        }
                        if (!flag and j1 > 0) {
                            flag = dfs(i1, j1, i1, j1, i1, j1 - 1, g, used, s);
                        }
                        if (!flag and j1 < (int)g[i1].size()) {
                            flag = dfs(i1, j1, i1, j1, i1, j1 + 1, g, used, s);
                        }
                        can = flag;
                    }
                }
            }
        }
        if (!can) {
            s = start + 1;
        }
        return can;
    }
    if (used[i][j] != s and used[i][j] != 0) {
        return false;
    }
    used[i][j] = s;
    if (g[i][j] == 1 or g[i][j] == 2) {
        int dir1 = i - fromi;
        int dir2 = j - fromj;
        if (checkOk(i, j, dir1, dir2, g)) {
            used[i][j] = 0;
            return false;
        } else {
            if (dir1 == 0) {
                g[i][j] = 1;
            } else {
                g[i][j] = 2;
            }
            bool flag = dfs(startFromi, startFromj, i + dir1, j + dir2, i, j, g, used, s);
            if (flag) {
                return true;
            } else {
                used[i][j] = 0;
                return false;
            }
        }
    } else {
        if (i - fromi == 0) {
            bool flag = false;
            if (!flag and !checkOk(i, j, 1, 0, g)) {
                g[i][j] = (j > fromj? 6 : 5);
                flag = dfs(startFromi, startFromj, i + 1, j, i, j, g, used, s);
            }
            if (!flag and !checkOk(i, j, -1, 0, g)) {
                g[i][j] = (j > fromj? 3 : 4);
                flag = dfs(startFromi, startFromj, i - 1, j, i, j, g, used, s);
            }
            if (flag) {
                return true;
            } else {
                used[i][j] = 0;
                return false;
            }
        } else {
            bool flag = false;
            if (!flag and !checkOk(i, j, 0, 1, g)) {
                g[i][j] = (i < fromi? 5 : 4);
                flag = dfs(startFromi, startFromj, i, j + 1, i, j, g, used, s);
            }
            if (!flag and !checkOk(i, j, 0, -1, g)) {
                g[i][j] = (i < fromi? 6 : 3);
                flag = dfs(startFromi, startFromj, i, j - 1, i, j, g, used, s);
            }
            if (flag) {
                return true;
            } else {
                used[i][j] = 0;
                return false;
            }
        }
    }
}

void solve() {
    int n, m, G;
    cin >> n >> m >> G;
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            cin >> x;
            g[i][j] = x;
        }
    }
    vector<vector<int>> used(n, vector<int>(m, 0));
    bool can = true;
    {
        int i = 0, j = 0, s = 0;
        can = dfs(i, j, -1, -1, 0, 0, g, used, s);
    }
    if (can) {
        cout << "YES" << '\n';
        for (auto &vec : g) {
            for (auto &i : vec) {
                cout << i << ' ';
            }
            cout << '\n';
        }
    } else {
        cout << "NO" << '\n';
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