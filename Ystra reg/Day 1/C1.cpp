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

void dfs(int u, int from, vector<vector<pair<int, int>>> &g, int d, vector<pair<int, int>> &p, vector<pair<node, node>> &dp, vector<int> &depth) {
    depth[u] = d;
    int ans1 = 0, ans2 = 0;
    int v1 = -1, v2 = -1;
    for (auto &[v, w] : g[u]) {
        if (v != from) {
            p[v] = {u, w};
            dfs(v, u, g, d + 1, p, dp, depth);
            auto sz = dp[v].first.val + w;
            if (sz > ans1) {
                ans2 = ans1;
                v2 = v1;
                ans1 = sz;
                v1 = v;
            } else if (sz > ans2) {
                ans2 = sz;
                v2 = v;
            }
        }
    }
    dp[u].first = {ans1, v1};
    dp[u].second = {ans2, v2};
}

int getAns(int u, int from, int b, vector<pair<node, node>> &dp, vector<pair<int, int>> &p) {
    int res = 0;
    if (from == -1) {
        res = dp[u].first.val + dp[u].second.val;
    } else {
        res = dp[u].first.to == from? dp[u].second.val : dp[u].first.val;
    }
    if (u != b) {
        res = max(res, (from == -1? dp[u].first.val : 0) + p[u].second + getAns(p[u].first, u, b, dp, p));
    }
    return res;
}

struct treeNode {
    int mx, push;
};

void push(vector<treeNode> &tree, int i, int l, int r) {
    int &push = tree[i].push;
    tree[i].mx += push;
    if (r - l > 1) {
        tree[i * 2].push += push;
        tree[i * 2 + 1].push += push;
    }
    push = 0;
}

void update(vector<treeNode> &tree, int i, int l, int r, int ql, int qr, int val) {
    if (l >= qr or r <= ql) {
        return;
    }
    push(tree, i, l, r);
    if (ql <= l and r <= qr) {
        tree[i].push += val;
        push(tree, i, l, r);
        return;
    }
    int m = (l + r) / 2;
    update(tree, i * 2, l, m, ql, qr, val);
    update(tree, i * 2 + 1, m, r, ql, qr, val);
    tree[i].mx = max(tree[i * 2].mx, tree[i * 2 + 1].mx);
}

void setVal(vector<treeNode> &tree, int i, int l, int r, int qi, int v) {
    if (l > qi or r <= qi) {
        return;
    }
    push(tree, i, l, r);
    if (r - l == 1) {
        tree[i].mx = v;
        return;
    }
    int m = (l + r) / 2;
    setVal(tree, i * 2, l, m, qi, v);
    setVal(tree, i * 2 + 1, m, r, qi, v);
    tree[i].mx = max(tree[i * 2].mx, tree[i * 2 + 1].mx);
}

int get(vector<treeNode> &tree, int i, int l, int r, int ql, int qr) {
    if (l >= qr or r <= ql) {
        return 0;
    }
    push(tree, i, l, r);
    if (ql <= l and r <= qr) {
        return tree[i].mx;
    }
    int m = (l + r) / 2;
    return max(get(tree, i * 2, l, m, ql, qr), get(tree, i * 2 + 1, m, r, ql, qr));
}

void fillAns(int u, int from, int d, int &maxD, vector<vector<pair<int, int>>> &g, vector<pair<node, node>> &dp, vector<vector<pair<int, int>>> &query, vector<int> &ans, vector<treeNode> &opt) { 
    int ans1 = dp[u].first.val;
    int ans2 = dp[u].second.val;
    for (auto &[db, i] : query[u]) {
        int ab = get(opt, 1, 0, maxD, db, d);
        ans[i] = max(ans1 + ans2, ans1 + ab);
    }
    for (auto &[v, w] : g[u]) {
        if (v == from) {
            continue;
        }
        int prevVal = get(opt, 1, 0, maxD, d, d + 1);
        if (v == dp[u].first.to) {
            setVal(opt, 1, 0, maxD, d, ans2 + w);
        } else {
            setVal(opt, 1, 0, maxD, d, ans1 + w);
        }
        update(opt, 1, 0, maxD, 0, d, w);
        fillAns(v, u, d + 1, maxD, g, dp, query, ans, opt);
        update(opt, 1, 0, maxD, 0, d, -w);
        setVal(opt, 1, 0, maxD, d, prevVal);
    }
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<pair<int, int>>> g(n);
    vector<pair<int, int>> p(n);
    vector<pair<node, node>> dp(n);
    vector<int> depth(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<vector<pair<int, int>>> query(n);
    vector<int> ans(q);
    dfs(0, -1, g, 0, p, dp, depth);
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        query[a].emplace_back(depth[b], i);
    }
    vector<treeNode> opt(4 * n);
    fillAns(0, -1, 0, n, g, dp, query, ans, opt);
    for (auto &i : ans) {
        cout << i << '\n';
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