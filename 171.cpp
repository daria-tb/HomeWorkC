#include <iostream>
#include <string>
using namespace std;
//Поліморфізм — це властивість, яка дозволяє викликати правильну функцію (залежно від фактичного типу об'єкта), навіть якщо ми звертаємося до нього через вказівник або посилання на базовий клас.
//Щоб це працювало, базова функція має бути позначена ключовим словом virtual. Тоді при виклику цієї функції через базовий тип, виконається її перевизначення в дочірньому класі (якщо таке є).
// Базовий клас

class Animal 
{
protected:
    string m_name;

    // Конструктор protected, щоб не створювати Animal напряму
    Animal(string name) : m_name(name) {}

public:
    string getName() { return m_name; }

    // Віртуальна функція
    virtual const char* speak() { return "???"; }
};

// Клас Cat перевизначає speak()
class Cat : public Animal 
{
public:
    Cat(string name) : Animal(name) {}

    virtual const char* speak() { return "Meow"; }
};

// Клас Dog перевизначає speak()
class Dog : public Animal 
{
public:
    Dog(string name) : Animal(name) {}

    virtual const char* speak() { return "Woof"; }
};

// Функція, яка демонструє поліморфізм
void report(Animal &animal) 
{
    cout << animal.getName() << " says " << animal.speak() << '\n';
}

int main() 
{
    Cat cat("Matros");
    Dog dog("Barsik");

    // Тест через посилання
    report(cat);   // Matros says Meow
    report(dog);   // Barsik says Woof

    // Масив вказівників на базовий клас
    Cat ivan("Ivan"), martun("Martun");
    Dog tolik("Tolik"), tyzik("Tyzik");

    Animal* animals[] = { &cat, &dog, &ivan, &tolik, &martun, &tyzik };

    for (int i = 0; i < 6; ++i) {
        cout << animals[i]->getName() << " says " << animals[i]->speak() << '\n';
    }

    return 0;
}

/* Використовуйте virtual, якщо хочете досягти динамічного зв’язування (тобто щоб метод працював згідно з реальним типом об’єкта).
Без virtual буде завжди викликатися метод з батьківського класу.
У поліморфізмі ключову роль грає тип об’єкта, а не тип вказівника чи посилання. */