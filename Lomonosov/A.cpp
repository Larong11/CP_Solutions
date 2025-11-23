#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void solve() {
    int k;
    cin >> k;
    string ans;
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        int curNum = 0;
        string curAns;
        char prevC = '.';
        for (char c : s) {
            if (c == '.') {
                if (curNum >= 26) {
                    curAns.push_back('a' + curNum - 26);
                } else {
                    curAns.push_back('A' + curNum);
                }
                curNum = 0;
            } else {
                if (c == 'N') {
                    curNum += 0;
                } else if (c == 'I') {
                    curNum += 1;
                } else if (c == 'V') {
                    if (prevC == 'I') {
                        curNum += 3;
                    } else {
                        curNum += 5;
                    }
                } else if (c == 'X') {
                    if (prevC == 'I') {
                        curNum += 8;
                    } else {
                        curNum += 10;
                    }
                } else if (c == 'L') {
                    if (prevC == 'X') {
                        curNum += 30;
                    } else {
                        curNum += 50;
                    }
                }
            }
            prevC = c;
        }
        if (curNum >= 26) { 
            curAns.push_back('a' + curNum - 26);
        } else {
            curAns.push_back('A' + curNum);
        }
        if (curAns.size() > ans.size()) {
            ans = curAns;
        } else {
            ans = max(ans, curAns);
        }
    }
    cout << ans << '\n';
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