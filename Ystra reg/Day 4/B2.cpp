#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int INF = 1e9;

struct node {
    int x, y, d;
    pair<int, int> dir;
};

void pushCell(int y, int x, int d, pair<int, int> dir, vector<vector<pair<int, int>>> &teleports, char c, queue<node> &q) {
    if (c == '#') {
        return;
    }
    if (c == '.' or c == 'E') {
        q.push({x, y, d, dir});
    } else if ('1' <= c and c <= '9') {
        q.push({x, y, d, dir});
        int num = c - '1';
        int nx, ny;
        if (teleports[num].front() == make_pair(y, x)) {
            nx = teleports[num].back().second;
            ny = teleports[num].back().first;
        } else {
            nx = teleports[num].front().second;
            ny = teleports[num].front().first;
        }
        q.push({nx, ny, d, {0, 0}});
    }
}

int solve(int n, int m, vector<vector<char>> &field) {
    int sx = -1, sy = -1, ex = -1, ey = -1;
    vector<vector<pair<int, int>>> teleports(9);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = field[i][j];
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
    q.push({sy, sx, 0, {0, 0}});
    while (!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        int d = q.front().d;
        auto dir = q.front().dir;
        q.pop();
        if (dists[y][x] < d) {
            continue;
        }
        dists[y][x] = d;
        if (dir.first != 0 or dir.second != 0) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (ny >= 0 and ny < n and nx >= 0 and nx < m) {
                pushCell(ny, nx, d, dir, teleports, field[ny][nx], q);
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
                    pushCell(ny, nx, d + 1, make_pair(j, i), teleports, field[ny][nx], q);
                }
            }
        }
    }
   return (dists[ey][ex] == INF? -1 : dists[ey][ex]);
}


inline bool checkCell(int x, int y, int &d, vector<vector<pair<int, int>>> &teleports, vector<vector<int>> &dists, char &c, queue<pair<int, pair<int, int>>> &q) {
    if ((c == '.' or c == 'E' or c == 'S') and dists[y][x] > d + 1) {
        dists[y][x] = d + 1;
        q.push({d + 1, {x, y}});
    } else if (c == '#') {
        return true;
    } else if ('1' <= c and c <= '9') {
        if (dists[y][x] > d + 1) {
            dists[y][x] = d + 1;
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
        if (dists[ny][nx] > d + 1) {
            dists[ny][nx] = d + 1;
            q.push({d + 1, {nx, ny}});
        }
    }
    return false;
}

int solve2(int n, int m, vector<vector<char>> &field) {
    int sx = -1, sy = -1, ex = -1, ey = -1;
    vector<vector<pair<int, int>>> teleports(9);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c = field[i][j];
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
        return -1;
    }
    return dists[ey][ex];
}



mt19937 rng(73);  // или любой другой сид
int ni(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

pair<pair<int, int>, vector<vector<char>>> gen() {
    int n = ni(3, 6);
    int m = ni(3, 6);
    vector<vector<char>> c(n, vector<char>(m, '.'));
    int sy = ni(0, n - 1), sx = ni(0, m - 1);
    int ey = ni(0, n - 1), ex = ni(0, m - 1);
    while (sy == ey and sx == ex) {
        ey = ni(0, n), ex = ni(0, m);
    }
    c[sy][sx] = 'S';
    c[ey][ex] = 'E';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (c[i][j] == '.') {
                int x = ni(-1, 4);
                if (x >= 3) {
                    c[i][j] = '#';
                }
            }
        }
    }
    return {{n, m}, c};
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
        auto x = gen();
        int f = solve(x.first.first, x.first.second, x.second);
        int s = solve2(x.first.first, x.first.second, x.second);
        if (f != s) {
            cout << x.first.first << ' ' << x.first.second << '\n';
            for (auto &vec : x.second) {
                for (auto &i : vec) {
                    cout << i;
                }
                cout << '\n';
            }
            return 0;
        } else {
            cout << q << ' ' << "OK" << '\n';
        }
    }
}