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

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    vector<ll> prefSums(n, 0);
    for (int i = 0; i < n; i++) {
        prefSums[i] = a[i] + (i > 0? prefSums[i - 1] : 0);
    }
    int res1 = 0, res2 = 0, res3 = 0;
    ll dif = 1e18;
    ll sum1, sum2, sum3;
    ll bigSum = prefSums.back();
    for (int i = 0; i < n - 2; i++) {
        int l = lower_bound(prefSums.begin() + i + 1, prefSums.end(), (i > 0? prefSums[i - 1] : 0) + prefSums.back() / 3 - dif) - prefSums.begin() - 1, r = l + 1;
        sum1 = 0;
        if (a[i] == 0) {
            continue;
        }
        for (int j = l + 1; j < n - 1; j++) {
            sum1 = prefSums[j - 1] - (i > 0? prefSums[i - 1] : 0);
            if (a[j - 1] == 0) {
                continue;
            }
            if ((bigSum - sum1) / 2 - sum1 < -dif) {
                continue;
            }
            if (sum1 - (bigSum - sum1) / 2 > dif) {
                break;
            }
            sum2 = prefSums[l] - prefSums[j - 1];
            sum3 = bigSum - sum2 - sum1;
            while (r < n - 1 and sum2 + a[r] < sum3) {
                l++;
                r++;
                sum2 += a[l];
                sum3 -= a[l];
            }
            if (l != j - 1) {
                sum2 = prefSums[l] - prefSums[j - 1];
                sum3 = bigSum - sum1 - sum2;
                ll curdif = max(sum1, max(sum2, sum3)) - min(sum1, min(sum2, sum3));
                if (dif > curdif) {
                    res1 = i + 1;
                    res2 = j + 1;
                    res3 = l + 2;
                    dif = curdif;
                }
            }
            if (r != n - 1) {
                sum2 = prefSums[r] - prefSums[j - 1];
                sum3 = bigSum - sum1 - sum2;
                ll curdif = max(sum1, max(sum2, sum3)) - min(sum1, min(sum2, sum3));
                if (dif > curdif) {
                    res1 = i + 1;
                    res2 = j + 1;
                    res3 = r + 2;
                    dif = curdif;
                }
            }

        }
    }
    cout << dif << '\n';
    cout << res1 << ' ' << res2 << ' ' << res3 << '\n';
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

//32 - 2:58:32