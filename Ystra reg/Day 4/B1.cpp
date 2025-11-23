#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;


const int INF = 1e9;

struct node {
    int x, y, d;
    pair<int, int> dir;
    friend bool operator<(node &a, node &b) {
        return a.d < b.d;
    }
};

void pushCell(int y, int x, int d, pair<int, int> dir, vector<vector<pair<int, int>>> &teleports, char c, queue<node> &q, vector<vector<int>> &dists) {
    if (c == '#') {
        return;
    }
    if (c == '.' or c == 'E') {
        if (dists[y][x] > d) {
            dists[y][x] = d;
            q.push({x, y, d, dir});
        }
    } else if ('1' <= c and c <= '9') {
        if (dists[y][x] > d) {
            dists[y][x] = d;
            q.push({x, y, d, dir});
        }
        int num = c - '1';
        int nx, ny;
        if (teleports[num].front() == make_pair(y, x)) {
            nx = teleports[num].back().second;
            ny = teleports[num].back().first;
        } else {
            nx = teleports[num].front().second;
            ny = teleports[num].front().first;
        }
        if (dists[ny][nx] > d) {
            dists[ny][nx] = d;
            q.push({nx, ny, d, dir});
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    int sx = -1, sy = -1, ex = -1, ey = -1;
    vector<vector<pair<int, int>>> teleports(9);
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
                teleports[c - '1'].emplace_back(i, j);
            }
        }
    }
    vector<vector<int>> dists(n, vector<int>(m, INF));
    queue<node> q;
    q.push({sx, sy, 0, {0, 0}});
    dists[sy][sx] = 0;
    while (!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        int d = q.front().d;
        auto dir = q.front().dir;
        q.pop();
        if (dir.first != 0 or dir.second != 0) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (ny >= 0 and ny < n and nx >= 0 and nx < m) {
                pushCell(ny, nx, d, dir, teleports, field[ny][nx], q, dists);
            }
        }
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == j and i == 0) {
                    continue;
                }
                if (dir.second == i and dir.first == j) {
                    continue;
                }
                int ny = y + i;
                int nx = x + j;
                if (ny >= 0 and ny < n and nx >= 0 and nx < m) {
                    pushCell(ny, nx, d + 1, make_pair(j, i), teleports, field[ny][nx], q, dists);
                }
            }
        }
    }
    cout << (dists[ey][ex] == INF? -1 : dists[ey][ex]) << '\n';
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