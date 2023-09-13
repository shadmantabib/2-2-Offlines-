#include <bits/stdc++.h>
using namespace std;
#define minsz 5
typedef unsigned long long int ul;
ofstream fout("output.txt");

bool primeChecker(ul n)
{
    if (n == 2 || n == 3)
    {
        return true;
    }

    if (n == 1 || n % 2 == 0)
    {
        return false;
    }

    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

ul prevPrime(ul n)
{
    if (n % 2 == 0)
    {
        n--;
    }

    while (!primeChecker(n))
    {
        n -= 2;
    }
    return n;
}

ul nextPrime(ul n)
{
    if (n % 2 == 0)
    {
        n++;
    }

    while (!primeChecker(n))
    {
        n += 2;
    }
    return n;
}

class keyval
{
public:
    string key;
    int value;

    keyval()
    {
        key = "";
        value = INT_MIN;
    }

    keyval(string _key, int _value)
    {
        key = _key;
        value = _value;
    }
};

class HashTable
{

    vector<keyval> *table;
    bool *prevMarker;

    int primebefore, primeafter, tblsz;
    int collisionCounter, probeCounter, counter,maxc;
    /*

    Using rehashing here so to maintain efficiency of probing and collsion.
    Moreover,the various table size data shows I have to store 10k elements into
    nearer 5k sized table.So rehashing is used maintaining load factor less than
    0.5

    */
     void rehashchaindel(ul (*hashFunc)(string))
    {
        int newSize = nextPrime(0.8 * tblsz);
        vector<keyval> *newTable = new vector<keyval>[newSize];
        bool *newprevMarker = new bool[newSize];

        for (int i = 0; i < newSize; i++)
        {
            newprevMarker[i] = false;
        }

        for (int i = 0; i < tblsz; i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                string key = table[i][j].key;
                int value = table[i][j].value;
                int hash_index = hashFunc(key) % newSize;

                newTable[hash_index].push_back(keyval(key, value));
                newprevMarker[hash_index] = true;
            }
        }
        

        // Clean up the old table and prevMarker array
        delete[] table;
        delete[] prevMarker;

        table = newTable;
        prevMarker = newprevMarker;
        tblsz = newSize;
        primeafter = newSize;
    }
    void rehashchain(ul (*hashFunc)(string))
    {
        int newSize = nextPrime(1.2 * tblsz);
        vector<keyval> *newTable = new vector<keyval>[newSize];
        bool *newprevMarker = new bool[newSize];

        for (int i = 0; i < newSize; i++)
        {
            newprevMarker[i] = false;
        }

        for (int i = 0; i < tblsz; i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                string key = table[i][j].key;
                int value = table[i][j].value;
                int hash_index = hashFunc(key) % newSize;

                newTable[hash_index].push_back(keyval(key, value));
                newprevMarker[hash_index] = true;
            }
        }
        

        // Clean up the old table and prevMarker array
        delete[] table;
        delete[] prevMarker;

        table = newTable;
        prevMarker = newprevMarker;
        tblsz = newSize;
        primeafter = newSize;
    }

    ul customProbHash(ul (*hashFunc)(string), string key, int i)
    {
        ul hash_value = 0;
        int C1 = 2, C2 = 3;
        hash_value = (hashFunc(key) + C1 * i * auxHashFunc(key) + C2 * i * i) % tblsz;
        return hash_value;
    }

    ul doubleHash(ul (*hashFunc)(string), string s, int i)
    {
        ul hash_value = 0;
        hash_value = (hashFunc(s) + i * auxHashFunc(s)) % tblsz;
        return hash_value;
    }

    ul auxHashFunc(string s)
    {
        ul hash_value = 0;
        for (int i = 0; i < s.size(); i++)
        {
            hash_value += int(s[i]);
        }
        hash_value = primebefore - (hash_value % primebefore);
        return hash_value;
    }
    void rehashcustomProbe(ul (*hashFunc)(string))
    {
        int newSize = nextPrime(2 * tblsz);
        vector<keyval> *newTable = new vector<keyval>[newSize];
        bool *newprevMarker = new bool[newSize];

        for (int i = 0; i < newSize; i++)
        {
            newprevMarker[i] = false;
        }

        for (int i = 0; i < tblsz; i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                string key = table[i][j].key;
                int value = table[i][j].value;
                int hash_index = hashFunc(key) % newSize;

                int probe = 1;
                while (!newTable[hash_index].empty())
                {
                    hash_index = customProbHash(hashFunc, key, probe) % newSize;
                    probe++;
                }

                newTable[hash_index].push_back(keyval(key, value));
                newprevMarker[hash_index] = true;
            }
        }

        // Clean up the old table and prevMarker array
        delete[] table;
        delete[] prevMarker;

        table = newTable;
        prevMarker = newprevMarker;
        tblsz = newSize;
        primeafter = newSize;
    }

    void rehashdoubleHash(ul (*hashFunc)(string))
    {
        int newSize = nextPrime(2 * tblsz);
        vector<keyval> *newTable = new vector<keyval>[newSize];
        bool *newprevMarker = new bool[newSize];

        for (int i = 0; i < newSize; i++)
        {
            newprevMarker[i] = false;
        }

        for (int i = 0; i < tblsz; i++)
        {
            for (int j = 0; j < table[i].size(); j++)
            {
                string key = table[i][j].key;
                int value = table[i][j].value;
                int hash_index = hashFunc(key) % newSize;
                int i = 0;

                while (!newTable[hash_index].empty())
                {
                    hash_index = doubleHash(hashFunc, key, i) % newSize;
                    i++;
                }

                newTable[hash_index].push_back(keyval(key, value));
                newprevMarker[hash_index] = true;
            }
        }

        // Clean up the old table and prevMarker array
        delete[] table;
        delete[] prevMarker;

        table = newTable;
        prevMarker = newprevMarker;
        tblsz = newSize;
        primeafter = newSize;
    }

