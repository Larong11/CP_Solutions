#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

string ans;

struct ABC {
    int A, B, C, mx;
    ABC() : A(0), B(0), C(0), mx(0) {}
    inline void add(char &c) {
        if (c == 'A') {
            A++;
            mx = max(A, mx);
        } else if (c == 'B') {
            B++;
            mx = max(B, mx);
        } else {
            C++;
            mx = max(C, mx);
        }
    }
    inline void del(char &c) {
        if (c == 'A') {
            A--;
        } else if (c == 'B') {
            B--;
        } else {
            C--;
        }
        mx = max(A, max(B, C));
    }
};

char symbols[] = {'A', 'B', 'C'};
void gen(int u, vector<ABC> &hz, vector<vector<int>> &a, int &n, string &s, bool flag = false) {
    if (u == n) {
        if (hz[0].A <= hz[0].B or hz[0].A <= hz[0].C) {
            return;
        }
        ans = s;
        return;
    }
    for (auto &c : symbols) {
        if (!flag and c == 'C') {
            return;
        }
        if (c == 'B') {
            if (n - u - 1 + hz[0].A < hz[0].B + 1) {
                continue;
            }
        }
        if (c == 'C') {
            if (n - u - 1 + hz[0].A < hz[0].C + 1) {
                continue;
            }
        }

        s.push_back(c);
        bool can = true;
        int stop = u;
        for (int i = 0; i <= u; i++) {
            hz[i].add(c);
            if (hz[i].mx != a[i][u - i]) {
                stop = i;
                can = false;
                break;
            }
        }

        if (can) {
            gen(u + 1, hz, a, n, s, flag);
        }

        s.pop_back();
        for (int i = 0; i <= stop; i++) {
            hz[i].del(c);
        }
        if (ans != "") {
            return;
        }
    }
}

void solve() {
    int n;
    ans = "";
    cin >> n;
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int x;
            cin >> x;
            a[i].push_back(x);
        }
    }
    string s = "";
    vector<ABC> hz(n);
    gen(0, hz, a, n, s);
    if (ans == "") {
        // if (n <= 10) {
            gen(0, hz, a, n, s, true);
        // } else {
// 
        // }
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == 'A') {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
}
void solve2(vector<vector<int>> a) {
    int n = a.size();
    ans = "";
    string s = "";
    vector<ABC> hz(n);
    gen(0, hz, a, n, s);
    for (int i = 0; i < n; i++) {
        if (ans[i] == 'A') {
            cout << i + 1 << ' ';
        }
    }
    cout << endl;
}

vector<vector<int>> getA(string &s) {
    int n = s.size();
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int A = 0, B = 0, C = 0;
        for (int j = i; j < n; j++) {
            if (s[j] == 'A') {
                A++;
            } else if (s[j] == 'B') {
                B++;
            } else if (s[j] == 'C') {
                C++;
            }
            a[i].push_back(max(A, max(B, C)));
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
        solve();
    }
    // string s;
    // while (cin >> s) {
    //     vector<vector<int>> a = getA(s);
    //     for (auto &vec : a) {
    //         for (auto &i : vec) {
    //             cout << i << ' ';
    //         }
    //         cout << '\n';
    //     }
    //     solve2(a);
    // }
}

// 33 - 2:47:31