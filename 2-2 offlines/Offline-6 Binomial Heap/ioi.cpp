#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

struct node {
    int n;
    int degree;
    node* parent;
    node* child;
    node* sibling;
};

class BinomialHeap {
private:
    node* H;
    node* Hr;

public:
    node* Initializeheap();
    int Binomial_link(node*, node*);
    node* Create_node(int);
    node* Union(node*, node*);
    node* Insert(node*, node*);
    node* Merge(node*, node*);
    node* Extract_Min(node*);
    node* Extract_Min1(node*);
    int Revert_list(node*);
    int Display(node*);
    node* Search(node*, int);
    int Decrease_key(node*, int, int);
    int Delete(node*, int);

    BinomialHeap() {
        H = Initializeheap();
        Hr = Initializeheap();
    }
};

node* BinomialHeap::Initializeheap() {
    return nullptr;
}

int BinomialHeap::Binomial_link(node* y, node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

node* BinomialHeap::Create_node(int k) {
    node* p = new node;
    p->n = k;
    return p;
}

node* BinomialHeap::Insert(node* H, node* x) {
    node* H1 = Initializeheap();
    x->parent = nullptr;
    x->child = nullptr;
    x->sibling = nullptr;
    x->degree = 0;
    H1 = x;
    H = Union(H, H1);
    return H;
}

node* BinomialHeap::Union(node* H1, node* H2) {
    node* H = Initializeheap();
    H = Merge(H1, H2);
    if (H == nullptr)
        return H;

    node* prev_x = nullptr;
    node* x = H;
    node* next_x = x->sibling;

    while (next_x != nullptr) {
        if ((x->degree != next_x->degree) || ((next_x->sibling != nullptr) && (next_x->sibling)->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else {
            if (x->n <= next_x->n) {
                x->sibling = next_x->sibling;
                Binomial_link(next_x, x);
            } else {
                if (prev_x == nullptr)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Binomial_link(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}

node* BinomialHeap::Merge(node* H1, node* H2) {
    node* H = Initializeheap();
    node* y;
    node* z;
    node* a;
    node* b;
    y = H1;
    z = H2;

    if (y != nullptr) {
        if (z != nullptr) {
            if (y->degree <= z->degree)
                H = y;
            else if (y->degree > z->degree)
                H = z;
        } else
            H = y;
    } else
        H = z;

    while (y != nullptr && z != nullptr) {
        if (y->degree < z->degree)
            y = y->sibling;
        else if (y->degree == z->degree) {
            a = y->sibling;
            y->sibling = z;
            y = a;
        } else {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

int BinomialHeap::Display(node* H) {
    if (H == nullptr) {
        cout << "The Heap is empty" << endl;
        return 0;
    }

    cout << "Printing Binomial Heap..." << endl;
    while (H != nullptr) {
        cout << "Binomial Tree, B" << H->degree << endl;
        cout << "Level 0 : " << H->n;

        node* child = H->child;
        int level = 1;
        while (child != nullptr) {
            cout << "\nLevel " << level << " : ";
            while (child != nullptr) {
                cout << child->n << " ";
                child = child->sibling;
            }
            level++;
        }
        cout << endl;
        H = H->sibling;
    }
}
node* BinomialHeap::Extract_Min1(node* H1) {
    node* t = nullptr;
    node* x = H1;

    if (x == nullptr) {
        cout << "Nothing to Extract" << endl;
        return x;
    }

    int min = x->n;
    node* p = x;

    while (p->sibling != nullptr) {
        if ((p->sibling)->n < min) {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }

    return x;
}


node* BinomialHeap::Extract_Min(node* H1) {
    node* t = nullptr;
    node* x = H1;
    node* minNode = nullptr;

    if (x == nullptr) {
        cout << "Nothing to Extract" << endl;
        return x;
    }

    int min = x->n;
    node* p = x;

    while (p->sibling != nullptr) {
        if ((p->sibling)->n < min) {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }

    if (t == nullptr && x->sibling == nullptr)
        H1 = nullptr;
    else if (t == nullptr)
        H1 = x->sibling;
    else if (t->sibling == nullptr)
        t = nullptr;
    else
        t->sibling = x->sibling;

    if (x->child != nullptr) {
        Revert_list(x->child);
        (x->child)->sibling = nullptr;
    }

    minNode = x;
    H = Union(H1, Hr);

    //cout << "Extract-Min returned " << minNode->n << endl;

    return minNode;
}


int BinomialHeap::Revert_list(node* y) {
    if (y->sibling != nullptr) {
        Revert_list(y->sibling);
        (y->sibling)->sibling = y;
    } else {
        Hr = y;
    }
}

node* BinomialHeap::Search(node* H, int k) {
    node* x = H;
    node* p = nullptr;

    if (x->n == k) {
        p = x;
        return p;
    }

    if (x->child != nullptr && p == nullptr)
        p = Search(x->child, k);

    if (x->sibling != nullptr && p == nullptr)
        p = Search(x->sibling, k);

    return p;
}

int BinomialHeap::Decrease_key(node* H, int i, int k) {
    int temp;
    node* p;
    node* y;
    node* z;
    p = Search(H, i);

    if (p == nullptr) {
        cout << "Invalid choice of key" << endl;
        return 0;
    }

    if (k > p->n) {
        cout << "Error!! New key is greater than current key" << endl;
        return 0;
    }

    p->n = k;
    y = p;
    z = p->parent;

    while (z != nullptr && y->n < z->n) {
        temp = y->n;
        y->n = z->n;
        z->n = temp;
        y = z;
        z = z->parent;
    }

    cout << "Key reduced successfully" << endl;
}

int BinomialHeap::Delete(node* H, int k) {
    node* np;

    if (H == nullptr) {
        cout << "\nHEAP EMPTY!!!!!";
        return 0;
    }

    Decrease_key(H, k, -1000);
    np = Extract_Min(H);

    if (np != nullptr)
        cout << "Node Deleted Successfully" << endl;
}

int main() {
    BinomialHeap bh;
    node* H;
    H = bh.Initializeheap();

    while (true) {
        char op;
        //cout << "Enter operation (I/P/F/E/U/D/Q): ";
        cin >> op;

        if (op == 'I') {
            int val;
           // cout << "Enter the element to be inserted: ";
            cin >> val;
            node* p = bh.Create_node(val);
            H = bh.Insert(H, p);
        } else if (op == 'P') {
            bh.Display(H);
        } else if (op == 'F') {
            node* p = bh.Extract_Min1(H);
            if (p != nullptr)
                cout /*<< "Find-Min returned "*/ << p->n << endl;
        } else if (op == 'E') {
            node* p = bh.Extract_Min(H);
            if (p != nullptr)
                cout /*<< "Extract-Min returned " */<< p->n << endl;
        } else if (op == 'U') {
            int key1, key2;
            //cout << "Enter keys to Union: ";
            cin >> key1 >> key2;
            node* H1 = bh.Initializeheap();
            node* H2 = bh.Initializeheap();
            H1 = bh.Search(H, key1);
            H2 = bh.Search(H, key2);

            if (H1 != nullptr && H2 != nullptr) {
                H = bh.Union(H1, H2);
                //cout << "Union successful" << endl;
            } else {
                //cout << "Keys not found" << endl;
            }
        } else if (op == 'D') {
            int key;
            //cout << "Enter the key to be deleted: ";
            cin >> key;
            bh.Delete(H, key);
        } else if (op == 'Q') {
            exit(0);
        } else {
            cout << "Invalid operation" << endl;
        }
    }

    return 0;
}