public:
    HashTable(int tableSize)
    {
        primeafter = nextPrime(tableSize);
        // cout<<"flag "<<endl;
        primebefore = prevPrime(tableSize);

        tblsz = primeafter;
        table = new vector<keyval>[tblsz];
        prevMarker = new bool[tblsz];

        for (int i = 0; i < tblsz; i++)
        {
            prevMarker[i] = false;
        }

        collisionCounter = 0;
        probeCounter = 0;
        maxc=0;
    }

    int getCollisionCounter() { return collisionCounter; }
    int getProbeCounter() { return probeCounter; }
    int Counter() { return counter; }

    int find_ChainHash(ul (*hashFunc)(string), string key)
    {
        ul h_ind = hashFunc(key) % tblsz;

        for (int i = 0; i < table[h_ind].size(); i++)
        {
            probeCounter++;
            if (table[h_ind][i].key == key)
            {
                return table[h_ind][i].value;
            }
        }
        return INT_MIN;
    }

    void insertChainHash(ul (*hashFunc)(string), string key, int value)
    {

        if ((float)(counter) / tblsz > 0.5)
        {
            // cout<<counter<<endl;
            rehashchain(hashFunc);
        }

        ul h_ind = hashFunc(key) % tblsz;
        int h_ind_size = table[h_ind].size();
        maxc=max(maxc, h_ind_size);
        if(counter%100==0 && maxc>10){
            rehashchain(hashFunc);
        }
        
        if (h_ind_size > 0)
        {
            collisionCounter++;
        }
        /*
        if (h_index>0){
            collisionCounter+= h_ind_size;
        }
        */
        table[h_ind].push_back(keyval(key, value));
        counter++;
    }

    void deleteChainHash(ul (*hashFunc)(string), string key,int inserted)
    {
        if (find_ChainHash(*hashFunc, key) == INT_MIN)
        {
            cout << "Not in the table,can not delete" << endl;
        }
        
        else
        {
            ul h_ind = hashFunc(key) % tblsz;
            
            
            int h_ind_size=table[h_ind].size();
            maxc=max(maxc, h_ind_size);
            if(maxc<3){
                rehashchaindel(hashFunc);

            }
            for (int i = 0; i < table[h_ind].size(); i++)
            {
                if (table[h_ind][i].key == key)
                {
                    table[h_ind].erase(table[h_ind].begin() + i);
                    cout << "The element has been erased from hash table" << endl;
                }
            }
        }
    }

    int find_Double(ul (*hashFunc)(string), string key)
    {
        int i = 0;
        ul h_ind = doubleHash(hashFunc, key, i);

        while (!(table[h_ind].empty() && !prevMarker[h_ind]))
        {
            probeCounter++;

            if (table[h_ind][0].key == key)
            {
                return table[h_ind][0].value;
            }

            i++;
            h_ind = doubleHash(hashFunc, key, i);
        }

        return INT_MIN;
    }

    void insertDoubleHash(ul (*hashFunc)(string), string key, int value)
    {

        if ((float)(counter) / tblsz > 0.5)
        {
            // cout<<counter<<endl;
            rehashdoubleHash(hashFunc);
        }

        int i = 0;
        ul h_ind = 0;

        while (true)
        {
            h_ind = doubleHash(hashFunc, key, i);

            if (table[h_ind].empty())
            {
                table[h_ind].push_back(keyval(key, value));
                prevMarker[h_ind] = true;
                

                break;
            }
            else
            {
                collisionCounter++;
            }
            i++;
        }
        counter++;
    }

    void deleteDoubleHash(ul (*hashFunc)(string), string key)
    {
        int i = 0;
        ul h_ind = 0;

        while (true)
        {
            h_ind = doubleHash(hashFunc, key, i);

            if (table[h_ind].empty() && !prevMarker[h_ind])
            {
                cout << "Unable to find ...cannot delete" << endl;
                break;
            }
            else
            {
                if (table[h_ind].size() > 0)
                {
                    if (table[h_ind].at(0).key == key)
                    {
                        table[h_ind].erase(table[h_ind].begin());
                        cout << "Deleted" << endl;
                        break;
                    }
                }
                i++;
            }
        }
    }

    int find_custprobe(ul (*hashFunc)(string), string key)
    {
        int i = 0;
        ul h_ind = customProbHash(hashFunc, key, i);

        if (table[h_ind].empty() && !prevMarker[h_ind])
        {
            return INT_MIN;
        }
        else
        {
            while (true)
            {
                probeCounter++;

                if (table[h_ind][0].key == key)
                {
                    return table[h_ind][0].value;
                }
                i++;
                h_ind = customProbHash(hashFunc, key, i);

                if (table[h_ind].empty() && !prevMarker[h_ind])
                {
                    break;
                }
            }
        }
        return INT_MIN;
    }

    void insertCustomProbHash(ul (*hashFunc)(string), string key, int value)
    {
        if ((float)(counter) / tblsz > 0.5)
        {
            rehashcustomProbe(hashFunc);
        }

        int i = 0;
        ul h_ind = 0;

        while (true)
        {
            h_ind = customProbHash(hashFunc, key, i);

            if (table[h_ind].empty())
            {
                table[h_ind].push_back(keyval(key, value));
                prevMarker[h_ind] = true;

                break;
            }
            else
            {
                collisionCounter++;
            }
            i++;
        }
        counter++;
    }

    void deleteCustomProbHash(ul (*hashFunc)(string), string key)
    {
        int i = 0;
        ul h_ind = 0;

        while (true)
        {
            h_ind = customProbHash(hashFunc, key, i);

            if (table[h_ind].empty() && !prevMarker[h_ind])
            {
                cout << "The doesn't exists in hash table. Unable to delete" << endl;
                break;
            }
            else
            {
                if (table[h_ind].size() > 0)
                {
                    if (table[h_ind][0].key == key)
                    {
                        table[h_ind].erase(table[h_ind].begin());
                        cout << "The key has been delete from hash table" << endl;
                        break;
                    }
                }
                i++;
            }
        }
        counter++;
    }
    void deleteDataGeneration(ul (*hashFunc)(string), string *dataSet, int dataSetSize, int method)
    {

        method=1;
        bool visited[dataSetSize];
        for (int i = 0; i < dataSetSize; i++)
        {
            visited[i] = false;
        }

        int inserted = 0, idx;
        while (inserted < 1000)
        {
            idx = rand() % dataSetSize;

            if (!visited[idx])
            {
                if (method == 1)
                {
                    //find_ChainHash(hashFunc, dataSet[idx]);
                    deleteChainHash(hashFunc, dataSet[idx],inserted);
                    
                }
                else if (method == 2)
                {
                    find_Double(hashFunc, dataSet[idx]);
                }
                else if (method == 3)
                {
                    find_custprobe(hashFunc, dataSet[idx]);
                }
                inserted++;
            }
        }
    }

    void probeDataGeneration(ul (*hashFunc)(string), string *dataSet, int dataSetSize, int method)
    {

        bool visited[dataSetSize];
        for (int i = 0; i < dataSetSize; i++)
        {
            visited[i] = false;
        }

        int inserted = 0, idx;
        while (inserted < 1000)
        {
            idx = rand() % dataSetSize;

            if (!visited[idx])
            {
                if (method == 1)
                {
                    find_ChainHash(hashFunc, dataSet[idx]);
                   // deleteChainHash(hashFunc, dataSet[idx],inserted);
                    
                }
                else if (method == 2)
                {
                    find_Double(hashFunc, dataSet[idx]);
                }
                else if (method == 3)
                {
                    find_custprobe(hashFunc, dataSet[idx]);
                }
                inserted++;
            }
        }
    }
};

