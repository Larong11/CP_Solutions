#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

bool can(int &n, int &m, vector<vector<int>> &a, vector<string> &ans) {
    bool flag = true;
    for (auto &vec : a) {
        for (auto &i : vec) {
            if (i < 0) {
                return false;
            } else if (i != 0) {
                flag = false;
            }
        }
    }
    if (flag) {
        cout << "YES" << '\n';
        cout << ans.size() << '\n';
        for (auto &s : ans) {
            cout << s << '\n';
        }
        return true;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 0) {
                continue;
            }
            if (j + 2 < m) {
                set<int> xyi;
                for (int l = j; l < j + 3; l++) {
                    int d = a[i][l];
                    if (d == 0 or !xyi.insert(d).second) {
                        continue;
                    }
                    for (int k = j; k < j + 3; k++) {
                        a[i][k] -= d;
                    }
                    string op = to_string(i + 1) + " " + to_string(j + 1) + " "  + to_string(i + 1) + " " + to_string(j + 3) + " " + to_string(-d);
                    ans.push_back(op);
                    flag = can(n, m, a, ans);
                    ans.pop_back();
                    for (int k = j; k < j + 3; k++) {
                        a[i][k] += d;
                    }
                    if (flag) {
                        return flag;
                    }
                }
            }
            if (i + 2 < n) {
                set<int> xyi;
                for (int l = i; l < i + 3; l++) {
                    int d = a[l][j];
                    if (d == 0 or !xyi.insert(d).second) {
                        continue;
                    }
                    for (int k = i; k < i + 3; k++) {
                        a[k][j] -= d;
                    }
                    string op = to_string(i + 1) + " " + to_string(j + 1) + " "  + to_string(i + 3) + " " + to_string(j + 1) + " " + to_string(-d);
                    ans.push_back(op);
                    flag = can(n, m, a, ans);
                    ans.pop_back();
                    for (int k = i; k < i + 3; k++) {
                        a[k][j] += d;
                    }
                    if (flag) {
                        return flag;
                    }
                }
            }
        }
    }
    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &vec : a) {
        for (auto &i : vec) {
            cin >> i;
        }
    }
    vector<string> ans;
    auto c = can(n, m, a, ans);
    if (!c) {
        cout << "NO" << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
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