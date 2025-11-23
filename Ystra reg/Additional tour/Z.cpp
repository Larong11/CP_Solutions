#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int ALL = (1 << 27) - 1;

string solve(vector<int> &a, int m) {
    int n = a.size();
    string ans = "a";
    vector<bool> used(26, false);
    // vector<int> help(n, (1<<27) - 1);
    used[0] = true;
    int d = 1;
    if (a[0] != 0) {
        return "";
    }
    for (int i = 1; i < n; i++) {
        if (a[i] - a[i - 1] > 1) {
            return "";
        }
        if (a[i] != 0) {
            ans.push_back(ans[a[i] - 1]);
        } else {
            if (a[i - 1] != 0) {
                
                int can = ALL;
                can -= (1<<0);
                int cur = a[i - 1];
                while (cur != 0) {
                    can &= ALL - (1 << (ans[cur] - 'a'));
                    cur = a[cur - 1];
                }
                bool set = false;
                for (int j = 1; j < 26; j++) {
                    if (can & (1 << j)) {
                        if (!used[j]) {
                            d++;
                            used[j] = true;
                        }
                        set = true;
                        ans.push_back('a' + j);
                        break;
                    }
                }
                if (!set) {
                    return "";
                }
            } else {
                if (!used[1]) {
                    used[1] = true;
                    d++;
                }
                ans.push_back('b');
            }
        }
        if (d > m) {
            return "";
        }
    }
    return ans;
}

void prefix(string &s, vector<int> &a) {
    if (s.size() != a.size()) {
        cout << "NO" << '\n';
        return;
    }
    int n = s.size();
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] and cur != 0) {
            cur = p[cur - 1];
        }
        if (s[i] == s[cur]) {
            p[i] = cur + 1;
        }
    }
    // for (auto &i : p) {
    //     cout << i << ' ';
    // }
    for (int i = 0; i < n; i++) {
        if (p[i] != a[i]) {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
    cout << s << '\n';
}

vector<int> prefix2(string s) {
    int n = s.size();
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] and cur != 0) {
            cur = p[cur - 1];
        }
        if (s[i] == s[cur]) {
            p[i] = cur + 1;
        }
    }
    // for (auto &i : p) {
    //     cout << i << ' ';
    // }
    // cout << '\n';
    return p;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    string s;
    // while (cin >> s >> m) {
    //     vector<int> a = prefix2(s);
    //     string s = solve(a, m);
    //     prefix(s, a);
    // }
    while (cin >> n >> m) {
        vector<int> a(n);
        for (auto &i : a) {
            cin >> i;
        }
        string s = solve(a, m);
        prefix(s, a);
    }
}