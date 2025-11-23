#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;

#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void solve() {
    string s;
    map<string, int> atoms;
    while (cin >> s) {
        int n = s.size();
        string name;
        int num = 0;
        for (auto &c : s) {
            if ('A' <= c and c <= 'Z') {
                if (!name.empty()) {
                    atoms[name] += max(1, num);
                }
                name.clear();
                name.push_back(c);
                num = 0;
            } else if ('a' <= c and c <= 'z') {
                if (!name.empty()) {
                    name.push_back(c);
                }
            } else if ('0' <= c and c <= '9') {
                if (!name.empty()) {
                    num *= 10;
                    num += c - '0';
                    if (num == 0) {
                        name.clear();
                    }
                }
            }
        }
        if (!name.empty()) {
            atoms[name] += max(1, num);
        }
    }
    for (auto &[key, val] : atoms) {
        cout << key << ' ' << val << '\n';
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