#include<bits/stdc++.h>
#include <chrono>
#include<fstream>
using namespace std;

ifstream fin("in.txt");
ofstream fout("out_avl.txt");
class Node {
  public:
    int value;
  Node * left;
  Node * right;
  int height;
  /*int height;
  int height(Node *N)
  {
    if (N == NULL)
        return 0;
    return N->height;
  }*/

  Node() {
    value = 0;
    left = NULL;
    right = NULL;
  }
  Node(int v) {
    value = v;
    left = NULL;
    right = NULL;
  }
};

class AVLTree {
  public:
    Node * root;
  AVLTree() {
    root = NULL;
  }
  bool isTreeEmpty() {
    if (root == NULL) {
      return true;
    } else {
      return false;
    }
  }

  int height(Node * r) {
    if (r == NULL)
      return -1;
    else {
     
      int lh = height(r -> left);
      int rh = height(r -> right);

      
      if (lh > rh)
        return (lh + 1);
      else return (rh + 1);
    }
  }


  int getBF(Node * n) {
    if (n == NULL)
      return -1;
    return height(n -> left) - height(n -> right);
  }

  Node * rightRotate(Node * y) {
    Node * x = y -> left;
    Node * T2 = x -> right;

   
    x -> right = y;
    y -> left = T2;

    return x;
  }

  Node * leftRotate(Node * x) {
    Node * y = x -> right;
    Node * T2 = y -> left;

 
    y -> left = x;
    x -> right = T2;

    return y;
  }

  Node * insert(Node * r, Node * new_node) {
    if (r == NULL) {
      r = new_node;
      //cout << "Value inserted succesfully" << endl;
      return r;
    }

    if (new_node -> value < r -> value) {
      r -> left = insert(r -> left, new_node);
    } else if (new_node -> value > r -> value) {
      r -> right = insert(r -> right, new_node);
    } else {
     // cout << "No duplicate values allowed!" << endl;
      return r;
    }

    int bf = getBF(r);
    
    if (bf > 1 && new_node -> value < r -> left -> value)
      return rightRotate(r);

    
    if (bf < -1 && new_node -> value > r -> right -> value)
      return leftRotate(r);

    
    if (bf > 1 && new_node -> value > r -> left -> value) {
      r -> left = leftRotate(r -> left);
      return rightRotate(r);
    }

    
    if (bf < -1 && new_node -> value < r -> right -> value) {
      r -> right = rightRotate(r -> right);
      return leftRotate(r);
    }

    
    return r;

  }

  Node * minValueNode(Node * node) {
    Node * current = node;
    
    while (current -> left != NULL) {
      current = current -> left;
    }
    return current;
  }

 Node * deleteNode(Node * r, int v) {
    
    if (r == NULL) {
      return NULL;
    }
    
    else if (v < r -> value) {
      r -> left = deleteNode(r -> left, v);
    }

    else if (v > r -> value) {
      r -> right = deleteNode(r -> right, v);
    }

    else {
      
      if (r -> left == NULL) {
        Node * temp = r -> right;
        delete r;
        return temp;
      } else if (r -> right == NULL) {
        Node * temp = r -> left;
        delete r;
        return temp;
      } else {
        
        Node * temp = minValueNode(r -> right);
  
        r -> value = temp -> value;
  
        r -> right = deleteNode(r -> right, temp -> value);
      }
    }

    int bf = getBF(r);
    
    if (bf == 2 && getBF(r -> left) >= 0)
      return rightRotate(r);
    
    else if (bf == 2 && getBF(r -> left) == -1) {
      r -> left = leftRotate(r -> left);
      return rightRotate(r);
    }
    
    else if (bf == -2 && getBF(r -> right) <= -0)
      return leftRotate(r);
   
    else if (bf == -2 && getBF(r -> right) == 1) {
      r -> right = rightRotate(r -> right);
      return leftRotate(r);
    }

    return r;
  }


  void printPreorder(Node * r) 
  {
    if (r == NULL)
      return;
 
   // cout << r -> value << " ";
    
    printPreorder(r -> left);
  
    printPreorder(r -> right);
  }

