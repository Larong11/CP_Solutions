#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 2;

#define pii pair<int, int>

int operator*(pair<int, int> a, pair<int, int> b) {
    return a.first * b.second - b.first * a.second;
}
pair<int, int> operator-(pair<int, int> a, pair<int, int> b) {
    return {a.first - b.first, a.second - b.second};
}

bool check(pii &f1, pii &f2, pii &f3, pii &f4, pii &f5) {
    int s1 = (f2 - f1) * (f3 - f2);
    int s2 = (f3 - f2) * (f4 - f3);
    int s3 = (f4 - f3) * (f5 - f4);
    int s4 = (f5 - f4) * (f1 - f5);
    return (s1 <= 0 and s2 <= 0 and s3 <= 0 and s4 <= 0) or
           (s1 >= 0 and s2 >= 0 and s3 >= 0 and s4 >= 0);
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<pair<pair<int, int>, int>> a(n);
    int minPoint = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first.first >> a[i].first.second;
        if (a[minPoint].first.second > a[i].first.second) {
            minPoint = i;
        } else if (a[minPoint].first.second == a[i].first.second and a[minPoint].first.first < a[i].first.first) {
            minPoint = i;
        }
        a[i].second = i;
    }
    pair<int, int> minP = a[minPoint].first;
    sort(a.begin(), a.end(), [&](pair<pair<int, int>, int> &f, pair<pair<int, int>, int> &s) {
        double x = atan2(f.first.second - minP.second, f.first.first - minP.first);
        double z = atan2(s.first.second - minP.second, s.first.first - minP.first);
        if (abs(x - z) < eps){
            return f.first.first * f.first.first + f.first.second * f.first.second < s.first.first * s.first.first + s.first.second * s.first.second; 
        } else {
            return x < z;
        }
    });
    vector<int> rIdxs(n);
    for (int i = 0; i < n; i++) {
        rIdxs[a[i].second] = i;
    }
    double square = 0;
    for (int i = 0; i < n; i++) {
        square += a[i].first * a[(i + 1 >= n? 0 : i + 1)].first;
    }
    for (int i = 0; i < q; i++) {
        int idx, x, y;
        cin >> idx >> x >> y;
        idx = rIdxs[idx - 1];
        int minus1 = (idx - 1 + n) % n;
        int minus2 = (idx - 2 + n) % n;
        int next1 = (idx + 1) % n;
        int next2 = (idx + 2) % n;

        square -= a[minus2].first * a[minus1].first;
        square -= a[minus1].first * a[idx].first;
        square -= a[idx].first * a[next1].first;
        square -= a[next1].first * a[next2].first;
        
        a[idx].first = {x, y};
        
        if (check(a[minus2].first, a[minus1].first, a[idx].first, a[next1].first, a[next2].first)) {
            
        } else if (check(a[minus2].first, a[idx].first, a[minus1].first, a[next1].first, a[next2].first)) {
            swap(a[idx], a[minus1]);
            swap(rIdxs[a[idx].second], rIdxs[a[minus1].second]);
        } else if (check(a[minus2].first, a[minus1].first, a[next1].first, a[idx].first, a[next2].first)) {
            swap(a[idx], a[next1]);
            swap(rIdxs[a[idx].second], rIdxs[a[next1].second]);
        }
        
        square += a[minus2].first * a[minus1].first;
        square += a[minus1].first * a[idx].first;
        square += a[idx].first * a[next1].first;
        square += a[next1].first * a[next2].first;
        
        cout << abs(square / 2.0) << '\n';
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