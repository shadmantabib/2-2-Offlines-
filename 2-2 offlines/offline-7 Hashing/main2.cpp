#include <bits/stdc++.h>

using namespace std;
#define NULLVAL INT_MIN
#define STRING_SIZE 5
typedef unsigned long long int u64;



bool isPrime(u64 num) {
    if (num == 2 || num == 3) {
        return true;
    }

    if (num == 1 || num % 2 == 0) {
        return false;
    }

    for (int i = 3; i*i <= num; i += 2) {
        if (num % i == 0){
            return false;
        }
    }
    return true;
}

u64 previousPrime (u64 num) {
    if (num % 2 == 0) {
        num--;
    }

    for ( ; !isPrime(num); num -= 2) { ; }
    return num;
}

u64 nextPrime (u64 num) {
    if (num % 2 == 0) {
        num++;
    }

    for ( ; !isPrime(num); num += 2) { ; }
    return num;
}


class PairNode {
    public:
        string key;
        int value;

    PairNode() {
        key = "";
        value = NULLVAL;
    }

    PairNode(string _key, int _value) {
        key = _key;
        value = _value;
    }

   
};


class HashTable {

    vector<PairNode> *table;
    bool *elementWasHere;

    int primebefore, NEXT_PRIME, TABLE_SIZE;
    int collisionCounter, probeCounter,counter;

    void rehash(u64 (*hashFunc)(string)) {
        int newSize = nextPrime(2 * TABLE_SIZE); // Double the size for rehashing
        vector<PairNode> *newTable = new vector<PairNode>[newSize];
        bool *newElementWasHere = new bool[newSize];

        for (int i = 0; i < newSize; i++) {
            newElementWasHere[i] = false;
        }

        for (int i = 0; i < TABLE_SIZE; i++) {
            for (int j = 0; j < table[i].size(); j++) {
                string key = table[i][j].key;
                int value = table[i][j].value;
                int hashIndex = hashFunc(key) % newSize;

                int probe = 1;
                while (!newTable[hashIndex].empty()) {
                    hashIndex = (hashFunc(key) + probe * auxHashFunc(key)) % newSize;
                    probe++;
                }

                newTable[hashIndex].push_back(PairNode(key, value));
                newElementWasHere[hashIndex] = true;
            }
        }

        // Clean up the old table and elementWasHere array
        delete[] table;
        delete[] elementWasHere;

        // Update variables
        table = newTable;
        elementWasHere = newElementWasHere;
        TABLE_SIZE = newSize;
        NEXT_PRIME = newSize;
    }
    
    u64 customProbHash(u64 (*hashFunc)(string), string key, int i) {
        u64 hash_value = 0;
        int C1 = 2, C2 = 3;
        hash_value = (hashFunc(key) + C1*i*auxHashFunc(key) + C2*i*i) % TABLE_SIZE;
        return hash_value;
    }

    u64 doubleHash(u64 (*hashFunc)(string), string s, int i) {
        u64 hash_value = 0;
        hash_value = (hashFunc(s) + i * auxHashFunc(s)) % TABLE_SIZE;
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
        NEXT_PRIME = nextPrime(tableSize);
        cout<<"flag "<<endl;
        primebefore = previousPrime(tableSize);

        TABLE_SIZE = NEXT_PRIME;
        table = new vector<PairNode>[TABLE_SIZE];
        elementWasHere = new bool[TABLE_SIZE];

        for (int i=0; i < TABLE_SIZE; i++) {
            elementWasHere[i] = false;
        }

        collisionCounter = 0;
        probeCounter = 0;
    }

    int getCollisionCounter() { return collisionCounter; }
    int getProbeCounter() { return probeCounter; }
     int Counter() { return counter; }


    /*
    #########################################
                Chaining Method
    #########################################
     */


    int searchChainHash (u64 (*hashFunc)(string), string key) {
        u64 hash_index = hashFunc(key) % TABLE_SIZE;
      
        for (int i=0; i < table[hash_index].size(); i++) {
               probeCounter++;
            if (table[hash_index].at(i).key == key) {
                return table[hash_index].at(i).value;
            }
           
        }
        return NULLVAL;
    }

   void insertChainHash(u64 (*hashFunc)(string), string key, int value) {
    if ((float)(counter + 1) / TABLE_SIZE > 0.5) {
        cout<<counter<<endl;
        rehash(hashFunc);
    }

    u64 hash_index = hashFunc(key) % TABLE_SIZE;
    int hash_index_size = table[hash_index].size();

    if (hash_index_size > 0) {
       collisionCounter++; 
    }
    table[hash_index].push_back(PairNode(key, value));
    counter++;
}

