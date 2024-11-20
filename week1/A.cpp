#include <iostream>  // Preprocessor directive for input/output
#include <string>
using namespace std;

int main() {
    int bites;
    std::cin >> bites;


    for (int i = 1; i <= bites; i++) {
        std::string currBite;
        std::cin >> currBite;
        
        if (currBite != "mumble") {
            int numBite = stoi(currBite);
            if (numBite != i) {
                std::cout << "something is fishy" << std::endl;
                return 0;
            } 
        }
    }

    std::cout << "makes sense" << std::endl;
}
