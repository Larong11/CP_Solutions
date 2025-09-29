#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

double odd(int dDiviation, double T) {
    return exp(double(dDiviation) / T);
}

int ni(int l, int r, mt19937 &gen) {
    uniform_int_distribution<int> rngInt(l, r);
    return rngInt(gen);
}

int diviation(int &f, int &s, vector<vector<int>> &a, int cnt, vector<int> used, int c) {
    used[f]--;
    if (used[f] == 0) {
        cnt--;
    }
    used[s]++;
    if (used[s] == 1) {
        cnt++;
    }
    for (int j = 0; j < a.size(); j++) {
        if (a[f][j] == c) {
            used[j]--;
            if (used[j] == 0) {
                cnt--;
            }
        }
        if (a[s][j] == c) {
            used[j]++;
            if (used[j] == 1) {
                cnt++;
            }
        }
    }
    return cnt;
}
void swap(int &f1, int &s1, vector<vector<int>> &a, int &cnt, vector<int> &used, vector<int> &pos, int c) {
    int f = pos[f1];
    int s = pos[s1];
    used[f]--;
    if (used[f] == 0) {
        cnt--;
    }
    used[s]++;
    if (used[s] == 1) {
        cnt++;
    }
    for (int j = 0; j < a.size(); j++) {
        if (a[f][j] == c) {
            used[j]--;
            if (used[j] == 0) {
                cnt--;
            }
        }
        if (a[s][j] == c) {
            used[j]++;
            if (used[j] == 1) {
                cnt++;
            }
        }
    }
    swap(pos[f1], pos[s1]);
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto &vec : a) {
        for (auto &i : vec) {
            cin >> i;
        }
    }
    vector<int> usedWhite(n, 0), usedBlack(n, 0);
    int cntWhite = 0, cntBlack = 0;
    vector<int> sentWhite, sentBlack;
    for (int i = 0; i < n; i++) {
        sentWhite.push_back(i);
        sentBlack.push_back(i);
    }
    for (int i = 0; i < k; i++) {
        usedWhite[i]++;
        usedBlack[i]++;
        if (usedWhite[i] == 1)
            cntWhite++;
        if (usedBlack[i] == 1)
            cntBlack++;
        for (int j = 0; j < n; j++) {
            if (a[i][j] == 1) {
                if (usedWhite[j] == 0) {
                    cntWhite++;
                }
                usedWhite[j]++;
            } else if (a[i][j] == 2) {
                if (usedBlack[j] == 0) {
                    cntBlack++;
                }
                usedBlack[j]++;
            }
        }
    }
    random_device rng;
    mt19937 gen(12837);
    uniform_real_distribution<double> rngDouble(0.0, 1.0);
    int numIter = 1e6;
    double T = 1;
    for (int iter = 0; iter < numIter; iter++) {
        int fWhite = ni(0, k - 1, gen);
        int sWhite = ni(k, n - 1, gen);
        int fBlack = ni(0, k - 1, gen);
        int sBlack = ni(k, n - 1, gen);

        int newWhite = diviation(sentWhite[fWhite], sentWhite[sWhite], a, cntWhite, usedWhite, 1);
        int newBlack = diviation(sentBlack[fBlack], sentBlack[sBlack], a, cntBlack, usedBlack, 2);

        double oddWhite = odd(newWhite - cntWhite, T);
        double oddBlack = odd(newBlack - cntBlack, T);

        if (oddWhite) {
            swap(fWhite, sWhite, a, cntWhite, usedWhite, sentWhite, 1);
        }
        if (oddBlack) {
            swap(fBlack, sBlack, a, cntBlack, usedBlack, sentBlack, 2);
        }
        T *= 0.999;
        if (cntBlack == n) {
            break;
        }
        if (cntWhite == n) {
            break;  
        }
    }   
    if (cntBlack == n) {
        cout << 2 << '\n';
        cout << k << '\n';
        for (int i = 0; i < k; i++) {
            cout << sentBlack[i] + 1 << ' ';
        }
    } else if (cntWhite == n) {
        cout << 1 << '\n';
        cout << k << '\n';
        for (int i = 0; i < k; i++) {
            cout << sentWhite[i] + 1 << ' ';
        }
    } else {
        cout << 0 << '\n';
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