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
     
      int lheight = height(r -> left);
      int rheight = height(r -> right);

      
      if (lheight > rheight)
        return (lheight + 1);
      else return (rheight + 1);
    }
  }


  int getBalanceFactor(Node * n) {
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
      cout << "Value inserted succesfully" << endl;
      return r;
    }

    if (new_node -> value < r -> value) {
      r -> left = insert(r -> left, new_node);
    } else if (new_node -> value > r -> value) {
      r -> right = insert(r -> right, new_node);
    } else {
      cout << "No duplicate values allowed!" << endl;
      return r;
    }

    int bf = getBalanceFactor(r);
    // Left Left Case  
    if (bf > 1 && new_node -> value < r -> left -> value)
      return rightRotate(r);

    // Right Right Case  
    if (bf < -1 && new_node -> value > r -> right -> value)
      return leftRotate(r);

    // Left Right Case  
    if (bf > 1 && new_node -> value > r -> left -> value) {
      r -> left = leftRotate(r -> left);
      return rightRotate(r);
    }

    // Right Left Case  
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
    // base case 
    if (r == NULL) {
      return NULL;
    }
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    else if (v < r -> value) {
      r -> left = deleteNode(r -> left, v);
    }
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (v > r -> value) {
      r -> right = deleteNode(r -> right, v);
    }
    // if key is same as root's key, then This is the node to be deleted 
    else {
      // node with only one child or no child 
      if (r -> left == NULL) {
        Node * temp = r -> right;
        delete r;
        return temp;
      } else if (r -> right == NULL) {
        Node * temp = r -> left;
        delete r;
        return temp;
      } else {
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        Node * temp = minValueNode(r -> right);
        // Copy the inorder successor's content to this node 
        r -> value = temp -> value;
        // Delete the inorder successor 
        r -> right = deleteNode(r -> right, temp -> value);
        //deleteNode(r->right, temp->value); 
      }
    }

    int bf = getBalanceFactor(r);
    // Left Left Imbalance/Case or Right rotation 
    if (bf == 2 && getBalanceFactor(r -> left) >= 0)
      return rightRotate(r);
    // Left Right Imbalance/Case or LR rotation 
    else if (bf == 2 && getBalanceFactor(r -> left) == -1) {
      r -> left = leftRotate(r -> left);
      return rightRotate(r);
    }
    // Right Right Imbalance/Case or Left rotation	
    else if (bf == -2 && getBalanceFactor(r -> right) <= -0)
      return leftRotate(r);
    // Right Left Imbalance/Case or RL rotation 
    else if (bf == -2 && getBalanceFactor(r -> right) == 1) {
      r -> right = rightRotate(r -> right);
      return leftRotate(r);
    }

    return r;
  }

  void printPreorder(Node * r) //(current node, Left, Right) 
  {
    if (r == NULL)
      return;
 
    cout << r -> value << " ";
    
    printPreorder(r -> left);
  
    printPreorder(r -> right);
  }

  void printInorder(Node * r) //  (Left, current node, Right)
  {
    if (r == NULL)
      return;
   
    printInorder(r -> left);
    
    cout << r -> value << " ";
    fout << r -> value << " ";

    printInorder(r -> right);
  }
  void printPostorder(Node * r) //(Left, Right, Root)
  {
    if (r == NULL)
      return;
   
    printPostorder(r -> left);
    
    printPostorder(r -> right);

    cout << r -> value << " ";
  }
  void printPreorder1(Node * r){
        if (r == NULL)
            return;
        cout << r -> value ;
        fout << r -> value ;
        if(r->left==NULL && r->right==NULL){
            return;
        }
        cout<<"(";
         fout<<"(";
        printPreorder1(r -> left);

        cout<<",";
        fout<<",";
       
        printPreorder1(r -> right);
        cout<<")";
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
    string ch2;
    string ch3;


    double insert_time = 0;
    double delete_time = 0;
    double search_time = 0;
    double traversal_time = 0;

    while (!fin.eof()) {
        Node* new_node = new Node();
        fin >> ch2;
        if (ch2 != "T") {
            fin >> ch3;

         
            auto start_time = chrono::high_resolution_clock::now();

            if (ch2 == "I") {
                ios_base::sync_with_stdio(false);
                new_node->value = stoi(ch3);
                obj.root = obj.insert(obj.root, new_node);

                obj.printPreorder1(obj.root);
                cout << endl;
                fout << endl;
            } else if (ch2 == "F") {
                new_node = obj.recursiveSearch(obj.root, stoi(ch3));
                if (new_node != NULL) {
                    cout << "found" << endl;
                    fout << "found" << endl;
                } else {
                    cout << "not found" << endl;
                    fout << "not found" << endl;
                }
            } else if (ch2 == "D") {
                new_node = obj.recursiveSearch(obj.root, stoi(ch3));
                
                obj.deleteNode(obj.root, stoi(ch3));
                obj.printPreorder1(obj.root);
                cout << endl;
                fout << endl;
            }
            
            

            auto end_time = chrono::high_resolution_clock::now();
            double time_taken = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000.0;


            if (ch2 == "I") {
                insert_time += time_taken;
            } else if (ch2 == "F") {
                search_time += time_taken;
            } else if (ch2 == "D") {
                delete_time += time_taken;
            }
        } else if (ch2 == "T") {
            
            auto start_time = chrono::high_resolution_clock::now();

            obj.printInorder(obj.root);
            cout << endl;
            fout << endl;

            
            auto end_time = chrono::high_resolution_clock::now();
            traversal_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count() / 1000.0;
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
