#include <bits/stdc++.h>
// using namespace std;

std::vector<std::vector<int>> transpose(std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("Error: input matrix is empty");
    }
    const int m = matrix.size(), n = matrix[0].size();
    std::vector<std::vector<int>> result(n, std::vector<int>(m));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

std::vector<std::vector<int>> multiply(std::vector<std::vector<int>>& mat1, 
                                       std::vector<std::vector<int>>& mat2) {
    if (mat1.empty() || mat2.empty()) {
        throw std::invalid_argument("Error: matrix1 or matrix2 is empty");
    }
    const int m1 = mat1.size(), n1 = mat1[0].size();
    const int m2 = mat2.size(), n2 = mat2[0].size();

    if (n1 != m2) {
        throw std::invalid_argument("Error: matrix1 col size and matrix2 row size does not match");
    }

    std::vector<std::vector<int>> result(m1, std::vector<int>(n2));
    for (int i = 0; i < m1; i++) {
        for (int j = 0; j < n2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < n1; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return result;
}

void remove_spaces(std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

void test_remove_spces() {
    std::string str = "q w e r t y 1 2 3 4 5 6";
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::cout << str.size() << "\n";
    std::cout << str << "\n";
}

void print_matrix(std::vector<std::vector<int>>& matrix) {
    const int m = matrix.size(), n = matrix[0].size();
    // std::cout << "m = " << m << " n = " << n << "\n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<std::string> read_file(std::string& file_path) {
    std::ifstream ifs(file_path);
    std::vector<std::string> buffer, info, output;
    std::string line;
    int num_mat = 0, n1 = 0, n2 = 0, m1 = 0, m2 = 0;
    int row1 = 0, row2 = 0, col1 = 0, col2 = 0;

    if (!ifs.is_open()) {
        throw std::invalid_argument("Failed to open file.");
    }

    int index = 0;
    while (std::getline(ifs, line)) {
        if (line == "Matrix_Transpose") {
            index++;
            num_mat = 1;
            info.push_back(std::to_string(num_mat));
            continue;
        }
        else if (line == "Matrix_Multiplication") {
            index++;
            num_mat = 2;
            info.push_back(std::to_string(num_mat));
            continue;
        }
        if (line.substr(0, 4) == "Name") {
            index++;
            if (n1 == 0) n1 = index;
            n2 = index;
            continue;
        }
        index++;
        if (line.substr(0, 3) == "End") {
            continue;
        }

        std::vector<int> values;
        std::stringstream stream(line);
        int n;
        while (stream >> n) {
            values.push_back(n);
        }
        if (m1 == 0) m1 = values.size();
        m2 = values.size();
        values.clear();

        std::string temp;
        for (int i = 0; i < line.size() - 1; i++) {
            // if (m1 == 0) m1 = (line.size() - 1) / 2;
            // m2 = (line.size() - 1) / 2;
            
            temp += line[i];
        }
        output.push_back(temp);
    }
    
    // std::cout << "total = " << index << "\n";
    // std::cout << "n1 = " << n1 << "\n";
    // std::cout << "n2 = " << n2 << "\n";
    // std::cout << "m1 = " << m1 << "\n";
    // std::cout << "m2 = " << m2 << "\n";

    row1 = n2 - n1 - 1;
    row2 = index - n2 - 1;
    col1 = m1;
    col2 = m2;
    // std::cout << "(row1, col1) = " << row1 << "," << col1 << "\n";
    // std::cout << "(row2, col2) = " << row2 << "," << col2 << "\n";

    if (num_mat == 1) {
        std::string str = std::to_string(row2) + " " + std::to_string(col2);
        info.push_back(str);
    }
    else if (num_mat == 2) {
        std::string str1 = std::to_string(row1) + " " + std::to_string(col1);
        std::string str2 = std::to_string(row2) + " " + std::to_string(col2);
        info.push_back(str1);
        info.push_back(str2);
    }

    for (int i = 0; i < output.size(); i++) {
        info.push_back(output[i]);
    }

    // for (int i = 0; i < info.size(); i++) {
    //     for (int j = 0; j < info[i].size(); j++) {
    //         std::cout << info[i][j]; 
    //     }
    //     std::cout << "\n";
    // }
    // std::cout << "\n";
    
    
    ifs.close();
    return info;
}

void test_read_file() {
    std::vector<std::string> buffer; 
    for (int file_index = 1; file_index <= 5; file_index++) {
        std::string file_path = "D:/C++/matrix_operation/input0" + std::to_string(file_index) + ".txt";
        buffer = read_file(file_path);
        for (int i = 0; i < buffer.size(); i++) {
            for (int j = 0; j < buffer[i].size(); j++) {
                std::cout << buffer[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

void test(int file_index) {
    std::vector<std::string> buffer; 
    std::vector<std::vector<int>> mat1, mat2, result, output;
    std::vector<int> values;
    
    // int file_index = 1;
    std::string file_path = "D:/C++/matrix_operation/input0" + std::to_string(file_index) + ".txt";
    buffer = read_file(file_path);

    int shift = 0;
    if (buffer[0] == "1") {
        shift = 2;
        std::string temp = buffer[1];
        std::stringstream stream(temp);
        int m, n; 
        while (stream >> m >> n) {
            // std::cout << m << n;
            result.resize(m, std::vector<int>(n, 0));
        }
        // print_matrix(result); // original size

        for (int k = shift; k < buffer.size(); k++) {
            // std::cout << "k = " << k << "\n";
            std::string temp = buffer[k];
            std::stringstream stream(temp);
            int n;
            while (stream >> n) {
                values.push_back(n);
                // std::cout << n;
            }
            result[k - shift] = values;
            values.clear();
        }
        print_matrix(result);
        output = transpose(result);
        print_matrix(output);
    }
    else if (buffer[0] == "2") {
        shift = 3;
        for (int b = 1; b <= 2; b++) {
            std::string temp = buffer[b];
            std::stringstream stream(temp);
            int m, n; 
            while (stream >> m >> n) {
                // std::cout << m << n;
                if (b == 1) mat1.resize(m, std::vector<int>(n, 0));
                if (b == 2) mat2.resize(m, std::vector<int>(n, 0));
            }
        } 
        // original size
        // print_matrix(mat1);
        // print_matrix(mat2);

        for (int k = shift; k < shift + mat1.size(); k++) {
            // std::cout << "k = " << k << "\n";
            std::string temp = buffer[k];
            std::stringstream stream(temp);
            int n;
            while (stream >> n) {
                values.push_back(n);
                // std::cout << n;
            }
            mat1[k - shift] = values;
            values.clear();
        }
        print_matrix(mat1);
        for (int k = shift + mat1.size(); k < buffer.size(); k++) {
            // std::cout << "k = " << k << "\n";
            std::string temp = buffer[k];
            std::stringstream stream(temp);
            int n;
            while (stream >> n) {
                values.push_back(n);
                // std::cout << n;
            }
            mat2[k - shift - mat1.size()] = values;
            values.clear();
        }
        print_matrix(mat2);
        
        output = multiply(mat1, mat2);
        print_matrix(output);
    }
}

int main() {
    std::vector<std::string> buffer; 
    std::vector<std::vector<int>> mat1, mat2, result, output;
    std::vector<int> values;
    
    // test_read_file();

    for (int i = 1; i <= 5; i++) {
        test(i);
    }
    
    int file_index = 7;
    std::string file_path = "D:/C++/matrix_operation/input0" + std::to_string(file_index) + ".txt";
    buffer = read_file(file_path);

    // std::cout << buffer.size();

    int shift = 0;
    if (buffer[0] == "1") {
        shift = 2;
        std::string temp = buffer[1];
        std::stringstream stream(temp);
        int m, n; 
        while (stream >> m >> n) {
            // std::cout << m << n;
            result.resize(m, std::vector<int>(n, 0));
        }
        // print_matrix(result); // original size

        for (int k = shift; k < buffer.size(); k++) {
            // std::cout << "k = " << k << "\n";
            std::string temp = buffer[k];
            std::stringstream stream(temp);
            int n;
            while (stream >> n) {
                values.push_back(n);
                // std::cout << n;
            }
            result[k - shift] = values;
            values.clear();
        }
        print_matrix(result);
        output = transpose(result);
        print_matrix(output);
    }
    else if (buffer[0] == "2") {
        shift = 3;
        for (int b = 1; b <= 2; b++) {
            std::string temp = buffer[b];
            std::stringstream stream(temp);
            int m, n; 
            while (stream >> m >> n) {
                // std::cout << m << n;
                if (b == 1) mat1.resize(m, std::vector<int>(n, 0));
                if (b == 2) mat2.resize(m, std::vector<int>(n, 0));
            }
        } 
        // original size
        // print_matrix(mat1);
        // print_matrix(mat2);

        for (int k = shift; k < shift + mat1.size(); k++) {
            // std::cout << "k = " << k << "\n";
            std::string temp = buffer[k];
            std::stringstream stream(temp);
            int n;
            while (stream >> n) {
                values.push_back(n);
                // std::cout << n;
            }
            mat1[k - shift] = values;
            values.clear();
        }
        print_matrix(mat1);
        for (int k = shift + mat1.size(); k < buffer.size(); k++) {
            // std::cout << "k = " << k << "\n";
            std::string temp = buffer[k];
            std::stringstream stream(temp);
            int n;
            while (stream >> n) {
                values.push_back(n);
                // std::cout << n;
            }
            mat2[k - shift - mat1.size()] = values;
            values.clear();
        }
        print_matrix(mat2);

        output = multiply(mat1, mat2);
        print_matrix(output);
    }
    
    return 0;
}

/*
inside buffer:
1
3 3     
1 2 3   
4 5 6   
7 5 9   
        
1       
2 3     
12 42 8 
35 7 23 
        
1       
5 2     
1 14    
3 8     
5 6     
7 4     
11 2    

2
3 3
3 3
1 2 3
4 5 6
7 5 9
2 2 3
4 5 5
8 8 7

2
4 2
2 4
1 2
2 3
3 4
4 1
2 3 1 4
5 7 2 3

output:
PS D:\C++\matrix_operation> ./practice1.exe
1 2 3 
4 5 6
7 5 9

1 4 7
2 5 5
3 6 9

12 42 8
35 7 23

12 35
42 7
8 23

1 14
3 8
5 6
7 4
11 2

1 3 5 7 11
14 8 6 4 2

1 2 3
4 5 6
7 5 9

2 2 3
4 5 5
8 8 7

34 36 34
76 81 79
106 111 109

1 2
2 3
3 4
4 1

2 3 1 4
5 7 2 3

12 17 5 10
19 27 8 17
26 37 11 24
13 19 6 19

1 2
2 3
3 4
4 1

2 3 1 4
5 7 2 3

12 17 5 10
19 27 8 17 
26 37 11 24
13 19 6 19
*/
