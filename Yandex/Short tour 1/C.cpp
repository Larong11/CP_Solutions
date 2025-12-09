#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int INF = 1e18;

int gen(int i, int lastSquare, int &sum, int &m, int &n, vector<int> &a, vector<int> &cur, vector<vector<vector<int>>> &used) {
    if (used[i][lastSquare][sum] != INF - 1) {
        return used[i][lastSquare][sum];
    }
    if (sum < 0 or (sum == 0 and i != n)) {
        return INF;
    }
    if (i == n) {
        if (sum != 0) {
            return INF;
        } else {
            return 0;
        }
    }
    int ans = INF;
    for (int j = lastSquare; j >= 1; j--) {
        sum -= j * j;
        if (sum < 0) {
            sum += j * j;
            used[i][j][sum] = INF;
            continue;
        }
        cur.push_back(j);
        used[i][j][sum + j * j] = (a[i] - j) * (a[i] - j) + gen(i + 1, j, sum, m, n, a, cur, used);
        cur.pop_back();
        sum += j * j;
    }
    for (int k = 2; k <= lastSquare; k++) {
        used[i][k][sum] = min(used[i][k][sum], used[i][k - 1][sum]);
    }
    return used[i][lastSquare][sum];
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    sort(a.rbegin(), a.rend());
    int sum = m;
    int lastSquare = sqrt(m) + 1;
    vector<int> cur;
    vector<vector<vector<int>>> used(n + 1, vector<vector<int>>(lastSquare + 1, vector<int>(sum + 1, INF - 1)));
    int ans = gen(0, lastSquare, sum, m, n, a, cur, used); 
    cout << (ans == INF? -1 : ans) << '\n';
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