    void deleteChainHash (u64 (*hashFunc)(string), string key) {
        if (searchChainHash(*hashFunc, key) == NULLVAL) {
            cout << "This key isn't present in hash table. Unable to delete" << endl;
        }
        else {
            u64 hash_index = hashFunc(key) % TABLE_SIZE;
            for (int i=0; i < table[hash_index].size(); i++) {
                if (table[hash_index].at(i).key == key) {
                    table[hash_index].erase(table[hash_index].begin() + i);
                    cout << "The element has been erased from hash table" << endl;
                }
            }
        }
    }

    /*
    #########################################
            Double Hashing Method
    #########################################
     */

    int searchDoubleHash (u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = doubleHash(hashFunc, key, i);

        if (table[hash_index].empty() && !elementWasHere[hash_index]) {
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
                if (table[hash_index].empty() && !elementWasHere[hash_index]) {
                    break;
                }
            }
        }
        return NULLVAL;
    }

   void insertDoubleHash(u64 (*hashFunc)(string), string key, int value) {
   
    if ((float)(counter + 1) / TABLE_SIZE > 0.5) {
        cout<<counter<<endl;
        rehash(hashFunc);
    }

    int i = 0;
    u64 hash_index = 0;

    while (true) {
        hash_index = doubleHash(hashFunc, key, i);
        //cout << "index: " << hash_index << endl;
        if (table[hash_index].empty()) {
            table[hash_index].push_back(PairNode(key, value));
            elementWasHere[hash_index] = true;
            // the element is here now
            //cout << "inserted" << endl;
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

            if (table[hash_index].empty() && !elementWasHere[hash_index]) {
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
    }

    /*
    #########################################
            Custom Probing Method
    #########################################
     */

    int searchCustomProbHash(u64 (*hashFunc)(string), string key) {
        int i = 0;
        u64 hash_index = customProbHash(hashFunc, key, i);

        if (table[hash_index].empty() && !elementWasHere[hash_index]) {
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

                if (table[hash_index].empty() && !elementWasHere[hash_index]) {
                    break;
                }
            }
        }
        return NULLVAL;
    }

   void insertCustomProbHash(u64 (*hashFunc)(string), string key, int value) {
    if ((float)(counter+ 1) / TABLE_SIZE > 0.5) {
        rehash(hashFunc);
    }

    int i = 0;
    u64 hash_index = 0;

    while (true) {
        hash_index = customProbHash(hashFunc, key, i);
        //cout << "hash-index: " << hash_index << endl;

        if (table[hash_index].empty()) {
            table[hash_index].push_back(PairNode(key, value));
            elementWasHere[hash_index] = true;
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

            if (table[hash_index].empty() && !elementWasHere[hash_index]) {
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
    
    /*
    #########################################
        Diagnostics For Report Generation
    #########################################
     */

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


// Hash1 :: PolynomialRollHashFunction
u64 Hash1(string s) {
    u64 hash_value = 0;
    int PRC = 61;

    for (int i=0; i < s.size(); i++) {
        hash_value += int(s[i]) * pow(PRC, i);
    }
    return hash_value;
}

// Hash2 :: PowerHash Function
u64 Hash2(string s) {
    u64 hash_value = 0;
    for (int i=0; i < s.size(); i++) {
        hash_value += pow(int(s[i]), i);
    }
    return hash_value;
}



const string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool stringExists(string key, string dataSet[], int arraySize) {
    for (int i=0; i < arraySize; i++) {
        if (dataSet[i] == key) {
            return true;
        }
    }
    return false;
}

void createDataset(int sampleSize, string dataSet[], int arraySize) {

    while(sampleSize<=10){
    string sample = "";

    for (int i=0; i < sampleSize; i++) {
        sample += ALPHABET[rand() % ALPHABET.size()];
    }

    int uniqueCounter = 0;
    dataSet[uniqueCounter++] = sample;
    int repeat = 0;

    while (uniqueCounter < arraySize) {

        for (int i=0; i < sampleSize; i++) {
            sample[i] = ALPHABET[rand() % ALPHABET.size()];
        }

        if (!stringExists(sample, dataSet, arraySize)) {
            dataSet[uniqueCounter++] = sample;
        }
        else{
            repeat++;
        }
    }
    sampleSize++;
    }
}


/*
##################################################################################
##################################################################################
##################################################################################
*/


int main() {
    
    cout << "1.Check Insert,Delete,Find creating Dummy Data manually" << endl;
    cout << "2.Calculations for randomly genered data(10,000) having variable table size" << endl;
    cout << "Enter option: ";

    int option;
    cin >> option;

    if (option == 1) {

        cout << "Enter hash table size: ";
        int hashTableSize;
        cin >> hashTableSize;

        HashTable ht(hashTableSize);
        string key;
        int value;

        while (true) {

            cout << endl;
            cout << "1. Insert" << endl;
            cout << "2. Delete" << endl;
            cout << "3. Search" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter choice: ";
            cin >> option;

            if (option == 1) {
                cout << "Push your key and value having space between them";
                cin >> key >> value;

                if (ht.searchChainHash(Hash1, key) == NULLVAL) {
                    ht.insertChainHash(Hash1, key, value);
                    cout << "Key inserted" << endl;
                }
                else {
                    cout << "This key already exists." << endl;
                }
            }
            else if (option == 2) {
                cout << "Enter key to delete: ";
                cin >> key;

                if (ht.searchChainHash(Hash1, key) ==NULLVAL) {
                    cout << "This key doesn't exist." << endl;
                }
                else {
                    ht.deleteChainHash(Hash1, key);
                    cout << "Key deleted" << endl;
                }
            }
            else if (option == 3) {
                cout << "Enter key to search: ";
                cin >> key;

                if (ht.searchChainHash(Hash1, key) == NULLVAL) {
                    cout << "This key doesn't exist." << endl;
                }
                else {
                    cout << "Value for this key: " << ht.searchChainHash(Hash1, key) << endl;
                }
            }
            else {
                break;
            }
        }
    }
  
    else if (option == 2) {

        int dataSetSize;

        cout << "Enter Table size: ";
        cin >> dataSetSize;
        
        string dataSet[10000];
        createDataset(STRING_SIZE, dataSet, 10000);

        HashTable Hash1_Chaining_Method(dataSetSize);
        HashTable Hash1_Double_Hashing(dataSetSize);
        HashTable Hash1_Custom_Probing(dataSetSize);

        for (int i=0; i < 10000; i++) {
            //cout<<"tracer"<<endl;
            Hash1_Chaining_Method.insertChainHash(Hash1, dataSet[i], i+1);
            Hash1_Double_Hashing.insertDoubleHash(Hash1, dataSet[i], i+1);
            Hash1_Custom_Probing.insertCustomProbHash(Hash1, dataSet[i], i+1);
        }

        cout << endl;
        cout << "\t" << "::Hash1::" << endl;
        cout << "\t" << "Collision Count (out of 10,000)" << endl;
        cout << "\t" << "Chain Hash: " << Hash1_Chaining_Method.getCollisionCounter() << endl;
        cout << "\t" << "Double Hash: " << Hash1_Double_Hashing.getCollisionCounter() << endl;
        cout << "\t" << "Custom Probe Hash: " << Hash1_Custom_Probing.getCollisionCounter() << endl;
        
        Hash1_Chaining_Method.probeDataGeneration(Hash1, dataSet, 10000, 1);
        Hash1_Double_Hashing.probeDataGeneration(Hash1, dataSet, 10000, 2);
        Hash1_Custom_Probing.probeDataGeneration(Hash1, dataSet, 10000, 3);

        cout << endl;
        cout << "\t" << "Probe Count (out of 1,000)" << endl;
        cout << "\t" << "Chain Hash: " << Hash1_Chaining_Method.getProbeCounter() << endl;
        cout << "\t" << "Double Hash: " << Hash1_Double_Hashing.getProbeCounter() << endl;
        cout << "\t" << "Custom Probe Hash: " << Hash1_Custom_Probing.getProbeCounter() << endl;
        cout<<"hello"<<endl;
        cout << endl;

        HashTable Hash2_Chaining_Method(dataSetSize);
        HashTable Hash2_Double_Hashing(dataSetSize);
        HashTable Hash2_Custom_Probing(dataSetSize);
        cout<<"hello"<<endl;

        for (int i=0; i < 10000; i++) {
            Hash2_Chaining_Method.insertChainHash(Hash2, dataSet[i], i+1);
            Hash2_Double_Hashing.insertDoubleHash(Hash2, dataSet[i], i+1);
            Hash2_Custom_Probing.insertCustomProbHash(Hash2, dataSet[i], i+1);
        }

        cout << endl;
        cout << "\t" << "::Hash 2::" << endl;
        cout << "\t" << "Collision Count (out of 10,000)" << endl;
        cout << "\t" << "Chain Hash: " << Hash2_Chaining_Method.getCollisionCounter() << endl;
        cout << "\t" << "Double Hash: " << Hash2_Double_Hashing.getCollisionCounter() << endl;
        cout << "\t" << "Custom Probe Hash: " << Hash2_Custom_Probing.getCollisionCounter() << endl;
        
        Hash2_Chaining_Method.probeDataGeneration(Hash2, dataSet, 10000, 1);
        Hash2_Double_Hashing.probeDataGeneration(Hash2, dataSet, 10000, 2);
        Hash2_Custom_Probing.probeDataGeneration(Hash2, dataSet, 10000, 3);
        
        cout << endl;
        cout << "\t" << "Probe Count (out of 1,000)" << endl;
        cout << "\t" << "Chain Hash: " << Hash2_Chaining_Method.getProbeCounter() << endl;
        cout << "\t" << "Double Hash: " << Hash2_Double_Hashing.getProbeCounter() << endl;
        cout << "\t" << "Custom Probe Hash: " << Hash2_Custom_Probing.getProbeCounter() << endl;
        cout << endl;

    }

    return 0;
}