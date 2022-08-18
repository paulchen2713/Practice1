#include <bits/stdc++.h>
// using namespace std;

// write results to a file
void sayHello(std::ofstream &ofs) { 
    for (int i = 0; i < 3; i++) 
        ofs << i << " Hello world" << "\n";
}  

void store_cout_results(std::ofstream &fs) {

    auto cout_buff = std::cout.rdbuf(); 
    std::cout.rdbuf(fs.rdbuf());

    for (int i = 3; i > 0; i--)
        std::cout << i << " Hello world!\n"; 
 
    std::cout.rdbuf(cout_buff);
    
}

int main() {

    std::ofstream ofs("testing_write_file1.txt"); 
    sayHello(ofs);
    ofs.close();

    std::ofstream fs;
    fs.open("testing_write_file2.txt");

    store_cout_results(fs);
    fs.close();

    return 0;
}
