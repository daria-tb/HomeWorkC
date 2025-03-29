#include <iostream>

class Base 
{
public:
    virtual void show() 
    {
        std::cout << "Base show\n";
    }

    virtual ~Base() //якщо забрати virtual, деструктор Derived не викличеться
    /* коли деструктор Base не віртуальний, 
    при видаленні через Base* (delete ptr;) викликається лише Base::~Base(), 
    а Derived::~Derived() не викликається
    це призводить до витоків пам’яті. */
    {
        std::cout << "Base destructor\n";
    }
};

class Derived : public Base 
{
public:
    void show() override 
    {
        std::cout << "Derived show\n";
    }

    ~Derived() 
    {
        std::cout << "Derived destructor\n";
    }
};

int main() 
{
    Derived d;
    Base* p = &d;
    p->show();

    return 0;
}
