#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

struct node {
    int val, to;
};

int cntDepth(int u, int from, vector<vector<int>> &g, vector<pair<node, node>> &maxDepth) {
    int x = 0;
    int len1 = 0, len2 = 0;
    int to1 = -1, to2 = -1;
    for (int &v : g[u]) {
        if (v == from) {
            continue;
        }
        int x = cntDepth(v, u, g, maxDepth) + 1;
        if (x > len1) {
            len2 = len1;
            to2 = to1;
            len1 = x;
            to1 = v;
        } else if (x > len2) {
            len2 = x;
            to2 = v;
        }
    }
    maxDepth[u].first = {len1, to1};
    maxDepth[u].second = {len2, to2};
    return maxDepth[u].first.val;
}

bool cntMaxDistAndCheckPossible(int u, int from, int distFrom, int &k, vector<vector<int>> &g, vector<pair<node, node>> &maxDepth, vector<int> &maxDist) {
    if (maxDepth[u].first.val + maxDepth[u].second.val > k) {
        return false;
    }
    if (maxDepth[u].first.val + distFrom > k) {
        return false;
    }
    maxDist[u] = max(distFrom, maxDepth[u].first.val);
    bool possible = true;
    for (auto &v : g[u]) {
        if (v == from) {
            continue;
        }
        if (v == maxDepth[u].first.to) {
            possible &= cntMaxDistAndCheckPossible(v, u, max(distFrom + 1, maxDepth[u].second.val + 1), k, g, maxDepth, maxDist);
        } else {
            possible &= cntMaxDistAndCheckPossible(v, u, max(distFrom + 1, maxDepth[u].first.val + 1), k, g, maxDepth, maxDist);
        }
    }
    return possible;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g1(n), g2(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g1[u].push_back(v);
        g1[v].push_back(u);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g2[u].push_back(v);
        g2[v].push_back(u);
    }
    vector<pair<node, node>> maxDepth1(n), maxDepth2(n);
    cntDepth(0, -1, g1, maxDepth1);
    cntDepth(0, -1, g2, maxDepth2);
    vector<int> maxDist1(n), maxDist2(n);
    bool possible = true;
    possible &= cntMaxDistAndCheckPossible(0, -1, 0, k, g1, maxDepth1, maxDist1);
    possible &= cntMaxDistAndCheckPossible(0, -1, 0, k, g2, maxDepth2, maxDist2);
    if (!possible) {
        cout << 0 << '\n';
    } else {
        int ans = 0;
        sort(maxDist2.begin(), maxDist2.end());
        for (int i = 0; i < n; i++) {
            auto x = upper_bound(maxDist2.begin(), maxDist2.end(), k - 1 - maxDist1[i]);
            if (x == maxDist2.begin()) {
                continue;
            } else {
                ans += x - maxDist2.begin();
            }
        }
        cout << ans << '\n';
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
#endif
    cin >> q;
    while (q--) {
        solve();
    }
}