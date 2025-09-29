#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

int cntDiviation(int &f, int &s, int nk, int &diviation, int &targetSum, vector<int> &sums, vector<int> &a) {
    int newDiviation = diviation;
    newDiviation -= abs(targetSum - sums[f / nk]);
    newDiviation -= abs(targetSum - sums[s / nk]);
    newDiviation += abs(targetSum - (sums[f / nk] - a[f] + a[s]));
    newDiviation += abs(targetSum - (sums[s / nk] - a[s] + a[f]));
    return newDiviation;
}

void swap(int &f, int &s, int nk, int &diviation, int &targetSum, vector<int> &sums, vector<int> &a) {
    diviation -= abs(targetSum - sums[f / nk]);
    diviation -= abs(targetSum - sums[s / nk]);
    sums[f / nk] -= a[f] - a[s]; 
    sums[s / nk] -= a[s] - a[f];
    diviation += abs(targetSum - sums[f / nk]);
    diviation += abs(targetSum - sums[s / nk]);
    swap(a[f], a[s]);
}

double odd(int &dDiviation, double T) {
    return exp(double(dDiviation) / T);
}
int ni(int l, int r, mt19937 &gen) {
    uniform_int_distribution<int> rngInt(l, r);
    return rngInt(gen);
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> sums(k);
    int targetSum = (n + 1) * n / 2;
    if (targetSum % k != 0) {
        cout << 0 << '\n';
        return;
    }
    targetSum /= k;
    int diviation = 0;
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
      
    random_device rng;
    mt19937 gen(12837);
    uniform_real_distribution<double> rngDouble(0.0, 1.0);
    uniform_int_distribution<int> rngInt(0, k - 1), rngInt2(0, n / k - 1);
    shuffle(a.begin(), a.end(), rng);
    for (int i = 0; i < n; i++) {
        sums[i / (n / k)] += a[i];
    }
    for (int i = 0; i < k; i++) {
        diviation += abs(sums[i] - targetSum);
    }
    int numIter = 2e6;
    if (k != 1) {
        double T = 1;
        for (int iter = 0; iter < numIter; iter++) {
            int f = ni(0, k - 2, gen);
            int s = ni(f + 1, k - 1, gen);
            int fi = f;
            int is = s;
            f = f * (n / k) + rngInt2(gen);
            s = s * (n / k) + rngInt2(gen);
            double randD = rngDouble(gen);
            int dDiviation = diviation - cntDiviation(f, s, n / k, diviation, targetSum, sums, a);
            double curOdd = odd(dDiviation, T);
            if (randD < curOdd) {
                swap(f, s, n / k, diviation, targetSum, sums, a);
            }
            T *= 0.999;
        }
    }
    if (diviation != 0) {
        cout << 0 << '\n';
    } else {
        int cur = 0;
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
            if ((i + 1) / (n / k) > cur) {
                cout << '\n';
                cur++;
            }
        }
        cout << endl;
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