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
    int n, k, p;
    cin >> n >> k >> p;
    vector<int> order(p);
    for (auto &i : order) {
        cin >> i;
        --i;
    }
    vector<int> cars(p, p + 1);
    vector<int> nextCar(n, p + 1);
    for (int i = p - 1; i >= 0; i--) {
        // if (i + 1 < p and order[i + 1] == order[i]) {
            // cars[i] = cars[i + 1];
        // } else {
            cars[i] = nextCar[order[i]];
        // }
        nextCar[order[i]] = i;
    }
    nextCar.assign(n, 0);
    set<pair<int, int>> floor;
    int ans = 0;
    for (int i = 0; i < p; i++) {
        if (nextCar[order[i]]) {
            floor.erase({i, order[i]});
            floor.insert({cars[i], order[i]});
        } else {
            if ((int)floor.size() >= k) {
                auto mx = --floor.end();
                nextCar[mx->second] = 0;
                floor.erase(mx);
            }
            floor.insert({cars[i], order[i]});
            nextCar[order[i]] = 1;
            ans++;
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