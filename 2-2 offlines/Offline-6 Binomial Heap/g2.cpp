#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data, degree;
    Node *child, *sibling, *parent;
};

Node* newNode(int key) {
    Node* temp = new Node;
    temp->data = key;
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}

Node* mergeBinomialTrees(Node* b1, Node* b2) {
    if (b1->data > b2->data)
        swap(b1, b2);
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

list<Node*> unionBinomialHeap(list<Node*> l1, list<Node*> l2) {
    list<Node*> newHeap;
    list<Node*>::iterator it1 = l1.begin();
    list<Node*>::iterator it2 = l2.begin();

    while (it1 != l1.end() && it2 != l2.end()) {
        if ((*it1)->degree <= (*it2)->degree) {
            newHeap.push_back(*it1);
            it1++;
        } else {
            newHeap.push_back(*it2);
            it2++;
        }
    }

    while (it1 != l1.end()) {
        newHeap.push_back(*it1);
        it1++;
    }

    while (it2 != l2.end()) {
        newHeap.push_back(*it2);
        it2++;
    }

    return newHeap;
}

list<Node*> adjustHeap(list<Node*> heap) {
    if (heap.size() <= 1)
        return heap;
    
    list<Node*> newHeap;
    list<Node*>::iterator it1, it2, it3;
    it1 = it2 = it3 = heap.begin();

    if (heap.size() == 2) {
        it2 = it1;
        it2++;
        it3 = heap.end();
    } else {
        it2++;
        it3 = it2;
        it3++;
    }

    while (it1 != heap.end()) {
        if (it2 == heap.end())
            it1++;
        else if ((*it1)->degree < (*it2)->degree) {
            it1++;
            it2++;
            if (it3 != heap.end())
                it3++;
        } else if (it3 != heap.end() && (*it1)->degree == (*it2)->degree && (*it1)->degree == (*it3)->degree) {
            it1++;
            it2++;
            it3++;
        } else if ((*it1)->degree == (*it2)->degree) {
            Node* temp = mergeBinomialTrees(*it1, *it2);
            it1 = heap.erase(it1);
            it2 = heap.erase(it2);
            it3 = heap.insert(it3, temp);
            it3++;
        }
    }

    return heap;
}

list<Node*> insertTreeInHeap(list<Node*> heap, Node* tree) {
    list<Node*> temp;
    temp.push_back(tree);
    temp = unionBinomialHeap(heap, temp);
    return adjustHeap(temp);
}

list<Node*> removeMinFromTreeReturnHeap(Node* tree) {
    list<Node*> heap;
    Node* temp = tree->child;
    Node* lo;

    while (temp) {
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        heap.push_front(lo);
    }

    return heap;
}

list<Node*> insert(list<Node*> heap, int key) {
    Node* temp = newNode(key);
    return insertTreeInHeap(heap, temp);
}

Node* getMin(list<Node*> heap) {
    list<Node*>::iterator it = heap.begin();
    Node* temp = *it;

    while (it != heap.end()) {
        if ((*it)->data < temp->data)
            temp = *it;
        it++;
    }

    return temp;
}

list<Node*> extractMin(list<Node*> heap) {
    list<Node*> newHeap, lo;
    Node* temp = getMin(heap);
    list<Node*>::iterator it = heap.begin();

    while (it != heap.end()) {
        if (*it != temp)
            newHeap.push_back(*it);
        it++;
    }

    lo = removeMinFromTreeReturnHeap(temp);
    newHeap = unionBinomialHeap(newHeap, lo);
    return adjustHeap(newHeap);
}

void printTreeLevelOrder(Node* root) {
    if (!root)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            Node* child = current->child;
            while (child) {
                q.push(child);
                child = child->sibling;
            }
        }

        cout << endl;
    }
}

void printHeapLevelOrder(list<Node*> heap) {
    for (Node* tree : heap) {
        cout << "Binomial Tree, B" << tree->degree << endl;
        printTreeLevelOrder(tree);
    }
}

int main() {
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    list<Node*> heap;

    char op;
    int key, k1, k2;
    Node* temp1;
    Node* temp2;
    list<Node*> newHeap;

    while (infile >> op) {
        switch (op) {
            case 'I':
                infile >> key;
                heap = insert(heap, key);
                break;
            case 'F':
                outfile << "Find-Min returned " << getMin(heap)->data << endl;
                break;
            case 'E':
                heap = extractMin(heap);
                break;
            case 'P':
                outfile << "Printing Binomial Heap..." << endl;
                printHeapLevelOrder(heap);
                break;
            case 'U':
                infile >> k1 >> k2;
                temp1 = newNode(k1);
                temp2 = newNode(k2);
                newHeap.clear();
                newHeap.push_back(temp1);
                newHeap.push_back(temp2);
                heap = unionBinomialHeap(heap, newHeap);
                heap = adjustHeap(heap);
                break;
            default:
                break;
        }
    }

    infile.close();
    outfile.close();

    return 0;
}
