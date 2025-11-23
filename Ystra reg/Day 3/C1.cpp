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
    vector<int> a(n);
    vector<int> prefSums(n, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = x;
        prefSums[i] = (i > 0? prefSums[i - 1] : 0) + x;
    }
    int sum = prefSums.back();
    int i = 0, j = 1, k = 2;
    int sum0 = a[i], sum1 = a[j];
    int dif = 1e18;
    int res0, res1, res2;
    for (i; i < n; i++) {
        while ((j > i or j + 2 < i) and sum0 + a[j] <= sum / 3) {
            sum0 += a[j];
            sum1 -= a[j];
            j++;
            if (j >= n) {
                j -= n;
            }
            if (k >= n) {
                k -= n;
            }
            if (j == k) {
                k++;
                sum1 += a[j];
            }
        }
        while ((k + 1 < i or k > i) and sum1 + a[k] <= sum / 3) {
            sum1 += a[k];
            k++;
            if (k >= n) {
                k -= n;
            }
        }
        int sum2 = sum - sum0 - sum1;
        int curdif = max(sum0, max(sum1, sum2)) - min(sum0, min(sum1, sum2));
        if (curdif < dif) {
            dif = curdif;
            res0 = i;
            res1 = j;
            res2 = k;
        }
        sum0 -= a[i];
        if (i + 1 == j) {
            sum1 -= a[i + 1];
            sum0 += a[i + 1];
            j++;
            if (j == k) {
                k++;
                sum1 += a[j];
            }
            if (j >= n) {
                j -= n;
            }
            if (k >= n) {
                k -= n;
            }
        }
    }
    i = 0, j = 1, k = 2;
    sum0 = a[i], sum1 = a[j];
    for (i; i < n; i++) {
        while ((j > i or j + 2 < i) and sum0 <= sum / 3) {
            sum0 += a[j];
            sum1 -= a[j];
            j++;
            if (j >= n) {
                j -= n;
            }
            if (k >= n) {
                k -= n;
            }
            if (j == k) {
                k++;
                sum1 += a[j];
            }
        }
        while ((k + 1 < i or k > i) and sum1 <= sum / 3) {
            sum1 += a[k];
            k++;
            if (k >= n) {
                k -= n;
            }
        }
        int sum2 = sum - sum0 - sum1;
        int curdif = max(sum0, max(sum1, sum2)) - min(sum0, min(sum1, sum2));
        if (curdif < dif) {
            dif = curdif;
            res0 = i;
            res1 = j;
            res2 = k;
        }
        sum0 -= a[i];
        if (i + 1 == j) {
            sum1 -= a[i + 1];
            sum0 += a[i + 1];
            j++;
            if (j == k) {
                k++;
                sum1 += a[j];
            }
            if (j >= n) {
                j -= n;
            }
            if (k >= n) {
                k -= n;
            }
        }
    }
    if (res1 < res0) {
        swap(res1, res0);
    }
    if (res2 < res0) {
        swap(res2, res0);
    }
    if (res2 < res1) {
        swap(res2, res1);
    }
    cout << dif << '\n';
    cout << res0 + 1 << ' ' << res1 + 1 << ' ' << res2 + 1 << '\n'; 
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