#include <algorithm>
#include <iostream>
#include <random>
using namespace std;
struct Node {
    long long coef;
    long long power;
    Node* next;
    Node(long long c, long long p) : coef(c), power(p), next(nullptr) {}
    Node() :coef(), power(), next(nullptr) {}
};
struct DB{
    Node* head;
    int pos;
    DB* next;
    DB(int pos, Node *head): pos(pos),head(head), next(nullptr){}
    DB(): pos(),head(), next(nullptr){}
    bool push_back(Node *head_to_node, int pos){
        DB *now = this;
        DB *tail;
        DB *add = new DB(pos, head_to_node);
        while(now != nullptr){
            if (now->pos ==  pos){
                return false;
            }
            if (now->next == nullptr){
                tail = now;
            }
            now = now->next;
        }
        tail->next = add;
        return true;
    }
    Node *get(int pos){
        DB *now = this;
        while(now != nullptr){
            if (now->pos ==  pos){
                return now->head;
            }
            now = now->next;
        }
        return nullptr;
    }
    bool del(int pos){
        DB *now = this;
        DB *prev = nullptr;

        while(now != nullptr){
            if (now->pos == pos){
                Node *cur = now->head;
                while(cur != nullptr){
                    Node *next = cur->next;
                    delete(cur);
                    cur = next;
                }
                if (prev != nullptr) {
                    prev->next = now->next;
                }
                delete now;
                return true;
            }
            prev = now;
            now = now->next;
        }
        return false;
    }
};
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

Node* getTail(Node* cur) {
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}
void partition(Node* head, Node* tail, Node*& lessH, Node*& lessT, Node*& equalH, Node*& equalT, Node*& moreH, Node*& moreT){
    long long pivot = head->power;
//    int k = rnd() % 2;
//    if (k == 0){
//        pivot = tail->power;
//    }
    int i = 0;
    Node *nn = head;
    while(nn != nullptr){
        i++;
        nn = nn->next;
    }
    int ln = i / 2;
    i = 0;
    nn = head;
    while(i < ln){
        i++;
        nn = nn->next;
    }
    pivot = nn->power;

    Node* cur = head;
    while (cur != nullptr){
        Node* next = cur->next;
        cur->next = nullptr;
        if (cur->power < pivot){
            if (!lessH) lessH = lessT = cur;
            else lessT = lessT->next = cur;
        }
        else if (cur->power == pivot){
            if (!equalH) equalH = equalT = cur;
            else equalT = equalT->next = cur;
        }
        else {
            if (!moreH) moreH = moreT = cur;
            else moreT = moreT->next = cur;
        }
        if (cur == tail) break;
        cur = next;
    }
}
Node* quickSort3(Node* head, Node* tail){
    if (head == tail){
        return head;
    }
    Node *lessH = nullptr, *lessT = nullptr, *equalH = nullptr, *equalT = nullptr, *moreH = nullptr;
    Node *moreT = nullptr;
    partition(head, tail, lessH, lessT, equalH, equalT, moreH, moreT);

    if (lessH) lessH = quickSort3(lessH, lessT);
    if (moreH) moreH = quickSort3(moreH, moreT);
    if (moreH) moreT = getTail(moreH);
    if(moreH != nullptr){
        moreT->next=equalH;
    }
    if(equalH != nullptr){
        equalT->next=lessH;
    }
    return moreH ? moreH : (equalH ? equalH : lessH);
}

