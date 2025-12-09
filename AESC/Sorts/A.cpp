#include "bits/stdc++.h"

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define double ld
const int MOD = 1e9 + 7;
const double eps = 1e-6;
const int SIGNES_AFTER_COMMA = 9;

const int NUL = LLONG_MAX;

struct node {
    int val;
    node *next;
    node() {
        val = NUL;
        next = nullptr;
    }
    node(int x) {
        val = x;
        next = nullptr;
    }
};

struct List {
    node *head, *tail;
    List() {
        head = nullptr;
        tail = head;
    }
    node* pop_front() {
        node* cur = this->head;
        this->head = this->head->next;
        cur->next = nullptr;
        return cur;
    }
    void push_back(int x) {
        if (this->head == nullptr) {
            this->head = new node(x);
            this->tail = this->head;
        } else {
            this->tail->next = new node(x);
            this->tail = this->tail->next;
        }
    }
    void push_back(List b) {
        if (this->head == nullptr) {
            this->head = b.head;
        } else if (this->head->val == NUL) {
            this->head = b.head;
        } else {
            this->tail->next = b.head;
        }
        if (b.tail != nullptr) {
            this->tail = b.tail;
        }
    }
    void push_back(node *a) {
        if (this->head == nullptr) {
            this->head = a;
            this->tail = a;
        } else {
            this->tail->next = a;
            this->tail = this->tail->next;
        }
    }
    friend ostream& operator<<(ostream &out, List a) {
        node *cur = a.head;
        while (cur != nullptr) {
            cout << cur->val << ' ';
            cur = cur->next;
        }
        return out;
    }
    void sort() {
        if (this->head == nullptr) {
            return;
        }
        List l, e, b;
        int partition = this->head->val;
        while (this->head != nullptr) {
            auto cur = this->pop_front();
            if (cur->val == partition) {
                e.push_back(cur);
            } else if (cur->val > partition) {
                b.push_back(cur);
            } else {
                l.push_back(cur);
            }
        }
        l.sort();
        b.sort();
        e.push_back(b);
        l.push_back(e);
        this->push_back(l);
    }
};

void solve() {
    int n;
    cin >> n;
    List a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    a.sort();

    cout << a << '\n';
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