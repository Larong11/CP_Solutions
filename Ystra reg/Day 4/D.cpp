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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    while (q--) {
        int c;
        cin >> c;
        if (c == 1) {
            int p;
            cin >> p;
            --p;
            a[p] = -a[p];
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            int ans = 0;
            int sum = 0;
            for (int i = l; i < r; i++) {
                if (a[i] == 1) {
                    sum++;
                    ans++;
                }
            }
            vector<int> taken;
            for (int i = l; i < r; i++) {
                if (a[i] != 1) {
                    int x = 0;
                    taken.push_back(i);
                    int rightSum = sum - taken.size();
                    int leftSum = 0;
                    bool flag = true;
                    for (int j = l; j < r; j++) {
                        if (a[j] == 1) {
                            leftSum++;
                            rightSum--;
                        }
                        else if (a[j] == -1) {
                            if (x < taken.size() and j == taken[x]) {
                                rightSum++;
                                leftSum--;
                                x++;
                            }
                        }
                        if (leftSum < 0 or rightSum < 0) {
                            flag = false;
                            break;
                        }
                    }
                    if (!flag) {
                        taken.pop_back();
                    }
                }
            }
            cout << ans + taken.size() << '\n';
        }
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