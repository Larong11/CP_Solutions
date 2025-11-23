#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
// #define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-7;
const int SIGNES_AFTER_COMMA = 7;
const int INF = 1e10;

struct segment;

struct point {
    double x, y;
    point() : x(0), y(0) {}
    point(double x, double y) : x(x), y(y) {}
    point(point a, point b) : x(b.x - a.x), y(b.y - a.y) {}
    friend istream& operator>>(istream&in, point &data) {
        in >> data.x >> data.y;
        return in;
    }
    friend int operator^(point a, point b) {
        return a.x * b.y - b.x * a.y;
    }
    friend int operator*(point a, point b) {
        return a.x * b.x + a.y * b.y;
    }
    // bool isOnSegment(segment s) {
    //     point AB = point(s.a, s.b);
    //     point BA = point(s.b, s.a);
        
    //     point Ax = point(s.a, *this);
    //     point Bx = point(s.b, *this);

    //     return (AB ^ Ax) == 0 and (BA ^ Bx) == 0;
    // }
};

struct segment {
    point a, b;
    segment(point a, point b) : a(a), b(b) {}
};

double area (point a, point b, point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
 
bool intersect_1 (double a, double b, double c, double d) {
	if (a > b)  swap (a, b);
	if (c > d)  swap (c, d);
	return min(b,d) - max(a,c) >= eps;
}
 
bool intersect (point a, point b, point c, point d) {
    point ab(a, b);
    point cd(c, d);
    return (ab ^ point(a, c)) * (ab ^ point(a, d)) < 0.0 and
        (cd ^ point(c, a)) * (cd ^ point(c, b)) < 0.0;
}

bool check(double a, double h, vector<vector<point>> &ps) {
    point f1 = {-a, 0};
    point f2 = {0, h};
    point f3 = {a, 0};
    point f12 = point(f1, f2);
    point f23 = point(f2, f3);
    for (int i = 0; i < (int)ps.size(); i++) {
        // if (ps[i].back().y < f12.y / f12.x * (ps[i].back().x - f12.x) + point(f1, f2).y and
        //     ps[i].back().y < f23.y / f23.x * (ps[i].back().x - f23.x) - point(f2, f3).y) {
        //     return false;
        // }
        for (int j = 0; j < (int)ps[i].size() - 1; j++) {
            if (intersect(f1, f2, ps[i][j], ps[i][j + 1]) or intersect(f2, f3, ps[i][j], ps[i][j + 1])) {
                return false;
            }
            bool b1 = eps < f12.y / f12.x * (ps[i][j].x - f12.x) - ps[i][j].y;
            bool b2 = eps < f23.y / f23.x * (ps[i][j].x - f23.x) - ps[i][j].y;
            if (b1 and b2) {
                return false;
            }
        }
    }
    return true;
}

void solve() {
    int k;
    cin >> k;
    vector<vector<point>> a(k);
    double maxH = 0;
    vector<double> needToTry;
    needToTry.push_back(1);
    for (int i = 0; i < k; i++) {
        int n;
        cin >> n;
        for (int j = 0; j < n + 1; j++) {
            point x;
            cin >> x;
            a[i].push_back(x);
            maxH = max(x.y, maxH);
            if (j > 0) {
                if (a[i][j].y - a[i][j - 1].y != 0) {
                    needToTry.push_back(abs((a[i][j].x - a[i][j - 1].x) / (a[i][j].y - a[i][j - 1].y)));
                }
            }
        }
    }
    sort(needToTry.begin(), needToTry.end());
    needToTry.erase(unique(needToTry.begin(), needToTry.end()), needToTry.end());
    double L = 0, R = maxH + eps;
    double ans = 0;
    if (k <= 20) {
        for (auto &i : needToTry) {
            double l = L, r = R;
            double tani = i;
            while (r - l > eps) {
                double m = (l + r) / 2.0;
                double b = m * tani;
                double h = m;
                if (check(b, h, a)) {
                    ans = max(ans, b * h);
                    l = m;
                } else {
                    r = m;
                }
            }
        }
    } else {
        double l = L, r = R;
        while (r - l > eps) {
            double m = (l + r) / 2.0;
            double b = m;
            double h = m;
            if (check(b, h, a)) {
                ans = max(ans, b * h);
                l = m;
            } else {
                r = m;
            }
        }
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
    cin >> q;
#endif
    while (q--) {
        solve();
    }
}