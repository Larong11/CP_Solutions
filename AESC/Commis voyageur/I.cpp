#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

int diviation(int &f, int &s, vector<int> &pos, vector<vector<pair<int, int>>> &g, vector<int> &used, int &cnt) {
    int newCnt = cnt;
    int x = pos[f];
    int y = pos[s];
    for (auto &[v, i] : g[x]) {
        if (used[i] == 1 and v != s) {
            newCnt--;
        }
    }
    for (auto &[v, i] : g[y]) {
        if (used[i] == 0) {
            newCnt++;
        }
    }
    return newCnt;
}

void swap(int &f, int &s, vector<int> &pos, vector<vector<pair<int, int>>> &g, vector<int> &used, int &cnt) {
    int x = pos[f];
    int y = pos[s];
    for (auto &[v, i] : g[x]) {
        used[i]--;
        if (used[i] == 0) {
            cnt--;
        }
    }
    for (auto &[v, i] : g[y]) {
        used[i]++;
        if (used[i] == 1) {
            cnt++;
        }
    }
    swap(pos[f], pos[s]);
}

double odd(int dDiviation, double T) {
    return exp(double(dDiviation) / T);
}
int ni(int l, int r, mt19937 &gen) {
    uniform_int_distribution<int> rngInt(l, r);
    return rngInt(gen);
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }
    vector<int> sent;
    for (int i = 0; i < n; i++) {
        sent.push_back(i);
    }
    random_device rng;
    sort(sent.begin(), sent.end(), [&](int &a, int &b) {
        if (g[a].size() > k) {
            return true;
        } else {
            return g[a].size() < g[b].size();
        }
    });
    vector<int> used(m, 0);
    int cnt = 0;
    for (int i = 0; i < k; i++) {
        for (auto [v, j] : g[sent[i]]) {
            used[j]++;
            if (used[j] == 1) {
                cnt++;
            }  
        }
    }
    int l = -1;  
    for (int i = 0; i < k; i++) {
        if (g[i].size() > k) {
            l++;
        }
    }
    mt19937 gen(rng());  
    uniform_real_distribution<double> rngDouble(0.0, 1.0);
    int numIter = 10e6;
    double T = 1;
    for (int iter = 0; iter < numIter; iter++) {
        int f = ni(l + 1, k - 1, gen);
        int s = ni(k, n - 1, gen);
        int newCnt = diviation(f, s, sent, g, used, cnt);
        double chance = odd(newCnt - cnt, T);
        if (rngDouble(gen) < chance) {
            swap(f, s, sent, g, used, cnt);  
        }
        if (cnt == m) {
            break;
        }
        T *= 0.99999;
    }
    if (cnt == m) {
        cout << "Yes" << '\n';
        for (int i = 0; i < k; i++) {
            cout << sent[i] + 1 << ' ';;
        }
    } else {
        cout << "No" << '\n';
    }
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