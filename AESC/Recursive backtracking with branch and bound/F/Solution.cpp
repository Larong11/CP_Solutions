#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

int getRes(int x, int y, int dx, int dy, vector<vector<int>> &field) {
    int i = x + dx;
    int j = y + dy;
    while (i >= 0 and i < field.size() and j >= 0 and j < field.size()) {
        if (field[j][i] != -1) {
            return field[j][i];
        }
        i += dx;
        j += dy;
    }
    return -1;
}

int r_l_u_d[] = {1, -1, 0, 0, 0, 0, -1, 1};
// int r = getRes(x, y, 1, 0, field)
// int l = getRes(x, y, -1, 0, field)
// int u = getRes(x, y, 0, -1, field)
// int d = getRes(x, y, 0, 1, field)
int ur_dr_dl_ul[] = {1, 1, -1, -1, -1, 1, 1, -1};
// int ur = getRes(x, y, 1, -1, field);
// int dr = getRes(x, y, 1, 1, field);
// int dl = getRes(x, y, -1, 1, field);
// int ul = getRes(x, y, -1, -1, field);
int kon[] = {-2, -1, 1, 2, 2, 1, -1, -2, 1, 2, 2, 1, -1, -2, -2, -1};
// int f1 = field[y - 2][x + 1];
// int f2 = field[y - 1][x + 2];
// int f3 = field[y + 1][x + 2];
// int f4 = field[y + 2][x + 1];
// int f5 = field[y + 2][x - 1];
// int f6 = field[y + 1][x - 2];
// int f7 = field[y - 1][x - 2];
// int f8 = field[y - 2][x - 1];

void eat(int oldx, int oldy, int r, int i, int remain, vector<vector<int>> &field, vector<int> &deleted, vector<tuple<int, int, char>> &chess, vector<string> &ans, int &can);

void get(int remain, vector<vector<int>> &field, vector<int> &deleted, vector<tuple<int, int, char>> &chess, vector<string> &ans, int &can) {
    if (remain == 1) {
        for (auto &i : ans) {
            cout << i << '\n';
        }
        can = 1;
        return;
    }
    if (can) {
        return;
    }
    for (int i = 0; i < chess.size(); i++) {
        if (deleted[i]) {
            continue;
        }

        int x = get<1>(chess[i]);
        int y = get<0>(chess[i]);
        char c = get<2>(chess[i]);

        field[y][x] = -1;
        if (c == 'R' or c == 'Q') {
            for (int j = 0; j < 4; j++) {
                int r = getRes(x, y, r_l_u_d[j], r_l_u_d[j + 4], field);
                if (r != -1) {
                    eat(x, y, r, i, remain, field, deleted, chess, ans, can);
                }
            }
        }
        if (c == 'B' or c == 'Q') {
            for (int j = 0; j < 4; j++) {
                int r = getRes(x, y, ur_dr_dl_ul[j], ur_dr_dl_ul[j + 4], field);
                if (r != -1) {
                    eat(x, y, r, i, remain, field, deleted, chess, ans, can);
                }
            }
        }
        if (c == 'K') {
            for (int j = 0; j < 8; j++) {
                int ny = y + kon[j];
                int nx = x + kon[j + 8];
                if (ny < 0 or nx < 0 or ny >= 8 or nx >= 8) {
                    continue;
                }

                int r = field[ny][nx];
                if (r != -1) {
                    eat(x, y, r, i, remain, field, deleted, chess, ans, can);
                }
            }
        }
        field[y][x] = i;

        if (can) {
            break;
        }
    }
    return;
}

void eat(int oldx, int oldy, int r, int i, int remain, vector<vector<int>> &field, vector<int> &deleted, vector<tuple<int, int, char>> &chess, vector<string> &ans, int &can) {
    deleted[r] = true;
    int ny = get<0>(chess[r]);
    int nx = get<1>(chess[r]);
    get<0>(chess[i]) = ny;
    get<1>(chess[i]) = nx;
    field[ny][nx] = i;
    
    string add;
    add.push_back(oldx + 'a');
    add.push_back(8 - oldy + '0');
    add.push_back(':');
    add.push_back(nx + 'a');
    add.push_back(8 - ny + '0');
    ans.push_back(add);

    get(remain - 1, field, deleted, chess, ans, can);
    ans.pop_back();
    field[ny][nx] = r;
    get<0>(chess[i]) = oldy;
    get<1>(chess[i]) = oldx;
    deleted[r] = false;
}

void solve() {
    vector<vector<int>> field(8, vector<int>(8, -1));
    set<int> curChess;
    vector<tuple<int, int, char>> chess;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char c;
            cin >> c;
            if (c != '.') {
                field[i][j] = chess.size();
                chess.emplace_back(i, j, c);
            }
        }
    }
    vector<int> deleted(chess.size(), 0);
    vector<string> ans;
    int can = 0;
    get(chess.size(), field, deleted, chess, ans, can);
    if (!can) {
        cout << "NO SOLUTION" << '\n';
    }
}


signed main() {
    int q = 1;
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    cin >> q;
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(SIGNES_AFTER_COMMA);
    while (q--) {
        solve();
    }
}