#include <bits/stdc++.h>
// using namespace std;

struct Node {
    std::string tag;
    int value;
    struct Node *left, *right;
};

class BinaryTree {
private:
    struct Node* root;
    struct Node* return_node;

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
                // return_node = ptr;
                return true;
            }
            if (key <= ptr->value) {
                return search(key, ptr->left);
            } 
            else if (key > ptr->value) {
                return search(key, ptr->right);
            }
        } 
        else if (ptr == nullptr) {
            std::cout << "\nCould not find " << key << std::endl;
            return false;
        }
        return false;
    }

    // struct Node* search2(int key, struct Node* ptr) {
    //     if (ptr != nullptr) {
    //         if (key == ptr->value) {
    //             std::cout << "Found " << ptr->value << std::endl;
    //             return ptr;
    //         }
    //         if (key <= ptr->value) {
    //             return search2(key, ptr->left);
    //         } 
    //         else {
    //             return search2(key, ptr->right);
    //         }
    //     } 
    //     else if (ptr == nullptr) {
    //         std::cout << "\nCould not find " << key << std::endl;
    //         return nullptr;
    //     }
    //     return nullptr;
    // }

    void displayTree() {
        displayTree(root);
    }

    void displayTree(struct Node* ptr) {
        if (ptr != nullptr) {
            displayTree(ptr->left);
            std::cout << ptr->tag << " " << ptr->value << std::endl;
            displayTree(ptr->right);
        }
    }

    void store_results(struct Node* ptr, std::ofstream& ofs) {
        if (ptr != nullptr && ofs.is_open()) {
            store_results(ptr->left, ofs);
            ofs << ptr->tag << " " << ptr->value << "\n";
            store_results(ptr->right, ofs);
        }
    }
    
    bool is_empty() {
        return root == nullptr;
    }

    struct Node* get_root() {
        return root;
    }

    struct Node* get_return_node() {
        return return_node;
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
    struct Node* root = bin_tree.get_root();

    // read data from file
    int file_index = 1;
    std::cout << "please enter the file index (e.g. 1~4): ";
    std::cin >> file_index;
    
    std::string file_path = "D:/C++/sort_binary_search/Input" + std::to_string(file_index) + ".txt";

    bin_tree = built_tree(file_path, bin_tree);

    int val = 754;
    std::cout << "please enter an integer to be searched: ";
    std::cin >> val;

    std::cout << "file path: " << file_path << "\n";

    std::cout << "\n";
    bin_tree.search(val);
    
    // write results to a file
    std::string out_file_name = "test" + std::to_string(file_index) + "_result.txt";
    std::ofstream ofs(out_file_name);

    
    // bool isFound = bin_tree.search(val);
    // if (isFound == true) {
    //     struct Node* return_node = bin_tree.get_return_node();
    //     ofs << "Found " << return_node->tag << " " << return_node->value << "\n\n";
    // }
    // else if (isFound == false) {
    //     ofs << "Could not Found " << val << "\n\n";
    // }
    bin_tree.store_results(root, ofs);
    

    // struct Node* return_node = bin_tree.search2(val, root);
    // if (return_node != nullptr) {
    //     ofs << "Found " << return_node->tag << " " << return_node->value << "\n\n";
    // }
    // else if (return_node == nullptr) {
    //     ofs << "Could not Found " << val << "\n\n";
    // }
    // bin_tree.store_results(root, ofs);

    std::cout << "\n";
    // std::cout << "sorted results: \n";
    bin_tree.displayTree();
    std::cout << "\n";
    
    // bin_tree.search(val);
    ofs.close();
    return 0;
}

/*
PS D:\C++\sort_binary_search> ./practice3.exe
please enter the file index (e.g. 1~4): 1
please enter an integer to be searched: 754
file path: D:/C++/sort_binary_search/Input1.txt

Found 754

A11 40
A13 61
A17 62
A5 139
A23 148
A18 183
A7 223
A19 280
A14 295
A21 356
A8 357
A10 421
A15 520
A20 534
A9 620
A3 630
A16 666
A2 751
A1 754
A22 779
A6 856
A12 911
A4 944
*/

