#include <bits/stdc++.h>
// using namespace std;

// write results to a file
void sayHello(std::ofstream &ofs) { 
    ofs << "Hello world" << "\n"; 
}  


int main() {

    std::ofstream fs("somefile.txt"); 
    sayHello(fs); // this works! 

    return 0;
}
