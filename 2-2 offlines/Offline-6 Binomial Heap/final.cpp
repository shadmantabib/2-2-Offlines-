#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("out2.txt");


struct Node
{
    int data, degree;
    Node *child, *sibling, *parent;
};

Node *newNode(int key)
{
    Node *temp = new Node;
    temp->data = key;
    temp->degree = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}


Node *merge(Node *b1, Node *b2)
{
    
    if (b1->data > b2->data)
        swap(b1, b2);

    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1;
}

list<Node *> unionBHeap(list<Node *> l1,
                                list<Node *> l2)
{

    list<Node *> _new;
    list<Node *>::iterator it = l1.begin();
    list<Node *>::iterator ot = l2.begin();
    while (it != l1.end() && ot != l2.end())
    {

        if ((*it)->degree <= (*ot)->degree)
        {
            _new.push_back(*it);
            it++;
        }

        else
        {
            _new.push_back(*ot);
            ot++;
        }
    }

    while (it != l1.end())
    {
        _new.push_back(*it);
        it++;
    }


    while (ot != l2.end())
    {
        _new.push_back(*ot);
        ot++;
    }
    return _new;
}


list<Node *> adjust(list<Node *> _heap)
{
    if (_heap.size() <= 1)
        return _heap;
    list<Node *> new_heap;
    list<Node *>::iterator ptr, ptr-nxt, ptr-nxt-sibling;
    ptr = ptr-nxt = ptr-nxt-sibling = _heap.begin();

    if (_heap.size() == 2)
    {
        ptr-nxt = ptr;
        ptr-nxt++;
        ptr-nxt-sibling = _heap.end();
    }
    else
    {
        ptr-nxt++;
        ptr-nxt-sibling = ptr-nxt;
        ptr-nxt-sibling++;
    }
    while (ptr != _heap.end())
    {
    
        if (ptr-nxt == _heap.end())
            ptr++;

        else if ((*ptr)->degree < (*ptr-nxt)->degree)
        {
            ptr++;
            ptr-nxt++;
            if (ptr-nxt-sibling != _heap.end())
                ptr-nxt-sibling++;
        }

        
        else if (ptr-nxt-sibling != _heap.end() &&
                 (*ptr)->degree == (*ptr-nxt)->degree &&
                 (*ptr)->degree == (*ptr-nxt-sibling)->degree)
        {
            ptr++;
            ptr-nxt++;
            ptr-nxt-sibling++;
        }

        else if ((*ptr)->degree == (*ptr-nxt)->degree)
        {
            Node *temp;
            *ptr = merge(*ptr, *ptr-nxt);
            ptr-nxt = _heap.erase(ptr-nxt);
            if (ptr-nxt-sibling != _heap.end())
                ptr-nxt-sibling++;
        }
    }
    return _heap;
}


list<Node *> insertATreeInHeap(list<Node *> _heap,
                               Node *tree)
{

    list<Node *> temp;


    temp.push_back(tree);

    temp = unionBHeap(_heap, temp);

    return adjust(temp);
}

list<Node *> removeMin(Node *tree)
{
    list<Node *> heap;
    Node *temp = tree->child;
    Node *lo;

  
    while (temp)
    {
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        heap.push_front(lo);
    }
    return heap;
}


list<Node *> insert(list<Node *> _head, int key)
{
    Node *temp = newNode(key);
    return insertATreeInHeap(_head, temp);
}

Node *getMin(list<Node *> _heap)
{
    list<Node *>::iterator it = _heap.begin();
    Node *temp = *it;
    while (it != _heap.end())
    {
        if ((*it)->data < temp->data)
            temp = *it;
        it++;
    }
    return temp;
}

list<Node *> extractMin(list<Node *> _heap)
{
    list<Node *> new_heap, lo;
    Node *temp;

    temp = getMin(_heap);
    list<Node *>::iterator it;
    it = _heap.begin();
    while (it != _heap.end())
    {
        if (*it != temp)
        {

            new_heap.push_back(*it);
        }
        it++;
    }
    lo = removeMin(temp);
    new_heap = unionBHeap(new_heap, lo);
    cout << "Extract-Min returned " << temp->data << endl;
    fout << "Extract-Min returned " << temp->data << endl;
    new_heap = adjust(new_heap);
    return new_heap;
}



void printTreeLevelOrder(Node *root, int treeIndex)
{
    if (!root)
        return;

    queue<pair<Node *, int>> q;
    q.push({root, 0});

    while (!q.empty())
    {
        int size = q.size();
        cout << "Level " << q.front().second << " : ";
        fout << "Level " << q.front().second << " : ";
        while (size--)
        {
            Node *current = q.front().first;
            int level = q.front().second;
            q.pop();

            cout << current->data << " ";
            fout << current->data << " ";
            Node *child = current->child;
            while (child)
            {
                q.push({child, level + 1});
                child = child->sibling;
            }
        }

        cout << endl;
        fout << endl;
    }
}

void printHeapLevelOrder(list<Node *> _heap)
{
    int binomialTreeIndex = 0;
    for (Node *tree : _heap)
    {
        cout << "Binomial Tree, B" << tree->degree << endl;
        fout << "Binomial Tree, B" << tree->degree << endl;
        printTreeLevelOrder(tree, tree->degree);
    }
}



Node *unionMultipleNumbers(vector<int> &nums)
{
    Node *result = nullptr;

    for (int num : nums)
    {
        Node *temp = newNode(num);
        if (!result)
            result = temp;
        else
            result = merge(result, temp);
    }

    return result;
}

int main()
{
    int ch, key;
    list<Node *> _heap;
    string s;
    while (fin >> s)
    {
        if (s == "I")
        {
            int x;
            fin >> x;
            _heap = insert(_heap, x);
        }
        if (s == "P")
        {
            cout << "Printing Binomial Heap..." << endl;
            fout << "Printing Binomial Heap..." << endl;
            printHeapLevelOrder(_heap);
        }

        if (s == "F")
        {
            Node *temp = getMin(_heap);
            cout << "Find-Min returned " << temp->data << "\n";
            fout << "Find-Min returned " << temp->data << "\n";
        }
        if (s == "E")
        {
            _heap = extractMin(_heap);
        }
        if (s == "U")
        {
            string line;
            getline(fin, line); 
            istringstream iss(line);
            vector<int> nums;
            int num;
            while (iss >> num)
            {
                nums.push_back(num);
            }

            list<Node *> _heap1;
            for (int x : nums)
            {
                _heap1 = insert(_heap1, x);
            }

            _heap = unionBHeap(_heap, _heap1);
            _heap = adjust(_heap);
        }
    }

    return 0;
}
