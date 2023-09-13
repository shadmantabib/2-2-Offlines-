#include <bits/stdc++.h>
using namespace std;

struct BinomialHeapNode {
    int key;
    int degree;
    BinomialHeapNode* parent;
    BinomialHeapNode* child;
    BinomialHeapNode* sibling;

    BinomialHeapNode(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
private:
    BinomialHeapNode* head;

    BinomialHeapNode* mergeTrees(BinomialHeapNode* tree1, BinomialHeapNode* tree2) {
        if (tree1->key < tree2->key) {
            tree1->sibling = tree2->child;
            tree2->child = tree1;
            tree1->parent = tree2;
            tree2->degree++;
            return tree2;
        } else {
            tree2->sibling = tree1->child;
            tree1->child = tree2;
            tree2->parent = tree1;
            tree1->degree++;
            return tree1;
        }
    }

    BinomialHeapNode* mergeHeaps(BinomialHeapNode* heap1, BinomialHeapNode* heap2) {
        if (!heap1) return heap2;
        if (!heap2) return heap1;

        BinomialHeapNode* newHead = nullptr;
        BinomialHeapNode* tail = nullptr;

        if (heap1->degree <= heap2->degree) {
            newHead = heap1;
            heap1 = heap1->sibling;
        } else {
            newHead = heap2;
            heap2 = heap2->sibling;
        }

        tail = newHead;

        while (heap1 && heap2) {
            if (heap1->degree <= heap2->degree) {
                tail->sibling = heap1;
                heap1 = heap1->sibling;
            } else {
                tail->sibling = heap2;
                heap2 = heap2->sibling;
            }
            tail = tail->sibling;
        }

        if (heap1) tail->sibling = heap1;
        else if (heap2) tail->sibling = heap2;

        return newHead;
    }

    void insertTree(BinomialHeapNode* tree) {
        BinomialHeapNode* newHeap = new BinomialHeapNode(tree->key);
        newHeap->child = tree->child;
        newHeap->sibling = tree->sibling;
        newHeap->degree = tree->degree;

        tree->child = nullptr;
        tree->sibling = nullptr;
        tree->degree = 0;

        head = mergeHeaps(head, newHeap);
    }

    void printTree(BinomialHeapNode* root) {
        queue<BinomialHeapNode*> q;
        q.push(root);

        while (!q.empty()) {
            BinomialHeapNode* node = q.front();
            q.pop();

            cout << "Level " << node->degree << " : " << node->key << " ";

            BinomialHeapNode* child = node->child;
            while (child) {
                q.push(child);
                child = child->sibling;
            }
        }
    }

public:
    BinomialHeap() : head(nullptr) {}

    void insert(int key) {
        BinomialHeapNode* newNode = new BinomialHeapNode(key);
        BinomialHeapNode* newHeap = new BinomialHeapNode(key);
        newHeap->child = newNode;
        head = mergeHeaps(head, newHeap);
    }

    int findMin() {
        if (!head) return -1;
        int minKey = head->key;
        BinomialHeapNode* curr = head;
        while (curr) {
            if (curr->key < minKey) {
                minKey = curr->key;
            }
            curr = curr->sibling;
        }
        return minKey;
    }

    void extractMin() {
        if (!head) return;
        int minKey = head->key;
        BinomialHeapNode* minNode = head;
        BinomialHeapNode* prevMinNode = nullptr;
        BinomialHeapNode* curr = head->sibling;

        while (curr) {
            if (curr->key < minKey) {
                minKey = curr->key;
                minNode = curr;
                prevMinNode = curr->parent;
            }
            curr = curr->sibling;
        }

        if (prevMinNode) {
            prevMinNode->sibling = minNode->sibling;
        } else {
            head = minNode->sibling;
        }

        BinomialHeapNode* newHeap = nullptr;
        BinomialHeapNode* child = minNode->child;

        while (child) {
            BinomialHeapNode* next = child->sibling;
            child->sibling = nullptr;
            newHeap = mergeHeaps(newHeap, child);
            child = next;
        }

        delete minNode;
        head = mergeHeaps(head, newHeap);
    }

    void levelOrderTraversal() {
        if (!head) return;
        queue<BinomialHeapNode*> q;
        q.push(head);

        while (!q.empty()) {
            BinomialHeapNode* node = q.front();
            q.pop();

            cout << "Binomial Tree, B" << node->degree << endl;
            printTree(node);
            cout << endl;

            BinomialHeapNode* child = node->child;
            while (child) {
                q.push(child);
                child = child->sibling;
            }
        }
    }

    void unionWith(BinomialHeap* otherHeap) {
        head = mergeHeaps(head, otherHeap->head);
        otherHeap->head = nullptr;
    }
};

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    BinomialHeap heap;

    string line;
    while (getline(input, line)) {
        if (line.empty()) continue;

        char op;
        int key1, key2;
        sscanf(line.c_str(), "%c %d %d", &op, &key1, &key2);

        if (op == 'I') {
            heap.insert(key1);
        } else if (op == 'F') {
            int minKey = heap.findMin();
            output << "Find-Min returned " << minKey << endl;
            cout << "Find-Min returned " << minKey << endl;
        } else if (op == 'E') {
            heap.extractMin();
        } else if (op == 'P') {
            heap.levelOrderTraversal();
        } else if (op == 'U') {
            BinomialHeap otherHeap;
            otherHeap.insert(key1);
            otherHeap.insert(key2);
            heap.unionWith(&otherHeap);
        }
    }

    input.close();
    output.close();

    return 0;
}
