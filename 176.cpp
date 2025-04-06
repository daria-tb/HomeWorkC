#include <iostream>
#include <string>
/* Приклад чистої віртуальної функції

У наведеному прикладі клас Animal містить чисту віртуальну функцію speak(), 
яку мають перевизначити всі дочірні класи, щоб об'єкти цих класів могли бути створені. */
class Animal
{
protected:
    std::string m_name;
public:
    Animal(std::string name) : m_name(name) {}
    std::string getName() { return m_name; }
    virtual const char* speak() = 0; // Чиста віртуальна функція
};

class Cat : public Animal
{
public:
    Cat(std::string name) : Animal(name) {}
    virtual const char* speak() { return "Meow"; }
};

class Dog : public Animal
{
public:
    Dog(std::string name) : Animal(name) {}
    virtual const char* speak() { return "Woof"; }
};

class Lion : public Animal
{
public:
    Lion(std::string name) : Animal(name) {}
    virtual const char* speak() { return "Roar"; } // Перевизначення функції speak()
};
//--------
/* Чисті віртуальні функції з визначеннями

Можна також надавати реалізацію чистих віртуальних функцій у батьківському класі. 
Це дозволяє дочірнім класам використовувати реалізацію за замовчуванням, 
якщо вони не хочуть її змінювати. */
class Animal1
{
protected:
    std::string m_name;
public:
    Animal1(std::string name) : m_name(name) {}
    std::string getName() { return m_name; }
    virtual const char* speak() = 0; // Чиста віртуальна функція
};

const char* Animal1::speak()
{
    return "buzz"; // Реалізація за замовчуванням
};

class Dragonfly : public Animal1
{
public:
    Dragonfly(std::string name) : Animal1(name) {}
    virtual const char* speak() { return Animal1::speak(); } // Використовуємо реалізацію з батьківського класу
};


/* //Інтерфейс у C++ — це клас, що не має змінних-членів і містить лише чисті віртуальні функції.
// Інтерфейси використовуються для створення загальних контрактів, 
//що повинні бути реалізовані в класах-нащадках.
class IErrorLog
{
public:
    virtual bool openLog(const char* filename) = 0;
    virtual bool closeLog() = 0;
    virtual bool writeError(const char* errorMessage) = 0;
    virtual ~IErrorLog() {}; // Віртуальний деструктор

};

class FileErrorLog : public IErrorLog
{
public:
    bool openLog(const char* filename) override { // Реалізація відкриття файлу }
    bool closeLog() override { // Реалізація закриття файлу }
    bool writeError(const char* errorMessage) override { //Реалізація запису помилки в файл}
}; */


int main()
{
    Lion lion("John");
    std::cout << lion.getName() << " says " << lion.speak() << '\n'; // Помилка компіляції
//----------
    Dragonfly dfly("Barbara");
    std::cout << dfly.getName() << " says " << dfly.speak() << '\n'; // "Barbara says buzz"
}
