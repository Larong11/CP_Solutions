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
    int n;
    cin >> n;
    vector<int> a(2 * n);
    for (auto &i : a) {
        cin >> i;
    }
    sort(a.begin(), a.end());
    vector<int> ansH, ansN;
    set<int> idxes;
    idxes.insert(a.size() - 1);
    set<pair<pair<int, int>, pair<int, int>>> dists;
    for (int i = 0; i < a.size() - 1; i++) {
        dists.insert(make_pair(make_pair(a[i + 1] - a[i], -(a[i + 1] + a[i])), make_pair(i, i + 1)));
        idxes.insert(i);
    }
    while (!dists.empty()) {
        auto [w, deleting] = *dists.begin();
        int f = deleting.first;
        int s = deleting.second;
        ansH.push_back(a[s]);
        ansN.push_back(a[f]);
        dists.erase(dists.begin());
        idxes.erase(s);
        auto nextSP = idxes.lower_bound(s);
        int nextS = -1;
        if (nextSP != idxes.end()) {
            nextS = *nextSP;
            dists.erase(dists.find(make_pair(make_pair(a[nextS] - a[s], -(a[nextS] + a[s])), make_pair(s, nextS))));
        }
        auto nextFP = idxes.find(f);
        int nextF = -1;
        if (nextFP != idxes.begin()) {
            nextFP--;
            nextF = *nextFP;
            dists.erase(dists.find(make_pair(make_pair(a[f] - a[nextF], -(a[f] + a[nextF])), make_pair(nextF, f))));
        }
        idxes.erase(f);
        if (nextS != -1 and nextF != -1) {
            dists.insert(make_pair(make_pair(a[nextS] - a[nextF], -(a[nextS] + a[nextF])), make_pair(nextF, nextS)));
        }
    }
    for (auto &i : ansH) {
        cout << i << ' ';
    }
    cout << '\n';
    for (auto &i : ansN) {
        cout << i << ' ';
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