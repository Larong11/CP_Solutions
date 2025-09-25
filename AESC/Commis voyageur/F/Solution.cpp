#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

void print(vector<int> &pos) {
    int n = pos.size();
    vector<vector<char>> field(n, vector<char>(n, '.'));
    for (int i = 0; i < n; i++) {
        field[pos[i]][i] = '*';
    }
    for (auto &vec : field) {
        for (auto &c : vec) {
            cout << c << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int check(int &f, int &s, vector<int> &diag1, vector<int> &diag2, int &numDiag1, int &numDiag2, vector<int> &pos, int &n) {
    int newNum1 = numDiag1;
    int newNum2 = numDiag2;
    int yf = pos[f];
    int ys = pos[s];
    newNum1 -= (f + yf == s + ys and diag1[f + yf] == 2? 1 : (diag1[f + yf] == 1) + (diag1[s + ys] == 1));
    newNum1 += (f + ys == s + yf and diag1[f + ys] == 0? 1 : (diag1[f + ys] == 0) + (diag1[s + yf] == 0));
    newNum2 -= (n - f + yf == n - s + ys and diag2[n - f + yf - 1] == 2? 1 : (diag2[n - f + yf - 1] == 1) + (diag2[n - s + ys - 1] == 1));
    newNum2 += (n - f + ys == n - s + yf and diag2[n - f + ys - 1] == 0? 1 : (diag2[n - f + ys - 1] == 0) + (diag2[n - s + yf - 1] == 0));
    return newNum1 + newNum2;
}
const double k = 1/2.0;
double odd(int &iter, int &numIter) {
    // return 1;
    return exp(k * -double(iter) / double(numIter));
}

void swap(int &f, int &s, vector<int> &diag1, vector<int> &diag2, int &numDiag1, int &numDiag2, vector<int> &pos, int &n) {
    int yf = pos[f];
    int ys = pos[s];
    swap(pos[f], pos[s]);

    numDiag1 -= (f + yf == s + ys and diag1[f + yf] == 2? 1 : (diag1[f + yf] == 1) + (diag1[s + ys] == 1));
    numDiag1 += (f + ys == s + yf and diag1[f + ys] == 0? 1 : (diag1[f + ys] == 0) + (diag1[s + yf] == 0));
    numDiag2 -= (n - f + yf == n - s + ys and diag2[n - f + yf - 1] == 2? 1 : (diag2[n - f + yf - 1] == 1) + (diag2[n - s + ys - 1] == 1));
    numDiag2 += (n - f + ys == n - s + yf and diag2[n - f + ys - 1] == 0? 1 : (diag2[n - f + ys - 1] == 0) + (diag2[n - s + yf - 1] == 0));

    diag1[f + yf]--;
    diag1[f + ys]++;
    diag1[s + ys]--;
    diag1[s + yf]++;

    diag2[n - f + yf - 1]--;
    diag2[n - f + ys - 1]++;
    diag2[n - s + ys - 1]--;
    diag2[n - s + yf - 1]++;
}

void solve() {
    int n;
    cin >> n;
    vector<int> diag1(2 * n - 1, 0), diag2(2 * n - 1, 0);
    // int numDiag1 = 1;
    // int numDiag2 = 5;
    // for (int i = 0; i < n; i++) {
    //     int x = i, y = n - i - 1;
    //     diag1[x + y]++;
    //     diag2[n - x + y - 1]++;
    // }
    vector<int> positions(n);
    for (int i = 0; i < n; i++) {
        positions[i] = n - i - 1;
    }
    int numDiag1 = 0;
    int numDiag2 = 0;
    for (int i = 0; i < n; i++) {
        numDiag1 += diag1[i + positions[i]] == 0;
        diag1[i + positions[i]]++;
        numDiag2 += diag2[n - i + positions[i] - 1] == 0;
        diag2[n - i + positions[i] - 1]++;
    }
    int numIter = 1e5;
    random_device rng;
    mt19937 gen(rng());
    uniform_real_distribution<double> rngDouble(0.0, 1.0);
    uniform_int_distribution<int> rngInt(0, n - 1);
    int iter = 0;
    while (numDiag1 + numDiag2 != 2 * n) {
        iter++;
        int f = rngInt(gen);
        int s = rngInt(gen);
        if (f == s) {
            iter--;
            continue;
        }
        double dd = odd(iter, numIter), DD = rngDouble(gen);
        if ((check(f, s, diag1, diag2, numDiag1, numDiag2, positions, n) > numDiag1 + numDiag2) or dd > DD) {
            swap(f, s, diag1, diag2, numDiag1, numDiag2, positions, n);
        }        
    }
    for (auto &i : positions) {
        cout << n - i << ' ';
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