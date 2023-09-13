/*
    Shafayat Hossain Majumder
    16.09.2020
*/

#include <bits\stdc++.h>
using namespace std;

//defined my datatypes
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvll;

//defined my macro functions
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define printclock cerr << "Time : " << 1000 * (ld)clock() / (ld)CLOCKS_PER_SEC << "ms\n"
#define NITRO                     \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)

//defined my macro strings
#define ENDL "\n"
#define gap " "
#define ha "YES"
#define na "NO"

//defined my constants
const int INF = 0x3f3f3f3f;        //1061109567, > 1e9
const ll LNF = 0x3f3f3f3f3f3f3f3f; //4557430888798830399, > 4e18
const int MOD = 1000000007;        //9 digits, 1e9 + 7
const double EPS = 1e-8;
const ld EUL = 2.71828182845904523536; //20digits
const ld PII = 3.14159265358979323846; //20digits
//int   = 4e9,     ll = 1e19   hi value
//float = 7digits, double = 15digits, ld = 21 digits precision

const ll C1 = 11;
const ll C2 = 7;

struct keyval
{
    //stores key-value pair
    string key;
    ll value;
};

struct node
{
    int flag; // flag 0 = no data, flag 1 = data present, flag 2 = data deleted
    keyval *item;
    node *nxt;
};

