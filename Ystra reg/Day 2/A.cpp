#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

int operator*(pair<int, int> a, pair<int, int> b) {
    return (b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second);
}

const int cst = 1e4;

void solve() {
    int n;
    cin >> n;
    int xs[(int)3e4];
    int ys[(int)3e4];
    memset(ys, 0, sizeof(ys));
    memset(xs, 0, sizeof(xs));
    vector<int> possibleX;
    vector<int> possibleY;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        xs[x + cst]++;
        ys[y + cst]++;
        possibleX.push_back(x);        
        possibleY.push_back(y);        
    }
    sort(possibleX.begin(), possibleX.end());
    sort(possibleY.begin(), possibleY.end());
    possibleX.erase(unique(possibleX.begin(), possibleX.end()), possibleX.end());
    possibleY.erase(unique(possibleY.begin(), possibleY.end()), possibleY.end());
    int res = 0;
    int X = possibleX.size(), Y = possibleY.size();
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < i; j++) {
            res += (possibleX[i] - possibleX[j]) * (possibleX[i] - possibleX[j]) * xs[possibleX[i] + cst] * xs[possibleX[j] + cst];
        }
    }
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < i; j++) {
            res += (possibleY[i] - possibleY[j]) * (possibleY[i] - possibleY[j]) * ys[possibleY[i] + cst] * ys[possibleY[j] + cst];
        }
    }
    cout << res << '\n';
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
// 4:56:55 - 80
// 4:21:59 - 100
