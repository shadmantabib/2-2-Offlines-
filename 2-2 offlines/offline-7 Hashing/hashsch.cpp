#include <bits/stdc++.h>
using namespace std;
#define minsz 5
typedef unsigned long long int u64;
#define NULLVAL INT_MIN
ofstream fout("output.txt");



bool primeChecker(u64 n) {
    if (n == 2 || n == 3) {
        return true;
    }

    if (n == 1 || n % 2 == 0) {
        return false;
    }

    for (int i = 3; i*i <= n; i += 2) {
        if (n % i == 0){
            return false;
        }
    }
    return true;
}

u64 prevPrime(u64 n) {
    if (n % 2 == 0) {
        n--;
    }

    while (!primeChecker(n)) {
        n -= 2;
    }
    return n;
}


u64 nextPrime (u64 n) {
    if (n % 2 == 0) {
        n++;
    }

   while (!primeChecker(n)) {
        n += 2;
    }
    return n;
}


class keyval {
    public:
        string key;
        int value;

    keyval() {
        key = "";
        value = NULLVAL;
    }

    keyval(string _key, int _value) {
        key = _key;
        value = _value;
    }

   
};


class HashTable {

    vector<keyval> *table;
    bool *prevMarker;

    int primebefore, primeafter, tblsz;
    int collisionCounter, probeCounter,counter;
    /*
    
    Using rehashing here so to maintain efficiency of probing and collsion.
    Moreover,the various table size data shows I have to store 10k elements into
    nearer 5k sized table.So rehashing is used maintaining load factor less than 
    0.5
    
    */
    void rehash(u64 (*hashFunc)(string)) {
        int newSize = nextPrime(2 * tblsz); 
        vector<keyval> *newTable = new vector<keyval>[newSize];
        bool *newprevMarker = new bool[newSize];

        for (int i = 0; i < newSize; i++) {
            newprevMarker[i] = false;
        }

        for (int i = 0; i < tblsz; i++) {
            for (int j = 0; j < table[i].size(); j++) {
                string key = table[i][j].key;
                int value = table[i][j].value;
                int hashIndex = hashFunc(key) % newSize;

                int probe = 1;
                while (!newTable[hashIndex].empty()) {
                    hashIndex = (hashFunc(key) + probe * auxHashFunc(key)) % newSize;
                    probe++;
                }

                newTable[hashIndex].push_back(keyval(key, value));
                newprevMarker[hashIndex] = true;
            }
        }

        // Clean up the old table and prevMarker array
        delete[] table;
        delete[] prevMarker;

        // Update variables
        table = newTable;
        prevMarker = newprevMarker;
        tblsz = newSize;
        primeafter = newSize;
    }
    
    u64 customProbHash(u64 (*hashFunc)(string), string key, int i) {
        u64 hash_value = 0;
        int C1 = 2, C2 = 3;
        hash_value = (hashFunc(key) + C1*i*auxHashFunc(key) + C2*i*i) % tblsz;
        return hash_value;
    }

    u64 doubleHash(u64 (*hashFunc)(string), string s, int i) {
        u64 hash_value = 0;
        hash_value = (hashFunc(s) + i * auxHashFunc(s)) % tblsz;
        return hash_value;
    }

    u64 auxHashFunc(string s) {
        u64 hash_value = 0;
        for (int i=0; i < s.size(); i++) {
            hash_value += int(s[i]);
        }
        hash_value = primebefore - (hash_value % primebefore);
        return hash_value;
    }

public:

    HashTable(int tableSize) {
        primeafter = nextPrime(tableSize);
        //cout<<"flag "<<endl;
        primebefore =prevPrime(tableSize);

        tblsz = primeafter;
        table = new vector<keyval>[tblsz];
        prevMarker = new bool[tblsz];

        for (int i=0; i < tblsz; i++) {
            prevMarker[i] = false;
        }

        collisionCounter = 0;
        probeCounter = 0;
    }

    int getCollisionCounter() { return collisionCounter; }
    int getProbeCounter() { return probeCounter; }
    int Counter() { return counter; }

    int searchChainHash (u64 (*hashFunc)(string), string key) {
        u64 hash_index = hashFunc(key) % tblsz;
      
        for (int i=0; i < table[hash_index].size(); i++) {
               probeCounter++;
            if (table[hash_index].at(i).key == key) {
                return table[hash_index].at(i).value;
            }
           
        }
        return NULLVAL;
    }

