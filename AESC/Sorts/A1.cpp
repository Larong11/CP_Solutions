#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
// #define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;



struct Node {
    ll power, coef;
    Node *next;
    Node() : power(0), coef(0), next(nullptr) {}
    Node(ll power, ll coef) : power(power), coef(coef), next(nullptr) {}
};

void del(Node *head) {
    while (head) {
        auto x = head;
        head = head->next;
        delete(x);
    }
}

struct DB {
    ll idx;
    Node *cur;
    DB *next;
    DB() : idx(-1), cur(nullptr), next(nullptr) {}
    DB(ll idx, Node *cur) : idx(idx), cur(cur), next(nullptr) {}
    int add(ll idx, Node *cur) {
        auto x = this;
        while (x->next and x->idx != idx) {
            x = x->next;
        }
        if (x->idx == idx) {
            return 1;
        } else {
            x->next = new DB(idx, cur);
        }
    }
    int delDB(ll idx) {
        auto x = this;
        auto prev = this;
        while (x->next and x->idx != idx) {
            prev = x;
            x = x->next;
        }
        if (x->idx == idx) {
            prev->next = x->next;
            del(x->cur);
            delete(x);
        } else {
            return 1;
        }
    }
};

void reverse(Node *&head) {
    if (!head) {
        return;
    }
    Node *prev = nullptr, *cur = head, *next = head->next;
    while (next != nullptr) {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = next->next;
    }
    cur->next = prev;
    head = cur;
}

void reset(ll &power, ll &coef, ll &plus, bool &isPower) {
    power = 0;
    coef = 0;
    plus = 1;
    isPower = false;
}


Node *read() {
    Node *head = new Node();
    Node *last = head;
    ll power, coef, plus;
    bool isPower;
    reset(power, coef, plus, isPower);
    char prev = '#';
    char currentVar = '.';

    char c;
    while (cin >> c and c != '.') {
        if (c == ' ' or c == '.') {
            continue;
        }
        if (c == '^') {
            if (prev != currentVar) {
                del(head);
                return nullptr;
            }
            if (isPower) {
                del(head);
                return nullptr;
            }
            isPower = true;
            power = 0;
        } 
        else if (c == '-' or c == '+') {
            if (prev != '#') {
                if (power == 0 and coef == 0) {
                    del(head);
                    return nullptr;
                }
                if (isPower and power == 0) {
                    del(head);
                    return nullptr;
                }
                last->next = new Node(power, plus * coef);
                last = last->next;
                reset(power, coef, plus, isPower);
            }   
            plus = (c == '+'? 1 : -1);
        } 
        else if ('a' <= c and c <= 'z') {
            if (currentVar == '.') {
                currentVar = c;
            }
            if (c != currentVar) {
                del(head);
                return nullptr;
            }
            if (power > 0) {
                del(head);
                return nullptr;
            }
            power = 1;
            coef = max(coef, 1ll);
        } else if ('0' <= c and c <= '9') {
            if (prev == currentVar) {
                del(head);
                return nullptr;
            }
            if (isPower) {
                power = power * 10 + (c - '0');
            } else {
                coef = coef * 10 + (c - '0');
            }
        } else {
            del(head);
            return nullptr;
        }
        prev = c;
    }
    if (prev == '+' or prev == '-') {
        del(head);
        return nullptr;
    }
    last->next = new Node(power, plus * coef);
    reset(power, coef, plus, isPower);
    return head;
}

void push_back(Node *&l, Node *&lT, Node *cur, int &sorted) {
    if (!cur) {
        return;
    }
    if (l) {
        if (cur->power > lT->power) {
            sorted = (sorted == 0 or sorted == 1? 1 : -2);
        } else if (cur->power < lT->power) {
            sorted = (sorted == 0 or sorted == -1? -1 : -2);
        }
        lT->next = cur;
        lT = lT->next;
    } else {
        l = cur;
        lT = cur;
    }
}

template <typename T>
void merge(T *&l, T *&lt, T *&r, T *&rt) {
    if (!l) {
        l = r;
        lt = rt;
        return;
    }
    if (r) {
        lt->next = r;
        lt = rt;
    }
}

