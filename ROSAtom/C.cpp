#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define double ll
#define double ld
const double MOD = 1e9 + 7;
const double eps = 1e-6;
const double SIGNES_AFTER_COMMA = 9;

struct field {
    double E, t, type;
    field(double E, double t, double type) : E(E), t(t), type(type) {}
    field() {}
    friend bool operator<(field a, field b) {
        if (a.t != b.t) {
            return a.t < b.t;
        } else {
            return a.type < b.type;
        }
    }
};

void solve() {
    double T;
    cin >> T;
    vector<field> fields;
    for (double i = 0; i < T; i++) {
        double start, finish, e;
        cin >> start >> finish >> e;
        fields.emplace_back(e, start, 1);
        fields.emplace_back(e, finish, 0);
    }
    double m, q;
    cin >> q >> m;
    double Q;
    cin >> Q;
    vector<pair<double, double>> xs(Q);
    for (double i = 0; i < Q; i++) {
        double t;
        cin >> t;
        xs[i] = {t, i};
    }
    sort(xs.begin(), xs.end());
    sort(fields.begin(), fields.end());
    vector<double> ans(Q);
    double t = 0, x = 0, v = 0, a = 0;
    double last = 0;
    for (double i = 0; i < 2 * T; i++) {
        double dt = double(fields[i].t) - t;
        double newX = x + dt * v + dt * dt * a / 2.0;
        while (last < xs.size() and xs[last].first <= newX) {
            if (xs[last].first == 0) {
                ans[xs[last].second] = 0;
                last++;
                continue;
            }
            if (a != 0) {
                double Dt = (-v + sqrt(v * v - 2.0 * a * double(x - xs[last].first))) / a;
                ans[xs[last].second] = t + Dt;
            }
            else { 
                ans[xs[last].second] = t + double(xs[last].first - x) / v;
            }
            last++;
        }
        t = fields[i].t;
        x = newX;
        v += a * dt;
        a = a + (fields[i].E * (fields[i].type == 1? 1.0 : -1.0) * q / m);
    }
    while (last < xs.size()) {
        ans[xs[last].second] = t + double(xs[last].second - x) / v;
        last++;
    }
    for (auto &i : ans) {
        cout << i << '\n';
    }
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    double q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
#endif
    while (q--) {
        solve();
    }
}