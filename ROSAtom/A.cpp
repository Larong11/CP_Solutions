#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

vector<int> decrypt(int x) {
    vector<int> ans = {0, 0, 0, 0};
    for (int i = 3; i >= 0; i--) {
        ans[i] = x % 256;
        x /= 256;
    }
    return ans;
}

int encrypt(vector<int> &x) {
    int ans = x[0] * 256 * 256 * 256 + x[1] * 256 * 256 + x[2] * 256 + x[3];
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> ip;
    for (int i = 0; i < n; i++) {
        vector<int> local = {0, 0, 0, 0};
        int m = 0;
        string s;
        cin >> s;
        int x = 0;
        for (auto &ch : s) {
            if (ch == '.' or ch == '/') {
                x++;
                continue;
            }
            if (x < 4) {
                local[x] = 10 * local[x] + (ch - '0');
            } else {
                m = 10 * m + (ch - '0');
            }
        }
        m = 32 - m;
        int IP = encrypt(local);
        int minIP = (IP>>m)<<m;
        int maxIP = (IP>>m);
        for (int j = 0; j < m; j++) {
            maxIP = maxIP * 2ll + 1ll;
        }
        ip.push_back(make_pair(minIP, 0));
        ip.push_back(make_pair(maxIP, 1));
        // auto m1 = decrypt(minIP);
        // auto m2 = decrypt(maxIP);
        // cout << m1[0] << '.' << m1[1] << '.' << m1[2] << '.' << m1[3] << '\n';
        // cout << m2[0] << '.' << m2[1] << '.' << m2[2] << '.' << m2[3] << '\n';
        // cout << '\n';
    }
    sort(ip.begin(), ip.end());
    int open = 0;
    for (auto &[x, o] : ip) {
        if (o) {
            open--;
        } else {
            open++;
        }
        if (open > 1) {
            cout << "YES" << '\n';
            return;
        }
    }
    cout << "NO" << '\n';
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