#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int p = 26;
const int SIGNES_AFTER_COMMA = 6;

class intMod {
public:
    intMod(int val = 0) : val(val) {}
    intMod(ll val) : val(val) {}

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

vector<intMod> powers;
vector<intMod> hashes;

intMod getHash(int l, int r) {
    return hashes[r] - hashes[l] * powers[r - l];
}

void solve() {
    string s, t;
    cin >> s >> t;
    powers.emplace_back(1);
    for (int i = 1; i <= s.size(); i++) {
        powers.emplace_back(powers.back() * p);
    }
    intMod hash = 0;
    for (int i = 0; i < t.size(); i++) {
        hash = hash * p + (t[i] - 'a');
    }
    hashes.emplace_back(0);
    for (int i = 0; i < s.size(); i++) {
        hashes.emplace_back(hashes.back() * p + (s[i] - 'a'));
    }
    for (int i = 0; i <= s.size() - t.size(); i++) {
        if (getHash(i, i + t.size()) == hash) {
            cout << i << ' ';
        }
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
