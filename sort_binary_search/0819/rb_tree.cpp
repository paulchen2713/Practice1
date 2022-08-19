#include <bits/stdc++.h>
// using namespace std;

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
    ifs.close();
    std::cout << "\n";
}

void initialize(std::string file_path, std::map<std::string, int>& rb_tree) {
    std::ifstream ifs(file_path);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream stream(line);
        std::string key;
        int value;
        while (stream >> key >> value) {
            // std::string new_key = std::to_string(value) + "_" + key;
            // std::cout << new_key << " " << value << "\n";
            rb_tree.insert(std::pair<std::string, int>(key, value));
        }
    }
    ifs.close();
}

void print(std::map<std::string, int>& rb_tree) {
    for (const std::pair<std::string, int>& a : rb_tree) {
        // std::cout << "key: " << a.first.substr(std::to_string(a.second).size() + 1) << ", val: " << a.second << "\n";
        std::cout << "key: " << a.first << ", val: " << a.second << "\n";
    }
    std::cout << "size: " << rb_tree.size() << "\n";
}

// void quick_sort()

// bool binary_search()

int main() {
    std::map<std::string, int> rb_tree;

    // read data from file
    int file_index = 1;
    // std::cout << "please enter the file index (e.g. 1~4): ";
    // std::cin >> file_index;
    
    std::string file_path = "D:/C++/sort_binary_search/Input" + std::to_string(file_index) + ".txt";
    initialize(file_path, rb_tree);

    int val = 754;
    // std::cout << "please enter an integer to be searched: ";
    // std::cin >> val;

    std::cout << "Input File: " << file_path << "\n";

    print(rb_tree);

    // write results to a file
    std::string out_file_name = "D:/C++/sort_binary_search/test" + std::to_string(file_index) + "_result.txt";
    // std::ofstream ofs;
    // ofs.open(out_file_name);

    // ofs.close();

    std::cout << "Output File: " << out_file_name << "\n\n";
    return 0;
}
