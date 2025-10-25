#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
// #define double ld
int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 6;

class intMod {
public:
    intMod(int val = 0) : val(val % MOD) {}
    intMod(ll val) : val(val % MOD) {}
    friend istream& operator>>(istream &in, intMod &data) {
        in >> data.val;
        data.val = data.val % MOD;
        return in;
    }
    friend ostream& operator<<(ostream &out, intMod data) {
        out << data.val;
        return out;
    }
    friend intMod operator+(const intMod &a, const intMod &b) {
        int sum = a.val + b.val;
        return (sum < MOD? sum : sum - MOD);
    }
    friend intMod operator-(const intMod &a, const intMod &b) {
        int dif = a.val - b.val;
        return (dif < 0? dif + MOD : dif);
    }
    friend intMod operator*(const intMod &a, const intMod &b) {
        ll product = (ll)a.val * b.val;
        return product % MOD;
    }
    friend bool operator==(const intMod &a, const intMod &b) {
        return (a.val == b.val);
    }

private:
    int val;
};

void solve() {
    int n, m;
    cin >> n >> m >> MOD;
    vector<vector<intMod>> a(n, vector<intMod>(m));
    for (auto &x : a[0]) {
        cin >> x;
    }
    for (int i = 0; i < m; i++) {
        a[1][i] = (i - 1 >= 0? a[0][i - 1] : 0) + a[0][i] + (i + 1 < m? a[0][i + 1] : 0);
    }
    for (int i = 2; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j - 1 >= 0 and j + 1 < m) {
                a[i][j] = 2 * a[i - 1][j - 1] + a[i - 1][j] + 2 * a[i - 1][j + 1] - (i > 2? 2 : 1) * a[i - 2][j];
            } else if (j - 1 >= 0) {
                a[i][j] = 2 * a[i - 1][j - 1] + a[i - 1][j];
            } else if (j + 1 < m) {
                a[i][j] = 2 * a[i - 1][j + 1] + a[i - 1][j];
            } else {
                a[i][j] = 2 * a[i - 1][j];
            }
        }
    }
    for (auto &i : a.back()) {
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