   void insertChainHash(u64 (*hashFunc)(string), string key, int value) {
    if ((float)(counter + 1) / tblsz > 0.5) {
        //cout<<counter<<endl;
        rehash(hashFunc);
    }

    u64 hash_index = hashFunc(key) % tblsz;
    int hash_index_size = table[hash_index].size();

    if (hash_index_size > 0) {
       collisionCounter++; 
    }
    table[hash_index].push_back(keyval(key, value));
    counter++;
}

    void deleteChainHash (u64 (*hashFunc)(string), string key) {
        if (searchChainHash(*hashFunc, key) == NULLVAL) {
            cout << "Not in the table,can not delete" << endl;
        }
        else {
            u64 hash_index = hashFunc(key) % tblsz;
            for (int i=0; i < table[hash_index].size(); i++) {
                if (table[hash_index].at(i).key == key) {
                    table[hash_index].erase(table[hash_index].begin() + i);
                    cout << "The element has been erased from hash table" << endl;
                }
            }
        }
    }


    int searchDoubleHash (u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = doubleHash(hashFunc, key, i);

        if (table[hash_index].empty() && !prevMarker[hash_index]) {
            return NULLVAL;
        }
        else {
            while (true) {
                probeCounter++;

                if (table[hash_index].at(0).key == key) {
                    return table[hash_index].at(0).value;
                }
                i++;
                hash_index = doubleHash(hashFunc, key, i);

                // if any element wasn't there and the place is empty, then break it
                if (table[hash_index].empty() && !prevMarker[hash_index]) {
                    break;
                }
            }
        }
        return NULLVAL;
    }

   void insertDoubleHash(u64 (*hashFunc)(string), string key, int value) {
   
    if ((float)(counter + 1) / tblsz > 0.5) {
        //cout<<counter<<endl;
        rehash(hashFunc);
    }

    int i = 0;
    u64 hash_index = 0;

    while (true) {
        hash_index = doubleHash(hashFunc, key, i);
        
        if (table[hash_index].empty()) {
            table[hash_index].push_back(keyval(key, value));
            prevMarker[hash_index] = true;
            // the element is here now
           
            break;
        } else {
            collisionCounter++;
        }
        i++;
    }
    counter++;
}

    void deleteDoubleHash (u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = 0;

        while (true) {
            hash_index = doubleHash(hashFunc, key, i);

            if (table[hash_index].empty() && !prevMarker[hash_index]) {
                cout << "Unable to find ...cannot delete" << endl;
                break;
            }
            else {
                if (table[hash_index].size() > 0) {
                    if (table[hash_index].at(0).key == key) {
                        table[hash_index].erase(table[hash_index].begin());
                        cout << "Deleted" << endl;
                        break;
                    }
                }                
                i++;
            }
        }
    }



    int searchCustomProbHash(u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = customProbHash(hashFunc, key, i);

        if (table[hash_index].empty() && !prevMarker[hash_index]) {
            return NULLVAL;
        }
        else {
            while (true) {
                probeCounter++;

                if (table[hash_index].at(0).key == key) {
                    return table[hash_index].at(0).value;
                }
                i++;
                hash_index = customProbHash(hashFunc, key, i);

                if (table[hash_index].empty() && !prevMarker[hash_index]) {
                    break;
                }
            }
        }
        return NULLVAL;
    }

   void insertCustomProbHash(u64 (*hashFunc)(string), string key, int value) {
    if ((float)(counter+ 1) / tblsz > 0.5) {
        rehash(hashFunc);
    }

    int i = 0;
    u64 hash_index = 0;

    while (true) {
        hash_index = customProbHash(hashFunc, key, i);
        //cout << "hash-index: " << hash_index << endl;

        if (table[hash_index].empty()) {
            table[hash_index].push_back(keyval(key, value));
            prevMarker[hash_index] = true;
            //cout << "inserted:2" << endl;
            break;
        } else {
            collisionCounter++;
        }
        i++;
    }
    counter++;
}

    void deleteCustomProbHash(u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = 0;

        while (true) {
            hash_index = customProbHash(hashFunc, key, i);

            if (table[hash_index].empty() && !prevMarker[hash_index]) {
                cout << "The doesn't exists in hash table. Unable to delete" << endl;
                break;
            }
            else {
                if (table[hash_index].size() > 0) {    
                    if (table[hash_index].at(0).key == key) {
                        table[hash_index].erase(table[hash_index].begin());
                        cout << "The key has been delete from hash table" << endl;
                        break;
                    }
                }
                i++;
            }
        }
        counter++;
    }
    

