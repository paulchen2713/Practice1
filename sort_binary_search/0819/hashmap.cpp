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

void initialize(std::string file_path, std::unordered_map<std::string, int>& umap) {
    std::ifstream ifs(file_path);
    std::string line;
    while (std::getline(ifs, line)) {
        std::stringstream stream(line);
        std::string key;
        int value;
        while (stream >> key >> value) {
            // std::cout << tag << " " << value << "\n";
            umap.insert(std::pair<std::string, int>(key, value));
        }
    }
    ifs.close();
}

void print_map(const std::unordered_map<std::string, int>& umap) {
    for (const std::pair<std::string, int>& a : umap) {
        std::cout << "key: " << a.first << ", val: " << a.second << "\n";
    }
    std::cout << "size: " << umap.size() << "\n";
}

bool brute_force_search(std::unordered_map<std::string, int>& umap, int target_val) {
    for (const std::pair<std::string, int>& a : umap) {
        if (a.second == target_val) {
            std::cout << a.first << " ";
            return true;
        }
    }
    return false;
}

bool brute_force_search(std::unordered_map<std::string, int>& umap, std::string target_key) {
    for (const std::pair<std::string, int>& a : umap) {
        if (a.first == target_key) {
            std::cout << "Found " << target_key << " " << a.second << "\n";
            return true;
        }
    }
    std::cout << "Could not found " << target_key << "\n";
    return false;
}

std::vector<std::pair<std::string, int>> quick_sort(const std::unordered_map<std::string, int>& umap) {
    std::vector<std::pair<std::string, int>> elements(umap.begin(), umap.end());
    std::sort(elements.begin(), elements.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
        return a.second < b.second;
    });
    for (int i = 0; i < elements.size(); i++) {
        std::cout << i << " ";
        std::cout << elements[i].first << " " << elements[i].second << "\n";
    }
    std::cout << "size: " << elements.size() << "\n";
    return elements;
}

int binary_search(const std::vector<std::pair<std::string, int>>& arr, int target) {
    const int n = arr.size();
    int left = 0, right = n;
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (arr[middle].second == target) {
            return middle;
        }
        else if (target > arr[middle].second) {
            left = middle + 1;
        }
        else if (target < arr[middle].second) {
            right = middle;
        }
    }
    return -1;
}

int first_occur(const std::vector<std::pair<std::string, int>>& arr, int target) {
    int index = binary_search(arr, target);
    if (index == -1) return -1;
    for (int i = index; i > 0 && arr[i].second == target; i--) {
        index = i;
    }
    return index;
}

int main() {
    std::unordered_map<std::string, int> umap;
    std::vector<std::pair<std::string, int>> sorted;

    // read data from file
    int file_index = 2;
    // std::cout << "please enter the file index (e.g. 1~4): ";
    // std::cin >> file_index;
    
    std::string file_path = "D:/C++/sort_binary_search/Input" + std::to_string(file_index) + ".txt";
    initialize(file_path, umap); // buffer

    int val = 937;
    // std::cout << "please enter an integer to be searched: ";
    // std::cin >> val;

    sorted = quick_sort(umap);
    int index = first_occur(sorted, val);
    std::cout << "binary search 1st occur index: " << index << std::endl;
    
    // brute_force_search(umap, val);
    // std::cout << "\n";
    // brute_force_search(umap, "A100");

    // print_map(umap);

    std::cout << "Input File: " << file_path << "\n";

    

    // write results to a file
    std::string out_file_name = "D:/C++/sort_binary_search/test" + std::to_string(file_index) + "_result.txt";
    // std::ofstream ofs;
    // ofs.open(out_file_name);

    // ofs.close();

    std::cout << "Output File: " << out_file_name << "\n\n";
    return 0;
}
