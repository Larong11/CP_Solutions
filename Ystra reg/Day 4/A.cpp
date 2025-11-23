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
    int val, push;
};

vector<node> tree;

void build(int i, int l, int r, vector<int> &a) {
    if (r - l == 1) {
        tree[i] = {a[l], 0};
        return;
    }
    int m = (l + r) / 2;
    build (i * 2, l, m, a);
    build (i * 2 + 1, m, r, a);
    tree[i].val = tree[i * 2 + 1].val + tree[i * 2].val;
}

const int nul = -2e9;

void push(int i, int l, int r) {
    tree[i].val += tree[i].push * (r - l);
    int push = tree[i].push;
    tree[i].push = 0;
    if (r - l == 1) {
        return;
    }
    tree[i * 2].push += push;
    tree[i * 2 + 1].push += push;
}

void update(int i, int l, int r, int ql, int qr, int val) {
    if (l >= qr or r <= ql) {
        return;
    }
    if (ql <= l and r <= qr) {
        tree[i].push += val;
        return;
    }
    push(i, l, r);
    int m = (l + r) / 2;
    update(i * 2, l, m, ql, qr, val);
    update(i * 2 + 1, m, r, ql, qr, val);
    tree[i].val = tree[i * 2].val + tree[i * 2 + 1].val;
}

int get(int i, int l, int r, int qi) {
    if (l > qi or r <= qi) {
        return nul;
    }
    push(i, l, r);
    if (r - l == 1) {
        return tree[i].val;
    }
    int m = (l + r) / 2;
    int f = get(i * 2, l, m, qi);
    if (f == nul) {
        return get(i * 2 + 1, m, r, qi);
    }
    return f;
}

void undo(int &s, int &t, int qv, int prevv, int nextv, int &T) {
    if (prevv < nextv) {
        T += s * (nextv - prevv);
    } else {
        T -= t * (prevv - nextv);
    }
    if (qv < nextv) {
        T -= s * (nextv - qv);
    } else {
        T += t * (qv - nextv);
    }
}

void solve() {
    tree.clear();
    int n, q, s, t;
    cin >> n >> q >> s >> t;
    vector<int> a(n + 1);
    tree.resize(4 * a.size());
    for (auto &i : a) {
        cin >> i;
    }
    int T = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < a[i + 1]) {
            T -= s * (a[i + 1] - a[i]);
        } else {
            T += t * (a[i] - a[i + 1]);
        }
    }
    build(1, 0, n + 1, a);
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        r++;
        update(1, 0, n + 1, l, r, x);
        int L = get(1, 0, n + 1, l);
        int L1 = get(1, 0, n + 1, l - 1);
        int oldL = L - x;
        if (L1 < oldL) {
            T += s * (oldL - L1);
        } else {
            T -= t * (L1 - oldL);
        }
        if (L1 < L) {
            T -= s * (L - L1);
        } else {
            T += t * (L1 - L);
        }
        if (r < n + 1) {
            int R = get(1, 0, n + 1, r - 1);
            int R1 = get(1, 0, n + 1, r);
            int oldR = R - x;
            undo(s, t, R, oldR, R1, T);
        }
        cout << T << '\n';
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

//100 - 4:18:53
//Сразу после ушел посрать
// 4:08:03 - вернулся