//  PolynomialRollHashFunction
ul Hash1(string s)
{
    ul hash_value = 0;
    int PRC = 61;

    for (int i = 0; i < s.size(); i++)
    {
        hash_value += int(s[i]) * pow(PRC, i);
    }
    return hash_value;
}

//  PowerHash Function
ul Hash2(string s)
{
    ul hash_value = 0;
    for (int i = 0; i < s.size(); i++)
    {
        hash_value += pow(int(s[i]), i);
    }
    return hash_value;
}

const string stringsalph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool stringfinder(string key, string ds[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        if (ds[i] == key)
        {
            return true;
        }
    }
    return false;
}

void createds(int sampleSize, string ds[], int arraySize)
{
    string sample = "";

    int length = sampleSize + rand() % 6;
    for (int i = 0; i < length; i++)
    {
        sample += stringsalph[rand() % stringsalph.size()];
    }

    // cout<<sample<<endl;

    int uniqueCounter = 0;
    ds[uniqueCounter++] = sample;
    int iter = 0;

    while (uniqueCounter < arraySize)
    {
        
        int len = sampleSize + rand() % 6;
        for (int i = 0; i < len; i++)
        {
            sample[i] = stringsalph[rand() % stringsalph.size()];
        }

        if (!stringfinder(sample, ds, arraySize))
        {
            ds[uniqueCounter] = sample;
            uniqueCounter++;
        }
        else
        {
            iter++;
        }
    }
}