    void probeDataGeneration(u64 (*hashFunc)(string), string *dataSet, int dataSetSize, int method) {

        bool visited[dataSetSize];
        for (int i=0; i < dataSetSize; i++) {
            visited[i] = false;
        }

        int inserted = 0, idx;
        while(inserted < 1000) {
            idx = rand() % dataSetSize;

            if (!visited[idx]) {
                if (method == 1){
                    searchChainHash(hashFunc, dataSet[idx]);
                   
                }
                else if (method == 2){
                    searchDoubleHash(hashFunc, dataSet[idx]);
                  
                }
                else if (method == 3){
                    searchCustomProbHash(hashFunc, dataSet[idx]);   
                    
                }             
                inserted++;
            }
        }
        
    }
    

};

//  PolynomialRollHashFunction
u64 Hash1(string s) {
    u64 hash_value = 0;
    int PRC = 61;

    for (int i=0; i < s.size(); i++) {
        hash_value += int(s[i]) * pow(PRC, i);
    }
    return hash_value;
}

//  PowerHash Function
u64 Hash2(string s) {
    u64 hash_value = 0;
    for (int i=0; i < s.size(); i++) {
        hash_value += pow(int(s[i]), i);
    }
    return hash_value;
}



const string stringsalph = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool stringfinder(string key, string ds[], int arraySize) {
    for (int i=0; i < arraySize; i++) {
        if (ds[i] == key) {
            return true;
        }
    }
    return false;
}

void createds(int sampleSize, string ds[], int arraySize) {
    string sample = "";

    
    int length = 5 + rand() % 6;
    for (int i=0; i <  length; i++) {
        sample += stringsalph[rand() % stringsalph.size()];
    }
    
    //cout<<sample<<endl;

    int uniqueCounter = 0;
    ds[uniqueCounter++] = sample;
    int iter = 0;

    while (uniqueCounter < arraySize) {

        for (int i=0; i < sampleSize; i++) {
            sample[i] = stringsalph[rand() % stringsalph.size()];
        }

        if (!stringfinder(sample, ds, arraySize)) {
            ds[uniqueCounter] = sample;
            uniqueCounter++;
        }
        else{
            iter++;
        }
    }
}


