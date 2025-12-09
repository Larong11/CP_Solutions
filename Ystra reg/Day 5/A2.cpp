#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int INF = 1e9;

int dist(int i, int j, vector<pair<int, int>> &points) {
    return abs(points[i].first - points[j].first) + abs(points[i].second - points[j].second);
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> points;
    for (int i = 0; i < 2 * n; i++) {
        int x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }
    sort(points.begin(), points.end());
    int ans = 0;

    if (n == 1) {
        cout << dist(0, 1, points) << '\n';
        return;
    }

    vector<bool> used(2 * n, false);

    for (int i = 0; i < 2 * n - 1; i++) {
        if (used[i]) {
            continue;
        }
        int j = i + 1;
        while (j < 2 * n and used[j]) {
            j++;
        }
        int k = j + 1;
        while (k < 2 * n and used[k]) {
            k++;
        }
        if (k == 2 * n) {
            ans = max(ans, dist(i, j, points));
            used[i] = true;
            used[j] = true;
        } else {
            if (points[j].first == points[i].first and points[j].first != points[k].first) {
                int dij = dist(i, j ,points);
                used[i] = true;
                used[j] = true;
                ans = max(ans, dij);
            } else {
                int dij = dist(i, j ,points);
                int dik = dist(i, k ,points);
                if (dij < dik ) {
                    used[i] = true;
                    used[j] = true;
                    ans = max(ans, dij);
                } else {
                    used[i] = true;
                    used[k] = true;
                    ans = max(ans, dik);
                }
            }
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