int main()
{
    int seed = 103;
    srand(seed);

    cout << "1.Check Insert,Delete,Find creating Dummy Data manually" << endl;
    cout << "2.Calculations for randomly genered data(10,000) having variable table size" << endl;
    cout << "Enter choice : ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {

        int htsz;
        cout << "please enter your manual table size" << endl;
        cin >> htsz;

        HashTable ht(htsz);
        string key;
        int value;

        while (true)
        {

            cout << endl;
            cout << "1. Insert" << endl;
            cout << "2. Delete" << endl;
            cout << "3. Search" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1)
            {
                cout << "Push your key and value having space between them" << endl;
                cin >> key >> value;

                if (ht.find_ChainHash(Hash1, key) == INT_MIN)
                {
                    ht.insertChainHash(Hash1, key, value);
                    cout << "Key inserted successfully" << endl;
                }
                else
                {
                    cout << "This key already exists." << endl;
                }
            }
            else if (choice == 2)
            {
                cout << "Enter key to delete: ";
                cin >> key;

                if (ht.find_ChainHash(Hash1, key) == INT_MIN)
                {
                    cout << "This key doesn't exist." << endl;
                }
                else
                {
                    ht.deleteChainHash(Hash1, key,5);
                    cout << "Key deleted" << endl;
                }
            }
            else if (choice == 3)
            {
                cout << "Enter key to search: ";
                cin >> key;

                if (ht.find_ChainHash(Hash1, key) == INT_MIN)
                {
                    cout << "This key doesn't exist." << endl;
                }
                else
                {
                    cout << "Value: " << ht.find_ChainHash(Hash1, key) << endl;
                }
            }
            else
            {
                break;
            }
        }
    }

    else if (choice == 2)
    {

        int tablesz;

        cout << "Enter Table size: ";
        cin >> tablesz;

        string ds[10000];
        /*
        Since I have to use same 10000 data for each of the hashing having variable length
        I have hardcoded the datSize ds
        */
        createds(minsz, ds, 10000);

        HashTable h1chain(tablesz);
        HashTable h1doublehash(tablesz);
        HashTable h1custProbe(tablesz);

        for (int i = 0; i < 10000; i++)
        {
            // cout<<"tracer"<<endl;
            h1chain.insertChainHash(Hash1, ds[i], i + 1);
            h1doublehash.insertDoubleHash(Hash1, ds[i], i + 1);
            h1custProbe.insertCustomProbHash(Hash1, ds[i], i + 1);
        }

        cout << endl;
        fout << endl;
        cout << "\t"
             << "Data Summary for Hash1" << endl;
        fout << "\t"
             << "Data Summary for Hash1" << endl;
        cout << "Collision Count (out of 10,000)" << endl;
        fout << "Collision Count (out of 10,000)" << endl;
        cout << "Chain Hash: " << h1chain.getCollisionCounter() << endl;
        fout << "Chain Hash: " << h1chain.getCollisionCounter() << endl;
        cout << "Double Hash: " << h1doublehash.getCollisionCounter() << endl;
        fout << "Double Hash: " << h1doublehash.getCollisionCounter() << endl;
        cout << "Custom Probe Hash: " << h1custProbe.getCollisionCounter() << endl;
        fout << "Custom Probe Hash: " << h1custProbe.getCollisionCounter() << endl;
        h1chain.probeDataGeneration(Hash1, ds, 10000, 1);
        h1doublehash.probeDataGeneration(Hash1, ds, 10000, 2);
        h1custProbe.probeDataGeneration(Hash1, ds, 10000, 3);

        cout << endl;
        fout << endl;
        cout << "\t"
             << "Average Probe Count (out of 1,000)" << endl;
        fout << "\t"
             << "Average Probe Count (out of 1,000)" << endl;
        cout << "Chain Hash: " << h1chain.getProbeCounter() / 1000.0 << endl;
        fout << "Chain Hash: " << h1chain.getProbeCounter() / 1000.0 << endl;
        cout << "Double Hash: " << h1doublehash.getProbeCounter() / 1000.0 << endl;
        fout << "Double Hash: " << h1doublehash.getProbeCounter() / 1000.0 << endl;
        cout << "Custom Probe Hash: " << h1custProbe.getProbeCounter() / 1000.0 << endl;
        fout << "Custom Probe Hash: " << h1custProbe.getProbeCounter() / 1000.0 << endl;
        // cout<<"hello"<<endl;
        cout << endl;
        fout << endl;
        HashTable h2chain(tablesz);
        HashTable h2doublehash(tablesz);
        HashTable h2custprobe(tablesz);
        // cout<<"hello"<<endl;

        for (int i = 0; i < 10000; i++)
        {
            h2chain.insertChainHash(Hash2, ds[i], i + 1);
            h2doublehash.insertDoubleHash(Hash2, ds[i], i + 1);
            h2custprobe.insertCustomProbHash(Hash2, ds[i], i + 1);
        }

        cout << endl;
        fout << endl;
        cout << "\t"
             << "Data Summary for Hash2" << endl;
        fout << "\t"
             << "Data Summary for Hash2" << endl;
        cout << "Collision Count (out of 10,000)" << endl;
        fout << "Collision Count (out of 10,000)" << endl;
        cout << "Chain Hash: " << h2chain.getCollisionCounter() << endl;
        fout << "Chain Hash: " << h2chain.getCollisionCounter() << endl;
        cout << "Double Hash: " << h2doublehash.getCollisionCounter() << endl;
        fout << "Double Hash: " << h2doublehash.getCollisionCounter() << endl;
        cout << "Custom Probe Hash: " << h2custprobe.getCollisionCounter() << endl;
        fout << "Custom Probe Hash: " << h2custprobe.getCollisionCounter() << endl;

        h2chain.probeDataGeneration(Hash2, ds, 10000, 1);
        h2doublehash.probeDataGeneration(Hash2, ds, 10000, 2);
        h2custprobe.probeDataGeneration(Hash2, ds, 10000, 3);

        cout << endl;
        fout << endl;
        cout << "\t"
             << "Average Probe Count (out of 1,000)" << endl;
        fout << "\t"
             << "Average Probe Count (out of 1,000)" << endl;
        cout << "Chain Hash: " << h2chain.getProbeCounter() / 1000.0 << endl;
        fout << "Chain Hash: " << h2chain.getProbeCounter() / 1000.0 << endl;
        cout << "Double Hash: " << h2doublehash.getProbeCounter() / 1000.0 << endl;
        fout << "Double Hash: " << h2doublehash.getProbeCounter() / 1000.0 << endl;
        cout << "Custom Probe Hash: " << h2custprobe.getProbeCounter() / 1000.0 << endl;
        fout << "Custom Probe Hash: " << h2custprobe.getProbeCounter() / 1000.0 << endl;
        cout << endl;
        fout << endl;
    }
}