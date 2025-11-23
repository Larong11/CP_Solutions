#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

string print1(int m) {
    int j = 0;
    string a;
    int x = m % 3;
    while (m - j >= 3) {
        if (x == 2) {
            a += "1 1 0 ";
        } else {
            a += "0 1 1 ";
        }
        j += 3;
    }
    if (m - j == 2) {
        a += "1 1 ";
    } else if (m - j == 1) {
        a += "0 ";
    }
    return a;
}

string print3(int m) {
    string s;
    for (int i = 0; i < m; i++) {
        s += "2 ";
    }
    s += "\n2 ";
    s += print1(m - 2);
    s += "2\n";
    for (int i = 0; i < m; i++) {
        s += "2 ";
    }
    s += "\n";
    return s;
}   

string print2(int m) {
    string s;
    int j = 0;
    int x = m % 3;
    while (m - j >= 3) {
        if (x == 2) {
            s += "2 2 1 ";
        } else {
            s += "1 2 2 ";
        }
        j += 3;
    }
    if (m - j == 2) {
        s += "2 2 ";
    } else if (m - j == 1) {
        s += "1";
    }
    s = s + "\n" + s + "\n";
    return s;
}

void solve() {
    int n, m;
    cin >> n >> m;
    if (m >= 3) {
        string s4, s3, s2, s1;
        s3 = print3(m);
        s2 = print2(m);
        s1 = print1(m) + "\n";
        if (n % 4 == 1) {
            s4 = s1 + s3;
        } else {
            s4 = s3 + s1;
        }
        int i = 0;
        while (n - i >= 4) {
            cout << s4;
            i += 4;
        }
        if (n - i == 3) {
            cout << s3;
        } else if (n - i == 2) {
            cout << s2;
        } else if (n - i == 1) {
            cout << s1;
        }
    } else {
        if (m == 2) {
            string s1 = "1 1\n";
            string s2 = "2 2\n2 2\n";
            string s3;
            if (n % 3 == 2) {
                s3 = s2 + s1;
            } else {
                s3 = s1 + s2;
            }
            int i = 0;
            while (n - i >= 3) {
                cout << s3;
                i += 3;
            }
            if (n - i == 2) {
                cout << s2;
            } else if (n - i == 1) {
                cout << s1;
            }
        } else {
            string s1 = "0\n";
            string s2 = "1\n1\n";
            string s3;
            if (n % 3 == 2) {
                s3 = s2 + s1;
            } else {
                s3 = s1 + s2;
            }
            int i = 0;
            while (n - i >= 3) {
                cout << s3;
                i += 3;
            }
            if (n - i == 2) {
                cout << s2;
            } else if (n - i == 1) {
                cout << s1;
            }
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

// 100 - 3:48:12