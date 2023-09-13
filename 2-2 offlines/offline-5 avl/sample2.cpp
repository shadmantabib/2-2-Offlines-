#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#define SPACE 10
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode() {
        value = 0;
        left = NULL;
        right = NULL;
    }
    TreeNode(int v) {
        value = v;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
public:
    TreeNode* root;
    AVLTree() {
        root = NULL;
    }
    // Rest of the AVL tree implementation

    // ...

     bool isTreeEmpty() {
    if (root == NULL) {
      return true;
    } else {
      return false;
    }
  }
  // Get Height  
  int height(TreeNode * r) {
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
  int getBalanceFactor(TreeNode * n) {
    if (n == NULL)
      return -1;
    return height(n -> left) - height(n -> right);
  }

  TreeNode * rightRotate(TreeNode * y) {
    TreeNode * x = y -> left;
    TreeNode * T2 = x -> right;

    // Perform rotation  
    x -> right = y;
    y -> left = T2;

    return x;
  }

  TreeNode * leftRotate(TreeNode * x) {
    TreeNode * y = x -> right;
    TreeNode * T2 = y -> left;

    // Perform rotation  
    y -> left = x;
    x -> right = T2;

    return y;
  }

  TreeNode * insert(TreeNode * r, TreeNode * new_node) {
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

  TreeNode * minValueNode(TreeNode * node) {
    TreeNode * current = node;
    /* loop down to find the leftmost leaf */
    while (current -> left != NULL) {
      current = current -> left;
    }
    return current;
  }

  TreeNode * deleteNode(TreeNode * r, int v) {
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
        TreeNode * temp = r -> right;
        delete r;
        return temp;
      } else if (r -> right == NULL) {
        TreeNode * temp = r -> left;
        delete r;
        return temp;
      } else {
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree) 
        TreeNode * temp = minValueNode(r -> right);
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

  void print2D(TreeNode * r, int space) {
    if (r == NULL) // Base case  1
      return;
    space += SPACE; // Increase distance between levels   2
    print2D(r -> right, space); // Process right child first 3 
    cout << endl;
    for (int i = SPACE; i < space; i++) // 5 
      cout << " "; // 5.1  
    cout << r -> value << "\n"; // 6
    print2D(r -> left, space); // Process left child  7
  }
  void printPreorder(TreeNode * r) //(current node, Left, Right) 
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

 vector<int> traverse(TreeNode* r) {
    vector<int> result;
    traverseHelper(r, result);
    return result;
  }
  void traverseHelper(TreeNode* r, vector<int>& result) {
    if (r == NULL)
        return;
    // first recur on left child
    traverseHelper(r->left, result);
    // then add the data of node to the result
    result.push_back(r->value);
    // now recur on right child
    traverseHelper(r->right, result);
 }
  void printPostorder(TreeNode * r) //(Left, Right, Root)
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

  /* Print nodes at a given level */
  void printGivenLevel(TreeNode * r, int level) {
    if (r == NULL)
      return;
    else if (level == 0)
      cout << r -> value << " ";
    else // level > 0  
    {
      printGivenLevel(r -> left, level - 1);
      printGivenLevel(r -> right, level - 1);
    }
  }
  void printLevelOrderBFS(TreeNode * r) {
    int h = height(r);
    for (int i = 0; i <= h; i++)
      printGivenLevel(r, i);
  }

  TreeNode * iterativeSearch(int v) {
    if (root == NULL) {
      return root;
    } else {
      TreeNode * temp = root;
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

  TreeNode * recursiveSearch(TreeNode * r, int val) {
    if (r == NULL || r -> value == val)
      return r;

    else if (val < r -> value)
      return recursiveSearch(r -> left, val);

    else
      return recursiveSearch(r -> right, val);
  }
};

vector<string> parse_input(const string& file_path) {
    ifstream input_file(file_path);
    vector<string> lines;
    string line;
    while (getline(input_file, line)) {
        lines.push_back(line);
    }
    input_file.close();
    return lines;
}

void write_output(const string& file_path, const vector<string>& lines) {
    ofstream output_file(file_path);
    for (const string& line : lines) {
        output_file << line << endl;
    }
    output_file.close();
}

int main() {
    const string input_file = "in.txt";
    const string output_avl_file = "out_avl.txt";
    const string report_file = "report_avl.txt";

    vector<string> input_operations = parse_input(input_file);
    AVLTree avl_tree;
    vector<string> output_avl, report;
    clock_t start_time, end_time;

    for (const string& operation : input_operations) {
        char op;
        int key;
        sscanf(operation.c_str(), "%c %d", &op, &key);

        start_time = clock();

        if (op == 'I') {
            TreeNode* new_node = new TreeNode(key);
            avl_tree.root = avl_tree.insert(avl_tree.root, new_node);
        }
        else if (op == 'D') {
            avl_tree.root = avl_tree.deleteNode(avl_tree.root, key);
        }
        else if (op == 'F') {
            TreeNode* result_node = avl_tree.recursiveSearch(avl_tree.root, key);
            if (result_node != NULL) {
                output_avl.push_back("found");
            }
            else {
                output_avl.push_back("not found");
            }
        }
        else if (op == 'T') {
            vector<int> traversal_result = avl_tree.traverse(avl_tree.root);
            string result_str;
            for (int i = 0; i < traversal_result.size(); ++i) {
                if (i > 0) result_str += " ";
                result_str += to_string(traversal_result[i]);
            }
            output_avl.push_back(result_str);
        }

        end_time = clock();
        double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC * 1000.0;
        report.push_back(operation + " " + to_string(time_taken));
    }

    write_output(output_avl_file, output_avl);
    write_output(report_file, report);

    return 0;
}
