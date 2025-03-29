#include <iostream>

class Class 
{
public:
    Class() = default;

    //забороняємо копіювання
    Class(const Class&) = delete;
    Class& operator=(const Class&) = delete;

    //забороняємо переміщення
    Class(Class&&) = delete;
    Class& operator=(Class&&) = delete;
};

int main() 
{
    Class a;
    //копіювання
    // Class b = a;  //копіювання заборонено

    //присвоєння копіювання
    // Class c;
    // c = a;  //присвоєння копіювання заборонено

    //переміщення
    // Class d = std::move(a);  //переміщення заборонено

    //присвоєння переміщення
    // Class e;
    // e = std::move(a);  //присвоєння переміщення заборонено

    std::cout << "Testing is completed without compilation errors.\n";

    return 0;
}