Node* sort(Node *&head, int &sz, int sorted = 0) {
    if (!head) {
        return nullptr;
    }
    if (sorted == -2 or sorted == 0) {
        Node *l = nullptr, *b = nullptr, *e = nullptr;
        Node *lT = nullptr, *bT = nullptr, *eT = nullptr;
        Node *next = head;
        int cnt = 0;
        int partition = head->power;
        int sortedL = 0, sortedB = 0, sortedE = 0;
        while (next) {
            sz++;
            auto cur = next;
            next = next->next;
            cur->next = nullptr;
            if (cur->power < partition) {
                push_back(l, lT, cur, sortedL);
            } else if (cur->power > partition) {
                push_back(b, bT, cur, sortedB);
            } else {
                push_back(e, eT, cur, sortedE);
            }
        }
        lT = sort(l, sz, sortedL);
        bT = sort(b, sz, sortedB);
        merge(e, eT, l, lT);
        merge(b, bT, e, eT);
        head = b? b : (e? e : l);
        return bT;
    } else if (sorted == 1) {
        reverse(head);
        Node *t = head;
        while (t->next) {
            t = t->next;
        }
        return t;
    } else {
        Node *t = head;
        while (t->next) {
            t = t->next;
        }
        return t;
    }
}

void push_back(DB *&l, DB *&lT, DB *cur) {
    if (!cur) {
        return;
    }
    if (l) {
        lT->next = cur;
        lT = lT->next;
    } else {
        l = cur;
        lT = cur;
    }
}

DB *sort(DB *&head) {
    DB *l = nullptr, *b = nullptr, *e = nullptr;
    DB *lT = nullptr, *bT = nullptr, *eT = nullptr;
    DB *next = head;
    int cnt = 0;
    int partition = head->idx;
    while (next) {
        auto cur = next;
        next = next->next;
        cur->next = nullptr;
        if (cur->idx < partition) {
            push_back(l, lT, cur);
        } else if (cur->idx > partition) {
            push_back(b, bT, cur);
        } else {
            push_back(e, eT, cur);
        }
    }
    lT = sort(l);
    bT = sort(b);
    merge(e, eT, l, lT);
    merge(b, bT, e, eT);
    head = b? b : (e? e : l);
    return bT;
}

void normalize(Node *head) {
    Node *cur = head;
    Node *next = cur;
    while (cur) {
        next = cur->next;
        while (next and next->power == cur->power) {
            cur->coef += next->coef;
            auto x = next;
            next = next->next;
            delete(x);
        }
        cur->next = next;
        cur = cur->next;
    }
}

bool equal(Node *f, Node *s) {
    while (f and s) {
        if (f->power != s->power or f->coef != s->coef) {
            return false;
        }
        f = f->next;
        s = s->next;
    }
    if (f or s) {
        return false;
    }
    return true;
}


void print(Node *cur) {
    bool start = 1;
    while (cur != nullptr) {
        if (!start and cur->coef > 0) {
            cout << '+';
        }
        if(cur->coef == 0 and !start) {
            cur = cur->next;
            continue;
        }
        if (cur->power == 0 or abs(cur->coef) != 1) {
            cout << cur->coef;
        } else {
            if (cur->coef < 0) {
                cout << '-';
            }
        }
        if (cur->power > 0) {
            cout << 'x';
            if (cur->power > 1) {
                cout << '^' << cur->power;
            }
        }
        start = false;
        cur = cur->next;
    }
    cout << '.' << endl;
}

void solve() {
    map<ll, Node*> polinoms;
    string command;
    while (true) {
        cin >> command;
        if (command == "REM") {
            string commentary;
            getline(cin, commentary);
        } else if (command == "READ") {
            ll idx;
            cin >> idx;
            if (polinoms.find(idx) != polinoms.end()) {
                cout << "ERR LOL" << '\n';
            } else {
                auto pol = read();
                if (pol == nullptr) {
                    cout << "ERR LOL" << '\n';
                } else {
                    int sz = 0;
                    sort(pol, sz);
                    if (sz < 100) {
                        normalize(pol);
                    }
                    polinoms[idx] = pol;
                    cout << "OK" << '\n';
                }
            }
        } else if (command == "DEL") {
            ll idx;
            cin >> idx;
            if (polinoms.find(idx) == polinoms.end()) {
                cout << "ERR LOL" << '\n';
            } else {
                del(polinoms[idx]);
                polinoms.erase(idx);
                cout << "OK" << '\n';
            }
        } else if (command == "PRINT") {
            ll idx;
            cin >> idx;
            if (polinoms.find(idx) == polinoms.end()) {
                cout << "ERR LOL" << '\n';
            } else {
                print(polinoms[idx]);
            }
        } else if (command == "EQ") {
            ll n, m;
            cin >> n >> m;
            if (polinoms.find(n) == polinoms.end() or polinoms.find(m) == polinoms.end()) {
                cout << "ERR LOL" << '\n';
            } else {
                cout << (equal(polinoms[n], polinoms[m])? "TRUE" : "FALSE") << '\n';
            }
        } else if (command == "EXIT") {

            for (auto &x : polinoms) {
                cout << x.first << ": ";
                print(x.second);
            }
            break;
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