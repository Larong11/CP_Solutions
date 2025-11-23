// #include "bits/stdc++.h"

// using namespace std;
// using ll = long long;
// using ld = long double;
// #define int ll
// #define double ld
// const int MOD = 1e9 + 7;
// const double eps = 1e-6;
// const int SIGNES_AFTER_COMMA = 9;
// const int INF = 1000;

// int getPrice(int a, int b) {
//     int x = 1e9;
//     int cnt = 0;
//     while (a / x == b / x) {
//         cnt++;
//         a -= int(a / x) * x;
//         b -= int(b / x) * x;
//         x /= 10;
//     }
//     return 10 - cnt;
// }

// void build(int tree[], int idxes[], int i, int l, int r, vector<int> &a) {
//     if (r - l == 1) {
//         tree[i] = a[l];
//         return;
//     }
//     int m = (l + r) / 2;
//     build(tree, idxes, i * 2, l, m, a);
//     build(tree, i * 2 + 1, m, r, a);
//     tree[i] = min(tree[i * 2], tree[i * 2 + 1]);
// }

// pair<int, int> getMin(int tree[], int i, int l, int r, int ql, int qr) {
    
// }

// void recalc(vector<int> &from, vector<int> &to, vector<int> &pricesFrom, vector<int> &pricesTo, vector<int> &pTo) {
//     for (int i = 0; i < (int)to.size(); i++) {
//         int minVal = INF;
//         int idxFrom = 0;
//         for (int j = 0; j < (int)from.size(); j++) {
//             int p = getPrice(to[i], from[j]);
//             if (pricesFrom[j] + p < minVal) {
//                 minVal = pricesFrom[j] + p;
//                 idxFrom = j;
//             }
//         }
//         pricesTo[i] = minVal;
//         pTo[i] = idxFrom;
//     }
// }

// void solve() {
//     int start, end;
//     cin >> start >> end;
//     vector<int> hanti, dubai, moscow, kali, paris;
//     hanti.push_back(start);
//     paris.push_back(end);
//     {
//         int k;
//         int x;
//         cin >> k;
//         for (int i = 0; i < k; i++) {
//             cin >> x;
//         }
//         cin >> k;
//         for (int i = 0 ; i < k; i++) {
//             cin >> x;
//             dubai.push_back(x);
//         }
//         cin >> k;
//         for (int i = 0; i < k; i++) {
//             cin >> x;
//             moscow.push_back(x);
//         }
//         cin >> k;
//         for (int i = 0; i < k; i++) {
//             cin >> x;
//             kali.push_back(x);
//         }
//         cin >> k;
//         for (int i = 0; i < k; i++) {
//             cin >> x;
//         }
//     }
//     vector<int> pricesToHanti(1, 0);
//     vector<int> pricesToDubai(dubai.size()), toDubai(dubai.size());
//     vector<int> pricesToMoscow(moscow.size()), toMoscow(moscow.size());
//     vector<int> pricesToKali(kali.size()), toKali(kali.size());
//     vector<int> pricesToParis(1), toParis(1);

//     recalc(hanti, dubai, pricesToHanti, pricesToDubai, toDubai);
//     recalc(dubai, moscow, pricesToDubai, pricesToMoscow, toMoscow);
//     recalc(moscow, kali, pricesToMoscow, pricesToKali, toKali);
//     recalc(kali, paris, pricesToKali, pricesToParis, toParis);

//     cout << pricesToParis[0] << ' ' << 5 << '\n';
//     vector<int> ans;
//     ans.push_back(paris[0]);
//     ans.push_back(kali[toParis[0]]);
//     ans.push_back(moscow[toKali[toParis[0]]]);
//     ans.push_back(dubai[toMoscow[toKali[toParis[0]]]]);
//     ans.push_back(start);
//     for (int i = 4; i >= 0; i--) {
//         int x = ans[i];
//         int cnt = 0;
//         while (x) {
//             x /= 10;
//             cnt++;
//         }
//         for (int j = 0; j < 10 - cnt - (ans[i] == 0); j++) {
//             cout << 0;
//         }
//         cout << ans[i] << '\n';
//     }
//     cout << '\n';
// }


// signed main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout << fixed << setprecision(SIGNES_AFTER_COMMA);
//     int q = 1;
// #ifdef LOCAL
//     freopen("in.txt", "r", stdin);
//     freopen("out.txt", "w", stdout);
//     cin >> q;
// #endif
//     while (q--) {
//         solve();
//     }
// }