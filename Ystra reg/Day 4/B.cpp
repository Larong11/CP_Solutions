#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int INF = 1e9;

inline bool checkCell(int x, int y, int &d, vector<vector<pair<int, int>>> &teleports, vector<vector<int>> &dists, char &c, queue<pair<int, pair<int, int>>> &q) {
    if ((c == '.' or c == 'E' or c == 'S') and dists[y][x] > d + 1) {
        dists[y][x] = d + 1;
        q.push({d + 1, {x, y}});
    } else if (c == '#') {
        return true;
    } else if ('1' <= c and c <= '9') {
        if (dists[y][x] > d + 1) {
            dists[y][x] = d + 1;
            q.push({d + 1, {x, y}});
        }
        int num = c - '1';
        auto [ny, nx] = teleports[y][x];
        if (dists[ny][nx] > d + 1) {
            dists[ny][nx] = d + 1;
            q.push({d + 1, {nx, ny}});
        }
    }
    if (dists[y][x] < d + 1)  {
        return true;
    }
    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;
    int sx = -1, sy = -1, ex = -1, ey = -1;
    vector<vector<pair<int, int>>> teleports(n, vector<pair<int, int>>(m));
    vector<pair<int, int>> lol(10, {-1, -1}); 
    vector<vector<char>> field(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            field[i][j] = c;
            if (c == 'S') {
                sx = j;
                sy = i;
            } else if (c == 'E') {
                ex = j;
                ey = i;
            } else if ('1' <= c and c <= '9') {
                int num = c - '1';
                if (lol[num].first == -1) {
                    lol[num] = {i, j};
                } else {
                    teleports[i][j] = lol[num];
                    teleports[lol[num].first][lol[num].second] = {i, j};
                }
            }
        }
    }
    queue<pair<int, pair<int, int>>> q;
    vector<vector<int>> dists(n, vector<int>(m, INF));
    q.push({0, {sx, sy}});
    dists[sy][sx] = 0;
    while (!q.empty()) {
        auto [d, pos] = q.front();
        q.pop();
        int x = pos.first;
        int y = pos.second;
        for (int i = x + 1; i < m; i++) {
            if(checkCell(i, y, d, teleports, dists, field[y][i], q)) {
                break;
            }
        }
        for (int i = x - 1; i >= 0; i--) {
            if(checkCell(i, y, d, teleports, dists, field[y][i], q)) {
                break;
            }
        }
        for (int i = y - 1; i >= 0; i--) {
            if (checkCell(x, i, d, teleports, dists, field[i][x], q)) {
                break;
            }
        }
        for (int i = y + 1; i < n; i++) {
            if (checkCell(x, i, d, teleports, dists, field[i][x], q)) {
                break;
            }
        }
        bool d1 = true, d2 = true, d3 = true, d4 = true;
        for (int i = 1; i < max(n, m); i++) {
            if (d1 and y + i < n and x + i < m) {
                d1 = !checkCell(x + i, y + i, d, teleports, dists, field[y + i][x + i], q);
            } else {
                d1 = false;
            }
            if (d2 and y - i >= 0 and x + i < m) {
                d2 = !checkCell(x + i, y - i, d, teleports, dists, field[y - i][x + i], q);
            } else {
                d2 = false;
            }
            if (d3 and y - i >= 0 and x - i >= 0) {
                d3 = !checkCell(x - i, y - i, d, teleports, dists, field[y - i][x - i], q);
            } else {
                d3 = false;
            }
            if (d4 and y + i < n and x - i >= 0) {
                d4 = !checkCell(x - i, y + i, d, teleports, dists, field[y + i][x - i], q);
            } else {
                d4 = false;
            }
            if (!d1 and !d2 and !d3 and !d4) {
                break;
            }
        }
    }
    if (dists[ey][ex] == INF) {
        cout << -1 << '\n';
        return;
    }
    cout << dists[ey][ex] << '\n';
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

//100 - 2:22:00