DB* getTailDB(DB* cur) {
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}
void partition(DB* head, DB* tail, DB*& lessH, DB*& lessT, DB*& equalH, DB*& equalT, DB*& moreH, DB*& moreT){
    int pivot = head->pos;
//    int k = rnd() % 2;
//    if (k == 0){
//        pivot = tail->pos;
//    }

    int i = 0;
    DB *nn = head;
    while(nn != nullptr){
        i++;
        nn = nn->next;
    }
    int ln = i / 2;
    i = 0;
    nn = head;
    while(i < ln){
        i++;
        nn = nn->next;
    }
    pivot = nn->pos;

    DB* cur = head;
    while (cur != nullptr)
    {
        DB* next = cur->next;
        cur->next = nullptr;
        if (cur->pos < pivot){
            if (!lessH) lessH = lessT = cur;
            else lessT = lessT->next = cur;
        }
        else if (cur->pos == pivot){
            if (!equalH) equalH = equalT = cur;
            else equalT = equalT->next = cur;
        }
        else {
            if (!moreH) moreH = moreT = cur;
            else moreT = moreT->next = cur;
        }
        if (cur == tail) break;
        cur = next;
    }
}
DB* quickSort3(DB* head, DB* tail){
    if (head == tail){
        return head;
    }
    DB *lessH = nullptr, *lessT = nullptr, *equalH = nullptr, *equalT = nullptr, *moreH = nullptr;
    DB *moreT = nullptr;
    partition(head, tail, lessH, lessT, equalH, equalT, moreH, moreT);

    if (lessH) lessH = quickSort3(lessH, lessT);
    if (moreH) moreH = quickSort3(moreH, moreT);
    if (lessH) lessT = getTailDB(lessH);
    if(lessH != nullptr){
        lessT->next=equalH;
    }
    if(equalH != nullptr){
        equalT->next=moreH;
    }
    return lessH ? lessH : (equalH ? equalH : moreH);
}
pair<Node*, bool> read(){
    string pl;
    getline(cin, pl);
    string t;
    string variable = "";
    string prevVariable = "";
    bool state = false;
    for (auto x: pl){
        if (x != ' ' and x != '-' and x != '.'){
            t.push_back(x);
        }else if (x == '-'){
            t.push_back('-');
        }
        if (isalpha(x)){
            if (state){
                variable+=x;
            }else{
                state = true;
                if (!prevVariable.empty() and prevVariable != variable){
                    cout << "ERR" << endl;
                    return {nullptr, false};
                }
                prevVariable = variable;
                variable = x;
            }
        }else{
            state = false;
        }
    }
    if(variable.empty() or (!prevVariable.empty() and prevVariable != variable)){
        cout << "ERR" << endl;
        return {nullptr, false};
    }
    bool flag = false;
    int i = 0;
    Node* head = nullptr;
    Node* tail = nullptr;

    while (i < t.size()){
        Node* newNode;
        if (t[i] == '+'){
            i++;
            if (t[i] == '-'){
                cout << "ERR"  << endl;
                return {nullptr, false};
            }
        } else if (i != 0 and t[i] != '-'){
            cout << "ERR"  << endl;
            return {nullptr, false};
        }
        long long sign = 1;
        if (i < t.size() and t[i] == '-'){
            sign = -1;
            i++;
        }
        if (i >= t.size()){
            cout << "ERR"  << endl;
            return {nullptr, false};
        }
        long long coef = 1;
        if (i < t.size() and isdigit(t[i])){
            coef = (t[i] - '0');
            i++;
        }
        while( i < t.size() and isdigit(t[i])){
            coef = coef * 10 + (t[i] - '0');
            i++;
        }
        coef *= sign;
        long long power = 0;
        while(i < t.size() and isalpha(t[i])){
            power = 1;
            i++;
        }
        if (i < t.size() and t[i] == '^'){
            i++;
            if(i < t.size() and isdigit(t[i])){
                power = (t[i] - '0');
                i++;
            }else{
                cout << "ERR"  << endl;
                return {nullptr, false};
            }
            while(i < t.size() and isdigit(t[i])){
                power= power * 10 + (t[i] - '0');
                i++;
            }
        }
        if (flag == false){
            head = new Node(coef, power);
            tail = head;
        }else {
            newNode = new Node(coef, power);

            tail->next = newNode;
            tail = newNode;
        }
        flag = true;
    }
    head = quickSort3(head, tail);
    normalize(head);
    return {head, true};
}
void print(Node *head){
    if (head == nullptr){
        cout << "0." << endl;
        return;
    }
    Node* now = head;
    while(now != nullptr){
        if (now->coef != 1){
            if (now->coef < 0){
                if (now->coef == -1 and now->power != 0){
                    cout << "-";
                }else{
                    cout << now->coef;
                }
            }else{
                if (head != now){
                    cout << "+";
                }
                cout << now->coef;
            }
        }else if(now->power == 0){
            if (head != now){
                cout << "+";
            }
            cout << "1";
        }else if (head != now){
            cout << "+";
        }
        if (now->power != 0){
                        cout << "x";
            if (now->power != 1){
                cout << "^" << now->power;
            }
        }
        now = now->next;
    }
    cout << "." << endl;
}
bool eq(Node *head1, Node *head2){
    Node* now1 = head1;
    Node* now2 = head2;
    while (now1 != nullptr and now2 != nullptr){
        if ((now1->power) != (now2->power) or (now1->coef) != (now2->coef)){
            return false;
        }
        now1 = now1->next;
        now2 = now2->next;
    }
    if (now1 != nullptr or now2 != nullptr){
        return false;
    }
    return true;
}
int getNumber(string s, int ind){
    int number = s[ind] - '0';
    ind++;
    while(ind < s.size() and isdigit(s[ind])){
        number = number * 10 + s[ind] - '0';
        ind++;
    }
    return  number;
}
int getSpace(string s, int ind){
    int n = ind;
    while (ind < s.size() ){
        if (s[ind] == ' '){
            return ind;
        }
        ind++;
    }
    return -1;
}
void printDB(DB *head){
    DB* now = head->next;
    while(now != nullptr){
        cout << now->pos << ": " ;
        print(now->head);
        now = now->next;
    }
}
void solve(){
    string s;
    string pl;
    Node *head;
    bool flag = true;
    DB *db = new DB();
    while(flag){
        getline(cin, s);
        if (s[0] == 'R' and s[1] == 'E' and s[2] == 'A' and s[3] == 'D'){
            pair<Node*, bool> g;
            g = read();
            head = g.first;
            if (g.second == false){
                continue;
            }else{
                bool fl;
                if (db == nullptr){
                     db = new DB(s[5] - '0', g.first);
                }else{
                     int number = getNumber(s, 5);
                     fl = db->push_back(g.first, number);
                }
                if (!fl){
                    cout << "ERR" << endl;
                    continue;
                }
                cout << "OK" << endl;
            }
        }
        else if(s[0] == 'P' and s[1] == 'R' and s[2] == 'I' and s[3] == 'N' and s[4] == 'T'){
            int number = getNumber(s, 6);
            Node *now = db->get(number);
            if (now == nullptr){
                cout << "ERR" << endl;
                continue;
            }
            print(now);
        }
        else if(s == "EXIT"){
            quickSort3(db, getTailDB(db));
            printDB(db);
            flag = false;
        }else if(s[0] == 'D' and s[1] == 'E' and s[2] == 'L'){
            // TODO DEL
            int n = getNumber(s, 4);
            bool fl = db->del(n);
            if(!fl){
                cout << "ERR" << endl;
                continue;
            }
            cout << "OK" << endl;
        }else if(s[0] == 'R' and s[1] == 'E' and s[2] == 'M'){
            continue;
        }else if(s[0] == 'E' and s[1] == 'Q'){
            int number1 = getNumber(s, 3);
            int sp = getSpace(s, 3);
            int number2 = getNumber(s, sp + 1);
            Node* head1 = db->get(number1);
            Node* head2 = db->get(number2);
            if (head1 == nullptr or head2 == nullptr){
                cout << "ERR" << endl;
                continue;
            }
            bool flag = eq(head1, head2);
            if(flag){
                cout << "TRUE" << endl;
                continue;
            }
            cout << "FALSE" << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    unsigned long long q = 1;
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    while (q--) {
        solve();
    }
    return 0;
}