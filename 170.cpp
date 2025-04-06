#include <iostream>
#include <string>
/* example1 — показує, як вказівники і посилання на Child працюють коректно і бачать Child::getName().
example2 — демонструє, що якщо використовувати Parent* або Parent&, то ми втрачаємо доступ до Child::getName().
example3 — показує ту ж ситуацію з класами Animal, Cat, Dog.
example4 — приклад, як масив Animal може допомогти опрацювати різні типи тварин однією функцією report(). */
// Клас Parent
class Parent 
{
protected:
    int m_value;
public:
    Parent(int value) : m_value(value) {}
    const char* getName() { return "Parent"; }
    int getValue() { return m_value; }
};

// Клас Child, що наслідує Parent
class Child : public Parent 
{
public:
    Child(int value) : Parent(value) {}
    const char* getName() { return "Child"; }
    int getValueDoubled() { return m_value * 2; }
};

// Демонстрація вказівників і посилань на Child
void example1() 
{
    Child child(7);
    std::cout << "child is a " << child.getName() << " and has value " << child.getValue() << '\n';

    Child& rChild = child;
    std::cout << "rChild is a " << rChild.getName() << " and has value " << rChild.getValue() << '\n';

    Child* pChild = &child;
    std::cout << "pChild is a " << pChild->getName() << " and has value " << pChild->getValue() << '\n';
}

// Використання вказівників/посилань типу батьківського класу
void example2() 
{
    Child child(7);
    Parent& rParent = child;
    Parent* pParent = &child;

    std::cout << "child is a " << child.getName() << " and has value " << child.getValue() << '\n';
    std::cout << "rParent is a " << rParent.getName() << " and has value " << rParent.getValue() << '\n';
    std::cout << "pParent is a " << pParent->getName() << " and has value " << pParent->getValue() << '\n';
}

// Клас Animal і спадкоємці
class Animal 
{
protected:
    std::string m_name;
    Animal(std::string name) : m_name(name) {}
public:
    std::string getName() { return m_name; }
    const char* speak() { return "???"; }
};

class Cat : public Animal 
{
public:
    Cat(std::string name) : Animal(name) {}
    const char* speak() { return "Meow"; }
};

class Dog : public Animal 
{
public:
    Dog(std::string name) : Animal(name) {}
    const char* speak() { return "Woof"; }
};

// Демонстрація проблеми видимості
void example3() 
{
    Cat cat("Matros");
    std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';

    Dog dog("Barsik");
    std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';

    Animal* pAnimal = &cat;
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    pAnimal = &dog;
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';
}

// Функція, яка приймає посилання на батьківський клас
void report(Animal& rAnimal) 
{
    std::cout << rAnimal.getName() << " says " << rAnimal.speak() << '\n';
}

// Приклад масиву тварин
void example4() 
{
    Cat cats[] = { Cat("Matros"), Cat("Ivan"), Cat("Martun") };
    Dog dogs[] = { Dog("Barsik"), Dog("Tolik"), Dog("Tyzik") };

    for (const Cat& cat : cats)
        report(const_cast<Cat&>(cat));
    for (const Dog& dog : dogs)
        report(const_cast<Dog&>(dog));
}

int main() 
{
    std::cout << "=== Example 1 ===\n";
    example1();

    std::cout << "\n=== Example 2 ===\n";
    example2();

    std::cout << "\n=== Example 3 ===\n";
    example3();

    std::cout << "\n=== Example 4 ===\n";
    example4();

    return 0;
}
