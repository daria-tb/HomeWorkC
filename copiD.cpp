#include <iostream>

class MyClass 
{
public:
    MyClass() = default;

    //забороняємо копіювання
    MyClass(const MyClass&) = delete;
    MyClass& operator=(const MyClass&) = delete;

    //забороняємо переміщення
    MyClass(MyClass&&) = delete;
    MyClass& operator=(MyClass&&) = delete;
};

int main() 
{
    MyClass a; // Створюємо об'єкт a

    //копіювання
    // MyClass b = a;  //копіювання заборонено

    //присвоєння копіювання
    // MyClass c;
    // c = a;  //присвоєння копіювання заборонено

    //переміщення
    // MyClass d = std::move(a);  //переміщення заборонено

    //присвоєння переміщення
    // MyClass e;
    // e = std::move(a);  //присвоєння переміщення заборонено

    std::cout << "Testing is completed without compilation errors.\n";

    return 0;
}
