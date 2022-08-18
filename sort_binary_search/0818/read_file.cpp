#include <bits/stdc++.h>
// using namespace std;

void read_file(const std::string& file_path) {
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

void test(int file_index) {
    // int file_index = 1;
    std::string file_path = "D:/C++/sort_binary_search/Input" + std::to_string(file_index) + ".txt";
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

int main() {
    // read data from file
    int file_index = 1;
    std::string file_path = "D:/C++/sort_binary_search/Input" + std::to_string(file_index) + ".txt";
    std::cout << file_path << "\n";

    read_file(file_path);

    test(file_index);

    return 0;
}