  void printInorder(Node * r) 
  {
    if (r == NULL)
      return;
   
    printInorder(r -> left);
    
    //cout << r -> value << " ";
    fout << r -> value << " ";

    printInorder(r -> right);
  }
  void printPostorder(Node * r) 
  {
    if (r == NULL)
      return;
   
    printPostorder(r -> left);
    
    printPostorder(r -> right);

    //cout << r -> value << " ";
  }
  void printPreorder1(Node * r){
        if (r == NULL)
            return;
        //cout << r -> value ;
        fout << r -> value ;
        if(r->left==NULL && r->right==NULL){
            return;
        }
        //cout<<"(";
         fout<<"(";
        printPreorder1(r -> left);

        //cout<<",";
        fout<<",";
       
        printPreorder1(r -> right);
        //cout<<")";
        fout<<")";

    }


  Node * iterativeSearch(int v) {
    if (root == NULL) {
      return root;
    } else {
      Node * temp = root;
      while (temp != NULL) {
        if (v == temp -> value) {
          return temp;
        } else if (v < temp -> value) {
          temp = temp -> left;
        } else {
          temp = temp -> right;
        }
      }
      return NULL;
    }
  }

  Node * recursiveSearch(Node * r, int val) {
    if (r == NULL || r -> value == val)
      return r;

    else if (val < r -> value)
      return recursiveSearch(r -> left, val);

    else
      return recursiveSearch(r -> right, val);
  }

};


int main() {
    AVLTree obj;
    int option, val;
    string ch;
    string ch2;
    string ch3;


    double insert_time = 0;
    double delete_time = 0;
    double search_time = 0;
    double traversal_time = 0;
    int ord=0;
    while (fin >> ch2) {
        Node* new_node = new Node();
        
        if (ch2 != "T") {
            fin >> ch3;

         
           
            if (ch2 == "I") {
              //fout<<++ord<<endl;
                
                new_node->value = stoi(ch3);
                auto start_time = chrono::high_resolution_clock::now();

                obj.root = obj.insert(obj.root, new_node);
                auto end_time = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000.0;
                insert_time += time_taken;
                 
                obj.printPreorder1(obj.root);
               // cout << endl;
                fout << endl;
            } else if (ch2 == "F") {
              // fout<<++ord<<endl;
               auto start_time = chrono::high_resolution_clock::now();
                new_node = obj.recursiveSearch(obj.root, stoi(ch3));
                auto end_time = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000.0;
                search_time += time_taken;
                if (new_node != NULL) {
                    //cout << "found" << endl;
                    fout << "found" << endl;
                } else {
                    //cout << "not found" << endl;
                    fout << "not found" << endl;
                }
            } else if (ch2 == "D") {
              //fout<<++ord<<endl;
               
                new_node = obj.recursiveSearch(obj.root, stoi(ch3));
                auto start_time = chrono::high_resolution_clock::now();
                obj.root=obj.deleteNode(obj.root, stoi(ch3));
                auto end_time = chrono::high_resolution_clock::now();
                double time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000.0;
                delete_time += time_taken;
                obj.printPreorder1(obj.root);
                //cout << endl;
                fout << endl;
            }
            
            
        }
        else if (ch2 == "T") {
            
            
            //fout<<++ord<<endl;
            auto start_time = chrono::high_resolution_clock::now();
            obj.printInorder(obj.root);
            auto end_time = chrono::high_resolution_clock::now();
            traversal_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000.0;
            //cout << endl;
            fout << endl;

            
           
        }
    }


    ofstream report("report_avl.txt");
    report << "operation time(ms)" << endl;
    report << "insert " << insert_time << endl;
    report << "delete " << delete_time << endl;
    report << "search " << search_time << endl;
    report << "trav " << traversal_time << endl;
    double total_time = insert_time + delete_time + search_time + traversal_time;
    report << "total " << total_time << endl;
    report.close();

    return 0;
}

