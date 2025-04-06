/* Обрізка об’єктів в мові С++ — це процес, коли об’єкт дочірнього класу присвоюється 
об’єкту батьківського класу, і в результаті зберігається тільки частина об’єкта, 
що належить батьківському класу. Частина, що належить дочірньому класу, «обрізається», 
і доступ до неї неможливий. */
#include <iostream>
#include <vector>
#include <functional> // для std::reference_wrapper

class Parent
{
protected:
    int m_value;

public:
    Parent(int value)
        : m_value(value)
    {
    }

    virtual const char* getName() const { return "Parent"; }
    int getValue() const { return m_value; }
};

class Child : public Parent
{
public:
    Child(int value)
        : Parent(value)
    {
    }

    virtual const char* getName() const { return "Child"; }
};

void printName(const Parent &parent) // передача по посиланню
{
    std::cout << "I am a " << parent.getName() << '\n';
}

int main()
{
    // Обрізка об'єктів
    Child child(7);
    std::cout << "child is a " << child.getName() << " and has value " << child.getValue() << '\n';

    Parent &ref = child;
    std::cout << "ref is a " << ref.getName() << " and has value " << ref.getValue() << '\n';

    Parent *ptr = &child;
    std::cout << "ptr is a " << ptr->getName() << " and has value " << ptr->getValue() << '\n';

    // Обрізка при присвоєнні
    Parent parent = child; // обрізка
    std::cout << "parent is a " << parent.getName() << " and has value " << parent.getValue() << '\n';

    // Обрізка об'єктів у функціях
    printName(child); // передача по значенню (обрізка об'єкта)

    // Обрізка векторів
    std::vector<Parent*> v;
    v.push_back(new Parent(7)); // додаємо об'єкт класу Parent в наш вектор
    v.push_back(new Child(8));  // додаємо об'єкт класу Child в наш вектор

    // Виведення елементів вектора
    for (int count = 0; count < v.size(); ++count)
        std::cout << "I am a " << v[count]->getName() << " with value " << v[count]->getValue() << "\n";

    // Очистка пам'яті
    for (int count = 0; count < v.size(); ++count)
        delete v[count];

    // Використання std::reference_wrapper для поліморфізму
    std::vector<std::reference_wrapper<Parent> > v_ref;
    Parent p(7);
    Child ch(8);
    v_ref.push_back(p); // додаємо об'єкт класу Parent в наш вектор
    v_ref.push_back(ch); // додаємо об'єкт класу Child в наш вектор

    // Виведення елементів вектора
    for (int count = 0; count < v_ref.size(); ++count)
        std::cout << "I am a " << v_ref[count].get().getName() << " with value " << v_ref[count].get().getValue() << "\n";

    return 0;
}
