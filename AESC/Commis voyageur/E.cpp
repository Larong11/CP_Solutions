#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

double odd(int dDiviation, double T) {
    return exp(double(dDiviation) / T);
}

double dst(pair<double, double> a, pair<double, double> b) {
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

double cntDistance(int &f, int &s, vector<pair<double, double>> &a, double dist) {
    dist -= (f + 1 < a.size() ? dst(a[f], a[f + 1]) : 0) + (f - 1 >= 0? dst(a[f - 1], a[f]) : 0) + (s + 1 < a.size() ? dst(a[s], a[s + 1]) : 0) + (s - 1 >= 0? dst(a[s - 1], a[s]) : 0);
    dist += (s - 1 >= 0 ? dst(a[s - 1], a[f]) : 0) + (s + 1 < a.size() ? dst(a[f], a[s + 1]) : 0) + (f - 1 >= 0? dst(a[f - 1], a[s]) : 0) + (f + 1 < a.size() ? dst(a[s], a[f + 1]) : 0);
    return dist;
}

void swap(int &f1, int &s1, vector<pair<double, double>> &a, double &dist, vector<int> &pos) {
    int f = pos[f1];
    int s = pos[s1];
    dist -= (f + 1 < a.size() ? dst(a[f], a[f + 1]) : 0) + (f - 1 >= 0? dst(a[f - 1], a[f]) : 0) + (s + 1 < a.size() ? dst(a[s], a[s + 1]) : 0) + (s - 1 >= 0? dst(a[s - 1], a[s]) : 0);
    dist += (s - 1 >= 0 ? dst(a[s - 1], a[f]) : 0) + (s + 1 < a.size() ? dst(a[f], a[s + 1]) : 0) + (f - 1 >= 0? dst(a[f - 1], a[s]) : 0) + (f + 1 < a.size() ? dst(a[s], a[f + 1]) : 0);
    swap(pos[f], pos[s]);
}

void solve() {
    int n;
    cin >> n;
    vector<pair<double, double>> a(n);
    for (auto &i : a) {
        cin >> i.first >> i.second;
    }
    double dist = 0;
    vector<int> pos;
    for (int i = 0; i < n; i++) {
        if (!pos.empty()) {
            dist += dst(a[i], a[pos.back()]);
        }
        pos.push_back(i);
    }
    random_device rnd;
    mt19937 gen(rnd());
    uniform_int_distribution<int> rngInt(0, n - 1);
    uniform_real_distribution<double> rngDouble(0.0, 1.0);
    int numIter = 1e6;
    double T = 1;
    for (int iter = 0; iter < numIter; iter++) {
        int f = rngInt(gen);
        int s = rngInt(gen);
        while (f == s) {
            s = rngInt(gen);
        }
        double newDistance = cntDistance(pos[f], pos[s], a, dist);
        double chance = odd(dist - newDistance, T);
        if (chance) {
            swap(f, s, a, dist, pos);
        }
        T *= 0.999999;
    }
    for (auto &i : pos) {
        cout << i + 1 << ' ';
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