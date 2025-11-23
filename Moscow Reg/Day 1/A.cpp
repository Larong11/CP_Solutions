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
    int n, m;
    cin >> n;
    
    vector<string> c(n);
    vector<string> val;
    for (auto &i : c) {
        cin >> i;
        val.push_back(i);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    m = val.size();

    vector<pair<vector<int>, int>> idxs(m);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int bi = lower_bound(val.begin(), val.end(), s) - val.begin();
        idxs[bi].first.push_back(i);
    }
    int up = 0, up2 = 0;
    int down = 0, down2 = 0;
    for (int i = 0; i < n; i++) {
        int ai = lower_bound(val.begin(), val.end(), c[i]) - val.begin();
        int id = idxs[ai].first[idxs[ai].second];
        if (id > i) {
            down = max(down, id - i);
        } else {
            up = max(up, i - id);
        }
        idxs[ai].second++;
    }
    cout << max(up, down) + 2 * min(up, down) << '\n';
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