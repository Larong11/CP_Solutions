#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;
mt19937 rng(73);  // или любой другой сид
int ni(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

bool solve(vector<vector<int>> &a) {
    int n = a.size();
    int m = a[0].size();
    bool flag = true;
    if (flag) {
        return true;
    }

    if (n % 3 == 0) {
        return true;
        cout << m * n / 3 << '\n';
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j += 3) {
                cout << i + 1 << ' ' << j + 1 << ' ' << i + 1 << ' ' << j + 3 << ' ' << -a[j][i] << '\n';
            }
        }
    } else if (m % 3 == 0) {
        return true;
        cout << m * n / 3 << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j += 3) {
                cout << j + 1 << ' ' << i + 1 << ' ' << j + 3 << ' ' << i + 1 << ' ' << -a[i][j] << '\n';
            }
        }
    } else {
        return false;
        cout << "NO" << '\n';
    }
}


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

bool solv1(vector<vector<int>> &a) {
    int n = a.size();
    int m = a[0].size();
    vector<string> ans;
    return can(n, m, a, ans);
}

vector<vector<int>> gen() {
    int n = ni(3, 6), m = ni(3, 6);
    int x = ni(0, 10);
    vector<vector<int>> a(n, vector<int>(m));
    for (auto &vec : a) {
        for (auto &i : vec) {
            i = x;
        }
    }
    return a;
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
        auto a = gen();
        auto f = solv1(a);
        auto s = solve(a);
        if (f != s) {
            cout << a.size() << ' ' << a[0].size() << '\n';
            for (auto &vec : a) {
                for (auto &i : vec ){
                    cout << i << ' ';
                }
                cout << '\n';
            }
        }
        cout << q << endl;
    }
}