int main() {
    
    cout << "1.Check Insert,Delete,Find creating Dummy Data manually" << endl;
    cout << "2.Calculations for randomly genered data(10,000) having variable table size" << endl;
    cout << "Enter choice : ";

    int choice ;
    cin >> choice ;

    if (choice  == 1) {

        
        int htsz;
        cout<<"please enter your manual table size"<<endl;
        cin >> htsz;

        HashTable ht(htsz);
        string key;
        int value;

        while (true) {

            cout << endl;
            cout << "1. Insert" << endl;
            cout << "2. Delete" << endl;
            cout << "3. Search" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            cin >> choice ;

            if (choice  == 1) {
                cout << "Push your key and value having space between them";
                cin >> key >> value;

                if (ht.searchChainHash(Hash1, key) == NULLVAL) {
                    ht.insertChainHash(Hash1, key, value);
                    cout << "Key inserted successfully" << endl;
                }
                else {
                    cout << "This key already exists." << endl;
                }
            }
            else if (choice  == 2) {
                cout << "Enter key to delete: ";
                cin >> key;

                if (ht.searchChainHash(Hash1, key) == NULLVAL) {
                    cout << "This key doesn't exist." << endl;
                }
                else {
                    ht.deleteChainHash(Hash1, key);
                    cout << "Key deleted" << endl;
                }
            }
            else if (choice  == 3) {
                cout << "Enter key to search: ";
                cin >> key;

                if (ht.searchChainHash(Hash1, key) == NULLVAL) {
                    cout << "This key doesn't exist." << endl;
                }
                else {
                    cout << "Value: " << ht.searchChainHash(Hash1, key) << endl;
                }
            }
            else {
                break;
            }
        }
    }
  
    else if (choice  == 2) {

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

        for (int i=0; i < 10000; i++) {
            //cout<<"tracer"<<endl;
            h1chain.insertChainHash(Hash1, ds[i], i+1);
           h1doublehash.insertDoubleHash(Hash1, ds[i], i+1);
            h1custProbe.insertCustomProbHash(Hash1, ds[i], i+1);
        }

        cout << endl;
         fout << endl;
        cout << "\t" << "Data Summary for Hash1" << endl;
         fout << "\t" << "Data Summary for Hash1" << endl;
        cout  << "Collision Count (out of 10,000)" << endl;
          fout << "Collision Count (out of 10,000)" << endl;
        cout  << "Chain Hash: " <<h1chain.getCollisionCounter() << endl;
         fout  << "Chain Hash: " <<h1chain.getCollisionCounter() << endl;
        cout  << "Double Hash: " <<h1doublehash.getCollisionCounter() << endl;
          fout  << "Double Hash: " <<h1doublehash.getCollisionCounter() << endl;
        cout  << "Custom Probe Hash: " << h1custProbe.getCollisionCounter() << endl;
       fout  << "Custom Probe Hash: " << h1custProbe.getCollisionCounter() << endl;
       h1chain.probeDataGeneration(Hash1, ds, 10000, 1);
       h1doublehash.probeDataGeneration(Hash1, ds, 10000, 2);
       h1custProbe.probeDataGeneration(Hash1, ds, 10000, 3);

        cout << endl;
        fout << endl;
        cout << "\t" << "Average Probe Count (out of 1,000)" << endl;
           fout << "\t" << "Average Probe Count (out of 1,000)" << endl;
        cout << "Chain Hash: " <<h1chain.getProbeCounter()/1000.0 << endl;
        fout << "Chain Hash: " <<h1chain.getProbeCounter()/1000.0 << endl;
        cout << "Double Hash: " <<h1doublehash.getProbeCounter()/1000.0 << endl;
         fout << "Double Hash: " <<h1doublehash.getProbeCounter() /1000.0<< endl;
        cout << "Custom Probe Hash: " << h1custProbe.getProbeCounter()/1000.0 << endl;
        fout << "Custom Probe Hash: " << h1custProbe.getProbeCounter()/1000.0 << endl;
       // cout<<"hello"<<endl;
        cout << endl;
        fout<<endl;
        HashTable h2chain(tablesz);
        HashTable h2doublehash(tablesz);
        HashTable h2custprobe(tablesz);
        //cout<<"hello"<<endl;

        for (int i=0; i < 10000; i++) {
            h2chain.insertChainHash(Hash2, ds[i], i+1);
            h2doublehash.insertDoubleHash(Hash2, ds[i], i+1);
            h2custprobe.insertCustomProbHash(Hash2, ds[i], i+1);
        }

        cout << endl;
         fout << endl;
        cout << "\t" << "Data Summary for Hash2" << endl;
        fout << "\t" << "Data Summary for Hash2" << endl;
        cout  << "Collision Count (out of 10,000)" << endl;
         fout  << "Collision Count (out of 10,000)" << endl;
        cout  << "Chain Hash: " << h2chain.getCollisionCounter() << endl;
        fout  << "Chain Hash: " << h2chain.getCollisionCounter() << endl;
        cout << "Double Hash: " << h2doublehash.getCollisionCounter() << endl;
        fout  << "Double Hash: " << h2doublehash.getCollisionCounter() << endl;
        cout << "Custom Probe Hash: " << h2custprobe.getCollisionCounter() << endl;
         fout  << "Custom Probe Hash: " << h2custprobe.getCollisionCounter() << endl;
        
        h2chain.probeDataGeneration(Hash2, ds, 10000, 1);
        h2doublehash.probeDataGeneration(Hash2, ds, 10000, 2);
        h2custprobe.probeDataGeneration(Hash2, ds, 10000, 3);
        
        cout << endl;
        fout << endl;
        cout << "\t" << "Average Probe Count (out of 1,000)" << endl;
         fout << "\t" << "Average Probe Count (out of 1,000)" << endl;
        cout << "Chain Hash: " << h2chain.getProbeCounter()/1000.0 << endl;
         fout << "Chain Hash: " << h2chain.getProbeCounter()/1000.0 << endl;
        cout << "Double Hash: " << h2doublehash.getProbeCounter() /1000.0<< endl;
          fout  << "Double Hash: " << h2doublehash.getProbeCounter()/1000.0 << endl;
        cout << "Custom Probe Hash: " << h2custprobe.getProbeCounter()/1000.0 << endl;
          fout  << "Custom Probe Hash: " << h2custprobe.getProbeCounter()/1000.0 << endl;
        cout << endl;
          fout  << endl;

    }

    
}