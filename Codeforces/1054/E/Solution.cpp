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
    int n, k, l, r;
    cin >> n >> k >> l >> r;
    vector<int> a(n);
    int m = 0;
    {
        vector<int> u;
        for (auto &i : a) {
            cin >> i;
            u.push_back(i);
        }
        sort(u.begin(), u.end());
        u.erase(unique(u.begin(), u.end()), u.end());
        for (auto &i : a) {
            i = lower_bound(u.begin(), u.end(), i) - u.begin();
        }
        m = u.size();
    }
    vector<int> cnt(m);
    vector<int> cnt1(m);
    int c = 0;
    int L = 0, R = 0;
    int maxL = 0;
    int ans = 0;
    while (R < n) {
        if (cnt[a[R]] == 0) {
            c++;
        }
        cnt[a[R]]++;
        cnt1[a[R]]++;
        while (R - L + 1 > r or c > k) {
            if (cnt[a[L]] == 1) {
                c--;
            }
            cnt[a[L]]--;
            if (L >= maxL) {
                maxL++;
                cnt1[a[L]]--;
            }
            L++;
        }
        if (c == k) {
            if (R - L + 1 <= r and R - L + 1 >= l) {
                ans++;
                maxL = max(maxL, L);
                ans += maxL - L;
                int c1 = k;
                while (R - maxL + 1 >= l and c1 == k) {
                    if (cnt1[a[maxL++]]-- == 1) {
                        c1--;
                    }
                    if (c1 == k) {
                        ans++;
                    }
                }
                if (c1 != k) {
                    cnt1[a[--maxL]]++;
                }

            }
        }
        R++;
    }
    cout << ans << '\n';
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    cin >> q;
    while (q--) {
        solve();
    }
}