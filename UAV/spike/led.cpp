#include <iostream>

class Test
{
    int m_a;
    public:
    Test(int a) : m_a(a) {};
    int Return() {return m_a;}
};

int main() {

    Test thing(1);
    std::cout << thing.Return() << std::endl;

    bool forwards = true;
    int bits = 5;

    for (int integer = 0; integer < 31; integer++) {
        for (int b = 0; b < bits; b++) {
            std::cout << ((integer >> b) & 1) << ' ';
        }
        std::cout << std::endl;
    }
}