typedef node *nodep;
typedef keyval *datap;
ll hashing1(string key)
{
    ll h = 3323198485;
    for (ll ki : key)
    {
        h ^= ki;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

ll hashing2(string key)
{
    ll h = 0;
    for (int ki : key)
    {
        h = (h << 4) + ki;
        ll g = h & 0xf0000000;
        if (g != 0)
        {
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }
    return h;
}

ll auxhashing(string key)
{
    ll h = 5381;

    for (ll ki : key)
        h = ((h << 5) + h) + ki;

    return h;
}

ll calcindex(ll h1, ll h2, ll i, ll n, ll type)
{
    ll x;
    if (type == 2)
        x = (h1 + (i * h2)) % n;
    else
        x = (h1 + (C1 * i * h2) + (C2 * i * i)) % n;
    return x;
}

vector<string> wordgen(ll n)
{
    unordered_set<string> dic;
    string letter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ll len = 7;
    while (dic.size() < n)
    {
        string temp = "";
        for (ll i = 0; i < len; i++)
            temp += letter[rand() % letter.length()];
        dic.insert(temp);
    }
    return vector<string>(dic.begin(), dic.end());
}

class myHashTable
{
    vector<nodep> table;
    ll cnt;
    ll size;
    ll usehash;
    ll colhandle;
    ll col;
    ll probe;

public:
    myHashTable(ll n, ll usehash, ll colhandle);
    ~myHashTable();
    bool isfull();
    void ins(string key, ll val);
    ll search(string key);
    void del(string key);
    void resetcalc() { col = 0, probe = 0; };
    ll getcol() { return col; };
    ll getprobe() { return probe; };
    ll getelemsize() { return cnt; };
    void printtable();
};

myHashTable::myHashTable(ll n, ll usehash, ll colhandle)
{
    this->table = vector<nodep>(n);
    for (int i = 0; i < n; i++)
    {
        table[i] = new node;
        table[i]->flag = 0, table[i]->item = nullptr, table[i]->nxt = nullptr;
    }
    this->cnt = 0;
    this->size = n;
    this->usehash = usehash;
    this->colhandle = colhandle;
    resetcalc();
}

myHashTable::~myHashTable()
{
    this->table.clear();
}

bool myHashTable::isfull()
{
    return cnt >= size;
}

void myHashTable::ins(string key, ll val)
{
    if (isfull())
    {
        cout << "Table is full" << endl;
        return;
    }

    ll h1 = ((this->usehash == 1) ? hashing1(key) : hashing2(key)) % this->size;
    ll h2 = auxhashing(key) % this->size;
    ll index;

    datap temp = new keyval;
    temp->key = key;
    temp->value = val;

    if (colhandle == 1)
    {
        index = h1;
        if (table[index]->flag != 1)
            table[index]->flag = 1, table[index]->item = temp, table[index]->nxt = nullptr;
        else
        {
            this->col++;
            nodep head = table[index];
            while (head->nxt)
                head = head->nxt;
            nodep sm = new node;
            sm->flag = 1;
            sm->item = temp;
            sm->nxt = nullptr;

            head->nxt = sm;
        }
        cnt++;
    }
    else
    {
        ll i = 0;
        while (table[index = calcindex(h1, h2, i, this->size, this->colhandle)]->flag == 1)
        {
            if (i && index == h1)
                return;
            col++;
            i++;
        }
        table[index]->flag = 1;
        table[index]->item = temp;
        table[index]->nxt = nullptr;
        cnt++;
    }
}

ll myHashTable::search(string key)
{
    ll h1 = ((this->usehash == 1) ? hashing1(key) : hashing2(key)) % this->size;
    ll h2 = auxhashing(key) % this->size;
    ll index;
    if (colhandle == 1)
    {
        index = h1;
        this->probe++;
        if (table[index]->flag != 1)
            return -INF;
        else
        {
            this->probe--;
            nodep head = table[index];
            while (head)
            {
                this->probe++;
                if (head->item->key == key)
                    return head->item->value;
                head = head->nxt;
            }
            return -INF;
        }
    }
    else
    {
        ll i = 0;
        while (table[index = calcindex(h1, h2, i, this->size, this->colhandle)]->flag != 0)
        {
            if (i && index == h1)
                break;
            if (table[index]->flag == 1 && table[index]->item->key == key)
                return table[index]->item->value;
            i++;
            this->probe++;
        }
        return -INF;
    }
}

void myHashTable::del(string key)
{
    if (!cnt)
        return;

    ll h1 = ((this->usehash == 1) ? hashing1(key) : hashing2(key)) % this->size;
    ll h2 = auxhashing(key) % this->size;
    ll index;

    if (colhandle == 1)
    {
        index = h1;
        if (table[index]->flag != 1)
            return;
        else
        {
            nodep head = table[index];
            nodep prev = nullptr;
            while (head)
            {
                if (head->item->key == key)
                    break;
                prev = head;
                head = head->nxt;
            }
            if (prev)
                prev->nxt = head->nxt;
            else
            {
                table[index] = head->nxt;
                if (!table[index])
                {
                    nodep x = new node;
                    x->flag = 0;
                    x->item = nullptr;
                    x->nxt = nullptr;
                    table[index] = x;
                }
            }
            delete head;
            cnt--;
        }
    }
    else
    {
        ll i = 0;
        while (table[index = calcindex(h1, h2, i, this->size, this->colhandle)]->flag != 0)
        {
            if (i && index == h1)
            {
                break;
            }
            if (table[index]->flag == 1 && table[index]->item->key == key)
            {
                table[index]->flag = 2;
                delete table[index]->item;
                cnt--;
                return;
            }
            i++;
        }
    }
}

void myHashTable::printtable()
{
    for (int i = 0; i < size; i++)
    {
        //cout<<i<<endl;
        if (table[i]->flag == 1)
        {
            cout << i + 1 << gap;
            nodep head = table[i];
            while (head)
            {
                cout << "->" << gap << "(" << head->item->key << ", " << head->item->value << ")" << gap;
                head = head->nxt;
            }
            cout << endl;
        }
    }
}

int main()
{
    NITRO;
    srand(time(NULL));
    /*
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    */
    int x, y;
    cout << "-------------------------" << endl;
    cout << "HASH TABLE IMPLEMENTATION" << endl;
    cout << "-------------------------" << endl;

    cout << endl
         << "Enter the size of the dictionary:" << endl;
    cin >> x;
    cout << "Enter the size multiplication factor for the Hash Table:" << endl;
    cin >> y;
    vector<string> test = wordgen(x);
    myHashTable tbl1(x * y, 1, 1); //hash1, collision resolution: chaining
    myHashTable tbl2(x * y, 2, 1); //hash2, collision resolution: chaining
    myHashTable tbl3(x * y, 1, 2); //hash1, collision resolution: double hashing
    myHashTable tbl4(x * y, 2, 2); //hash2, collision resolution: double hashing
    myHashTable tbl5(x * y, 1, 3); //hash1, collision resolution: custom probing
    myHashTable tbl6(x * y, 2, 3); //hash2, collision resolution: custom probing
    for (int i = 0; i < x; i++)
    {
        tbl1.ins(test[i], i + 1);
        tbl2.ins(test[i], i + 1);
        tbl3.ins(test[i], i + 1);
        tbl4.ins(test[i], i + 1);
        tbl5.ins(test[i], i + 1);
        tbl6.ins(test[i], i + 1);
    }

    for (int i = 0; i < (x / 10); i++)
    {
        tbl1.search(test[rand() % x]);
        tbl2.search(test[rand() % x]);
        tbl3.search(test[rand() % x]);
        tbl4.search(test[rand() % x]);
        tbl5.search(test[rand() % x]);
        tbl6.search(test[rand() % x]);
    }
    cout << "------" << endl;
    cout << "HASH 1" << endl;
    cout << "------" << endl;
    cout << "Chaining Method:" << endl;
    cout << "No. of collisions :\t" << tbl1.getcol() << endl;
    cout << "Avg probes:\t\t" << (tbl1.getprobe() * 10.0 / x) << endl
         << endl;

    cout << "Double Hashing:" << endl;
    cout << "No. of collisions :\t" << tbl3.getcol() << endl;
    cout << "Avg probes:\t\t" << (tbl3.getprobe() * 10.0 / x) << endl
         << endl;

    cout << "Custom probing:" << endl;
    cout << "No. of collisions :\t" << tbl5.getcol() << endl;
    cout << "Avg probes:\t\t" << (tbl5.getprobe() * 10.0 / x) << endl
         << endl;

    cout << "------" << endl;
    cout << "HASH 2" << endl;
    cout << "------" << endl;
    cout << "Chaining Method:" << endl;
    cout << "No. of collisions :\t" << tbl2.getcol() << endl;
    cout << "Avg probes:\t\t" << (tbl2.getprobe() * 10.0 / x) << endl
         << endl;

    cout << "Double Hashing:" << endl;
    cout << "No. of collisions :\t" << tbl4.getcol() << endl;
    cout << "Avg probes:\t\t" << (tbl4.getprobe() * 10.0 / x) << endl
         << endl;

    cout << "Custom probing:" << endl;
    cout << "No. of collisions :\t" << tbl6.getcol() << endl;
    cout << "Avg probes:\t\t" << (tbl6.getprobe() * 10.0 / x) << endl
         << endl;

    printclock;
    return 0;
}