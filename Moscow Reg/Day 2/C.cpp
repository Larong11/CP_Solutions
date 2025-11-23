#include "bits/stdc++.h"

#pragma GCC optimize("03")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,bmi2,fma")

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;
const int INF = 100;

void build(int tree[], int idxes[], int i, int l, int r, vector<int> &a) {
    if (r - l == 1) {
        tree[i] = a[l];
        idxes[i] = l;
        return;
    }
    int m = (l + r) / 2;
    build(tree, idxes, i * 2, l, m, a);
    build(tree, idxes, i * 2 + 1, m, r, a);
    if (tree[i * 2] < tree[i * 2 + 1]) {
        tree[i] = tree[i * 2];
        idxes[i] = idxes[i * 2];
    } else {
        tree[i] = tree[i * 2 + 1];
        idxes[i] = idxes[i * 2 + 1];
    }
}

pair<int, int> getMin(int tree[], int idxes[], int i, int l, int r, int ql, int qr) {
    if (ql <= l and r <= qr) {
        return {tree[i], idxes[i]};
    }
    if (r <= ql or l >= qr) {
        return {INF, l};
    }
    int m = (l + r) / 2;
    auto f = getMin(tree, idxes, i * 2, l, m, ql, qr);
    auto s = getMin(tree, idxes, i * 2 + 1, m, r, ql, qr);
    if (f.first < s.first) {
        return f;
    } else {
        return s;
    }
}

int getPrice(ll a, ll b) {
    ll x = 1e9;
    int cnt = 0;
    while (a / x == b / x) {
        cnt++;
        a -= ll(a / x) * x;
        b -= ll(b / x) * x;
        x /= 10;
    }
    return 10 - cnt;
}

void recalc(int tree[], int idxes[], vector<ll> &from, vector<ll> &to, vector<int> &prices, vector<int> &p) {
    for (int i = 0; i < (int)to.size(); i++) {
        int minim = INF;
        int idx = 0;
        {
            auto x = find(from.begin(), from.end(), to[i]);
            if (x != from.end()) {
                auto y = getMin(tree, idxes, 1, 0, from.size(), x - from.begin(), x - from.begin() + 1);
                minim = y.first;
                idx = y.second;
            }
        }
        ll d = 10;
        for (int k = 1; k <= 10; k++) {
            ll minX = ll(to[i] / d) * d, maxX = minX + d - 1;
            d *= 10;
            auto f = lower_bound(from.begin(), from.end(), minX);
            auto s = upper_bound(from.begin(), from.end(), maxX);
            s--;
            if (s < f or f < from.begin()) {
                continue;
            }
            int p1 = getPrice(to[i], *f);
            int p2 = getPrice(to[i], *s);
            if (p1 > k or p2 > k or (p1 < k and p2 < k)) {
                continue;
            }
            auto x = getMin(tree, idxes, 1, 0, from.size(), f - from.begin(), s - from.begin() + 1);
            if (x.first + k < minim) {
                minim = x.first + k;
                idx = x.second;
            }
            if (int(f - from.begin()) == 0 and int(s - from.begin()) == (int)from.size() - 1) {
                break;
            }
        }
        prices[i] = minim;
        p[i] = idx;
    }
}

void solve() {
    ll start, end;
    cin >> start >> end;
    vector<ll> dubai, moscow, kali;
    {
        int k;
        ll x;
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> x;
        }
        cin >> k;
        for (int i = 0 ; i < k; i++) {
            cin >> x;
            dubai.push_back(x);
        }
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> x;
            moscow.push_back(x);
        }
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> x;
            kali.push_back(x);
        }
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> x;
        }
    }
    sort(dubai.begin(), dubai.end());
    sort(moscow.begin(), moscow.end());
    sort(kali.begin(), kali.end());
    int tree[400'000];
    int idxes[400'000];
    vector<int> prices(dubai.size());
    vector<int> toMoscow(moscow.size()), toKali(kali.size()), toParis(1);
    for (int i = 0; i < (int)dubai.size(); i++) {
        prices[i] = getPrice(dubai[i], start);
    }
    memset(tree, INF, sizeof(int) * dubai.size() * 4);
    build(tree, idxes, 1, 0, dubai.size(), prices);
    prices.resize(moscow.size());

    recalc(tree, idxes, dubai, moscow, prices, toMoscow);
    memset(tree, INF, sizeof(int) * moscow.size() * 4);
    build(tree, idxes, 1, 0, moscow.size(), prices);
    prices.resize(kali.size());

    recalc(tree, idxes, moscow, kali, prices, toKali);
    memset(tree, INF, sizeof(int) * kali.size() * 4);
    build(tree, idxes, 1, 0, kali.size(), prices);
    prices.resize(1);
    vector<ll> paris(1, end);
    recalc(tree, idxes, kali, paris, prices, toParis);
    cout << prices[0] << ' ' << 5 << '\n';
    vector<ll> ans;
    ans.push_back(paris[0]);
    ans.push_back(kali[toParis[0]]);
    ans.push_back(moscow[toKali[toParis[0]]]);
    ans.push_back(dubai[toMoscow[toKali[toParis[0]]]]);
    ans.push_back(start);
    for (int i = 4; i >= 0; i--) {
        ll x = ans[i];
        int cnt = 0;
        while (x) {
            x /= 10;
            cnt++;
        }
        for (int j = 0; j < 10 - cnt - (ans[i] == 0); j++) {
            cout << 0;
        }
        cout << ans[i] << '\n';
    }
    cout << '\n';
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