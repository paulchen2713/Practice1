#include <bits/stdc++.h>
// using namespace std;

struct Node {
    std::string tag;
    int value;
    struct Node* left, *right;
};

class BinaryTree {
private:
    struct Node *root;

public:
    BinaryTree() {
        root = nullptr;
    };

    void insert(std::string tag, int value) {
        // struct Node *p = new Node;
        struct Node* p = (struct Node*)calloc(1, sizeof(struct Node));
        struct Node* parent;
        
        p->tag = tag;
        p->value = value;
        p->left = p->right = nullptr;
        parent = nullptr;
        
        if (is_empty()) {
            root = p;
        } 
        else if (!is_empty()) {
            struct Node* ptr;
            ptr = root;
            while (ptr != nullptr) {
                parent = ptr;
                if (value > ptr->value) {
                    ptr = ptr->right;
                } 
                else {
                    ptr = ptr->left;
                }
            }
            if (value < parent->value) {
                parent->left = p;
            } 
            else {
                parent->right = p;
            }
        }
    };

    bool search(int key) {
        return search(key, root);
    };

    bool search(int key, struct Node* ptr) {
        if (ptr != nullptr) {
            if (key == ptr->value) {
                std::cout << "Found " << ptr->value << std::endl;
                return true;
            }
            if (key <= ptr->value) {
                return search(key, ptr->left);
            } 
            else {
                return search(key, ptr->right);
            }
        } 
        else if (ptr == nullptr) {
            std::cout << "\nCould not find " << key << std::endl;
            return false;
        }
        return false;
    }

    void displayTree() {
        displayTree(root);
    }

    void displayTree(struct Node* ptr) {
        if (ptr != nullptr) {
            displayTree(ptr->left);
            std::cout << ptr->tag << " " << ptr->value << std::endl;
            displayTree(ptr->right);
        }
    };
    
    bool is_empty() {
        return root == nullptr;
    }

    struct Node* get_root() {
        return root;
    }
    
    struct Node* emptyBST(struct Node* root) {
        struct Node* temp;
        
        if (root != nullptr) {
     
            // Traverse to left subtree
            emptyBST(root->left);
     
            // Traverse to right subtree
            emptyBST(root->right);
     
            std::cout << "\nReleased node: " << root->value;
            temp = root;
     
            // Require for free memory
            free(temp);
        }
        return root;
    }
};

void read_file(std::string file_path) {
    std::ifstream ifs(file_path);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream stream(line);
        std::string tag;
        int value;
        while (stream >> tag >> value) {
            std::cout << tag << " " << value << "\n";
        }
    }
    std::cout << "\n";
}

BinaryTree built_tree(std::string file_path, BinaryTree bin_tree) {
    std::ifstream ifs(file_path);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream stream(line);
        std::string tag;
        int value;
        while (stream >> tag >> value) {
            // std::cout << tag << " " << value << "\n";
            bin_tree.insert(tag, value);
        }
    }
    return bin_tree;
}

int main() {
    // construct an empty tree
    BinaryTree bin_tree;

    // read data from file
    int file_index = 1;
    // std::cout << "please enter the file index (e.g. 1~4): ";
    // std::cin >> file_index;
     
    std::string file_path = "D:/C++/sort_binary_search/Input" + std::to_string(file_index) + ".txt";
    // std::cout << file_path << "\n";

    bin_tree = built_tree(file_path, bin_tree);

    int val = 754;
    // std::cout << "please enter an integer to be searched: ";
    // std::cin >> val;

    std::cout << "\n";
    bin_tree.search(val);
    
    std::cout << "\n";
    // std::cout << "sorted results: \n";
    bin_tree.displayTree();
    std::cout << "\n";
    
    // bin_tree.search(val);
    return 0;
}


