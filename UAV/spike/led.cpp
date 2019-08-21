#include <iostream>

int main() {

    bool forwards = true;
    int bits = 5;

    for (int integer = 0; integer < 31; integer++) {
        for (int b = 0; b < bits; b++) {
            std::cout << ((integer >> b) & 1) << ' ';
        }
        std::cout << std::endl;
    }
}