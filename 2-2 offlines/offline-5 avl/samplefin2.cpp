#include<bits/stdc++.h>
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
  // Get Height  
  int height(Node * r) {
    if (r == NULL)
      return -1;
    else {
      /* compute the height of each subtree */
      int lheight = height(r -> left);
      int rheight = height(r -> right);

      /* use the larger one */
      if (lheight > rheight)
        return (lheight + 1);
      else return (rheight + 1);
    }
  }

  // Get Balance factor of node N  
  int getBalanceFactor(Node * n) {
    if (n == NULL)
      return -1;
    return height(n -> left) - height(n -> right);
  }

  Node * rightRotate(Node * y) {
    Node * x = y -> left;
    Node * T2 = x -> right;

    // Perform rotation  
    x -> right = y;
    y -> left = T2;

    return x;
  }

  Node * leftRotate(Node * x) {
    Node * y = x -> right;
    Node * T2 = y -> left;

    // Perform rotation  
    y -> left = x;
    x -> right = T2;

    return y;
  }

  Node * insert(Node * r, Node * new_node) {
    if (r == NULL) {
      r = new_node;
      cout << "Value inserted successfully" << endl;
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

    /* return the (unchanged) node pointer */
    return r;

  }

  Node * minValueNode(Node * node) {
    Node * current = node;
    /* loop down to find the leftmost leaf */
    while (current -> left != NULL) {
      current = current -> left;
    }
    return current;
  }

  Node* deleteNode(Node* r, int v) {
    if (r == NULL) {
        return r;
    }
    if (v < r->value) {
        r->left = deleteNode(r->left, v);
    } else if (v > r->value) {
        r->right = deleteNode(r->right, v);
    } else {
        // Node to be deleted found

        // Node with only one child or no child
        if (r->left == NULL) {
            Node* temp = r->right;
            delete r;
            return temp;
        } else if (r->right == NULL) {
            Node* temp = r->left;
            delete r;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        Node* temp = minValueNode(r->right);
        r->value = temp->value;
        r->right = deleteNode(r->right, temp->value);
    }

    int bf = getBalanceFactor(r);
    // Left Left Imbalance/Case or Right rotation
    if (bf > 1 && getBalanceFactor(r->left) >= 0)
        return rightRotate(r);
    // Left Right Imbalance/Case or LR rotation
    else if (bf > 1 && getBalanceFactor(r->left) == -1) {
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }
    // Right Right Imbalance/Case or Left rotation
    else if (bf < -1 && getBalanceFactor(r->right) <= -0)
        return leftRotate(r);
    // Right Left Imbalance/Case or RL rotation
    else if (bf < -1 && getBalanceFactor(r->right) == 1) {
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }

    return r;
}

  void printPreorder(Node * r) //(current node, Left, Right) 
  {
    if (r == NULL)
      return;
    /* first print data of node */
    cout << r -> value << " ";
    /* then recur on left sutree */
    printPreorder(r -> left);
    /* now recur on right subtree */
    printPreorder(r -> right);
  }

  void printInorder(Node * r) //  (Left, current node, Right)
  {
    if (r == NULL)
      return;
    /* first recur on left child */
    printInorder(r -> left);
    /* then print the data of node */
    cout << r -> value << " ";
    fout << r -> value << " ";
    /* now recur on right child */
    printInorder(r -> right);
  }
  void printPostorder(Node * r) //(Left, Right, Root)
  {
    if (r == NULL)
      return;
    // first recur on left subtree 
    printPostorder(r -> left);
    // then recur on right subtree 
    printPostorder(r -> right);
    // now deal with the node 
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
  while(!fin.eof()){
        Node * new_node = new Node();
        fin>>ch2;
        if(ch2!="T"){
        fin>>ch3;
        double time_taken=0;
        if(ch2=="I"){
            
           
            ios_base::sync_with_stdio(false);
            new_node->value = stoi(ch3);
            obj.root= obj.insert(obj.root,new_node);
            
         
           
            obj.printPreorder1(obj.root);
            cout<<endl;
             fout<<endl;

        }
         if(ch2=="F"){
            new_node = obj.recursiveSearch(obj.root, stoi(ch3));
            if (new_node != NULL)
            {
                cout << "found" << endl;
                fout << "found" << endl;
            }
            else
            {
                cout << "not found" << endl;
                 fout << "not found" << endl;
            }

         }


         
         if(ch2=="D"){
            new_node = obj.recursiveSearch(obj.root, stoi(ch3));
            //fout<<new_node->value<<"he;;"<<endl;
            //cout<< new_node->value<<endl;
            
                //cout<<"NULL"<<endl;
                obj.deleteNode(obj.root, stoi(ch3));
                obj.printPreorder1(obj.root);
                cout<<endl;
                fout<<endl;
            
              //cout<< new_node->left->value<<endl;
                //cout<< new_node->right->value<<endl;

            //if (new_node != NULL)
            //{
            //    obj.deleteNode(obj.root, val);
            //    cout << "Value Deleted" << endl;
            //}

         }
        



      }
    else if(ch2=="T"){
             obj.printInorder(obj.root);
                 cout<<endl;
                 fout<<endl;

         }
  }


  

  return 0;
}