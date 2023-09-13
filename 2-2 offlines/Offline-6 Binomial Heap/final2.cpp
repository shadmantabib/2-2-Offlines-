#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output2.txt");

struct BNode
{
    int value, order;
    BNode *child, *sibling, *parent;
};

BNode *createBNode(int val)
{
    BNode *temp = new BNode;
    temp->value = val;
    temp->order = 0;
    temp->child = temp->parent = temp->sibling = NULL;
    return temp;
}

BNode *mergeBNodes(BNode *node1, BNode *node2)
{
    if (node1->value > node2->value)
        swap(node1, node2);

    node2->parent = node1;
    node2->sibling = node1->child;
    node1->child = node2;
    node1->order++;

    return node1;
}

list<BNode *> combineBHeaps(list<BNode *> heapList1, list<BNode *> heapList2)
{
    list<BNode *> newHeapList;
    list<BNode *>::iterator it1 = heapList1.begin();
    list<BNode *>::iterator it2 = heapList2.begin();

    while (it1 != heapList1.end() && it2 != heapList2.end())
    {
        if ((*it1)->order <= (*it2)->order)
        {
            newHeapList.push_back(*it1);
            it1++;
        }
        else
        {
            newHeapList.push_back(*it2);
            it2++;
        }
    }

    while (it1 != heapList1.end())
    {
        newHeapList.push_back(*it1);
        it1++;
    }

    while (it2 != heapList2.end())
    {
        newHeapList.push_back(*it2);
        it2++;
    }
    return newHeapList;
}

list<BNode *> adjustBHeap(list<BNode *> heapList)
{
    if (heapList.size() <= 1)
        return heapList;

    list<BNode *> newHeap;
    list<BNode *>::iterator ptr, ptr_nxt, ptr_nxt_sibling;
    ptr = ptr_nxt = ptr_nxt_sibling = heapList.begin();

    if (heapList.size() == 2)
    {
        ptr_nxt = ptr;
        ptr_nxt++;
        ptr_nxt_sibling = heapList.end();
    }
    else
    {
        ptr_nxt++;
        ptr_nxt_sibling = ptr_nxt;
        ptr_nxt_sibling++;
    }

    while (ptr != heapList.end())
    {
        if (ptr_nxt == heapList.end())
            ptr++;
        else if ((*ptr)->order < (*ptr_nxt)->order)
        {
            ptr++;
            ptr_nxt++;
            if (ptr_nxt_sibling != heapList.end())
                ptr_nxt_sibling++;
        }
        else if (ptr_nxt_sibling != heapList.end() &&
                 (*ptr)->order == (*ptr_nxt)->order &&
                 (*ptr)->order == (*ptr_nxt_sibling)->order)
        {
            ptr++;
            ptr_nxt++;
            ptr_nxt_sibling++;
        }
        else if ((*ptr)->order == (*ptr_nxt)->order)
        {
            BNode *temp;
            *ptr = mergeBNodes(*ptr, *ptr_nxt);
            ptr_nxt = heapList.erase(ptr_nxt);
            if (ptr_nxt_sibling != heapList.end())
                ptr_nxt_sibling++;
        }
    }
    return heapList;
}

list<BNode *> insertBNodeInHeap(list<BNode *> heapList, BNode *bNode)
{
    list<BNode *> tempList;
    tempList.push_back(bNode);
    tempList = combineBHeaps(heapList, tempList);
    return adjustBHeap(tempList);
}

list<BNode *> removeMinimum(BNode *tree)
{
    list<BNode *> heapList;
    BNode *temp = tree->child;
    BNode *temp1;

    while (temp)
    {
        temp1= temp;
        temp = temp->sibling;
        temp1->sibling = NULL;
        heapList.push_front(temp1);
    }
    return heapList;
}

list<BNode *> insertNode(list<BNode *> heapList, int val)
{
    BNode *temp = createBNode(val);
    return insertBNodeInHeap(heapList, temp);
}

BNode *findMinimum(list<BNode *> heapList)
{
    list<BNode *>::iterator it = heapList.begin();
    BNode *temp = *it;

    while (it != heapList.end())
    {
        if ((*it)->value < temp->value)
            temp = *it;
        it++;
    }
    return temp;
}

list<BNode *> extractMinimum(list<BNode *> heapList)
{
    list<BNode *> newHeapList, lo;
    BNode *temp;

    temp = findMinimum(heapList);
    list<BNode *>::iterator it;
    it = heapList.begin();

    while (it != heapList.end())
    {
        if (*it != temp)
        {
            newHeapList.push_back(*it);
        }
        it++;
    }
    lo = removeMinimum(temp);
    newHeapList = combineBHeaps(newHeapList, lo);
    cout << "Extract-Min returned " << temp->value << endl;
    fout << "Extract-Min returned " << temp->value << endl;
    newHeapList = adjustBHeap(newHeapList);
    return newHeapList;
}

void printTreeLevelOrder(BNode *root, int treeOrder)
{
    if (!root)
        return;

    queue<pair<BNode *, int>> q;
    q.push({root, 0});

    while (!q.empty())
    {
        int size = q.size();
        cout << "Level " << q.front().second << " : ";
        fout << "Level " << q.front().second << " : ";
        while (size--)
        {
            BNode *current = q.front().first;
            int level = q.front().second;
            q.pop();

            cout << current->value << " ";
            fout << current->value << " ";
            BNode *child = current->child;
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

void printHeapLevelOrder(list<BNode *> heapList)
{
    int binomialTreeIndex = 0;
    for (BNode *tree : heapList)
    {
        cout << "Binomial Tree, B" << tree->order << endl;
        fout << "Binomial Tree, B" << tree->order << endl;
        printTreeLevelOrder(tree, tree->order);
    }
}

BNode *unionMultipleValues(vector<int> &values)
{
    BNode *result = nullptr;

    for (int val : values)
    {
        BNode *temp = createBNode(val);
        if (!result)
            result = temp;
        else
            result = mergeBNodes(result, temp);
    }

    return result;
}

int main()
{
    int choice, val;
    list<BNode *> heapList;
    string str;
    while (fin >> str)
    {
        if (str == "I")
        {
            int x;
            fin >> x;
            heapList = insertNode(heapList, x);
        }
        if (str == "P")
        {
            cout << "Printing Binomial Heap..." << endl;
            fout << "Printing Binomial Heap..." << endl;
            printHeapLevelOrder(heapList);
        }

        if (str == "F")
        {
            BNode *temp = findMinimum(heapList);
            cout << "Find-Min returned " << temp->value << "\n";
            fout << "Find-Min returned " << temp->value << "\n";
        }
        if (str == "E")
        {
            heapList = extractMinimum(heapList);
        }
        if (str == "U")
        {
            string line;
            getline(fin, line); 
            istringstream iss(line);
            vector<int> values;
            int num;
            while (iss >> num)
            {
                values.push_back(num);
            }

            list<BNode *> heapList1;
            for (int x : values)
            {
                heapList1 = insertNode(heapList1, x);
            }

            heapList = combineBHeaps(heapList, heapList1);
            heapList = adjustBHeap(heapList);
        }
    }

    return 0;
}
