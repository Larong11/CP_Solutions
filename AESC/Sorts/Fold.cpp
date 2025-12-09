/*
СТРОИМ СТЕНУ РАБОТЯГИ!
█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█
█═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═█
█═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═█
█═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═█
█═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═█
█═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═█
█═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═█
█═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═█
█═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═╩═╦═█
█▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄█
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
#include <numeric>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <cmath>
#include <bitset>
#include <cassert>
#include <queue>
#include <stack>
#include <deque>
    
     
     
using namespace std;
template<typename T1, typename T2>inline void chkmin(T1 &x, T2 y) { if (x > y) x = y; }
template<typename T1, typename T2>inline void chkmax(T1 &x, T2 y) { if (x < y) x = y; }
/** Interface */
     
inline int readChar();
template <class T = int> inline T readInt(); 
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );
     
/** Read */
     
static const int buf_size = 4096;
     
inline int getChar() {
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len) {
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    }
    if (pos == len) {
        return -1;
    }
    return buf[pos++];
}
     
inline int readChar() {
    int c = getChar();
    while (c <= 32) {
        c = getChar();
    }
    return c;
}
     
template <class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}
     
/** Write */
     
static int write_pos = 0;
static char write_buf[buf_size];
     
inline void writeChar( int x ) {
    if (write_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = x;
}
     
template <class T> 
inline void writeInt( T x, char end ) {
    if (x < 0)
        writeChar('-'), x = -x;
     
    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n--)
        writeChar(s[n]);
    if (end)
        writeChar(end);
}
     
inline void writeWord( const char *s ) {     while (*s)
writeChar(*s++); }
     
struct Flusher {
    ~Flusher() {
        if (write_pos)
            fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
    }
} flusher;   
#define sz(c) (int)(c).size()
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define left left228
#define right right228
#define next next228
#define rank rank228
#define prev prev228
#define y1 y1228                                                         


inline void link(vector<int> &nextPrev, int a, int b) {
    nextPrev[a] ^= a ^ b;
    nextPrev[b] ^= a ^ b;
}


int main() {
    int n = readInt(), m = readInt();
    vector<int> top(n), bottom(n), nextPrev(n), h(n);
    for (int i = 0; i < n; i++) {
        top[i] = bottom[i] = i;
        h[i] = 1;
    }
    int l = 0;
    int r = n;
    bool reversed = false;
    for (int i = 0; i < m; i++) {
        int x = readInt();
        if (r - l - x <= x) {
            if (!reversed) {
                for (int i = 0; i < r - l - x; i++) {
                    link(nextPrev, top[l + x - i - 1], top[l + x + i]);
                    top[l + x - i - 1] = bottom[l + x + i];
                    h[l + x - i - 1] += h[l + x + i];
                }
                r = l + x;
            } else {
                for (int i = 0; i < r - l - x; i++) {
                    link(nextPrev, bottom[l + (r - l - x) + i], bottom[l + (r - l - x) - 1 - i]);
                    bottom[l + (r - l - x) + i] = top[l + (r - l - x) - 1 - i];
                    h[l + (r - l - x) + i] += h[l + (r - l - x) - 1 - i];
                }
                l = r - x;
            }
        } else {
            if (!reversed) {
                reversed = true;
                for (int i = 0; i < x; i++) {
                    link(nextPrev, top[l + x + i], top[l + x - 1 - i]);
                    top[l + x + i] = bottom[l + x - 1 - i];
                    h[l + x + i] += h[l + x - 1 - i];
                }
                l = l + x;
            } else {
                reversed = false;
                for (int i = 0; i < x; i++) {
                    link(nextPrev, bottom[l + (r - l - x) - i - 1], bottom[l + (r - l - x) + i]);
                    bottom[l + (r - l - x) - i - 1] = top[l + (r - l - x) + i];
                    h[l + (r - l - x) - i - 1] += h[l + (r - l - x) + i];
                }
                r -= x;
            }
        }
    }
    if (reversed) {
        swap(top, bottom);
        reverse(top.begin(), top.end());
        reverse(bottom.begin(), bottom.end());
        reverse(h.begin(), h.end());
        swap(l, r);
        l = n - l;
        r = n - r; 
    }
    int max = l;
    for (int i = l; i < r; i++) {
        if (h[i] > h[max]) {
            max = i;
        }
    }
    int x = bottom[max];
    int pr = x;
    while (x != top[max]) {
        writeInt(x + 1, ' ');
        int nx = nextPrev[x] ^ pr;
        pr = x;
        x = nx;
    }
    writeInt(top[max] + 1, '\n');
    for (int i = l; i < r; i++) {
        writeInt(bottom[i] + 1, ' ');
    }
    writeChar('\n');
    for (int i = l; i < r; i++) {
        writeInt(top[i] + 1, ' ');
    }
    writeChar('\n');
    return 0;
}