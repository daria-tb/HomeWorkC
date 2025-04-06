/* Модифікатор override
Використовується, щоб гарантувати, що метод дійсно перевизначає віртуальну функцію батьківського класу.
Якщо сигнатура не співпадає — компілятор видає помилку.
Допомагає уникнути невидимих багів у спадкуванні. 

class A {
public:
    virtual const char* getName1(int x) { return "A"; }
    virtual const char* getName2(int x) { return "A"; }
};

class B : public A {
public:
    virtual const char* getName1(short int x) override { return "B"; }  // інший тип параметра -
    virtual const char* getName2(int x) const override { return "B"; }  // додано const -
    virtual const char* getName3(int x) override { return "B"; }        // перевизначення +
};

Модифікатор final
Забороняє дальше перевизначення віртуального методу або наслідування від класу.
Вказується після оголошення методу чи класу.

class A {
public:
    virtual const char* getName() { return "A"; }
};

class B : public A {
public:
    virtual const char* getName() override final { return "B"; } // далі перевизначати не можна
};

class C : public B {
public:
    virtual const char* getName() override { return "C"; } // помилка: B::getName() final
};

class B final : public A { // клас B не можна наслідувати
public:
    virtual const char* getName() override { return "B"; }
};

class C : public B { // помилка
public:
    virtual const char* getName() override { return "C"; }
};
*/

/* Коваріантний тип повернення
У перевизначенні дозволено повертати дочірній тип замість батьківського.
Працює лише з вказівниками або посиланнями. */
#include <iostream>

class Parent 
{
public:
    virtual Parent* getThis() { std::cout << "called Parent::getThis()\n"; return this; }
    void printType() { std::cout << "returned a Parent\n"; }
};

class Child : public Parent 
{
public:
    virtual Child* getThis() override { std::cout << "called Child::getThis()\n"; return this; }
    void printType() { std::cout << "returned a Child\n"; }
};

int main() 
{
    Child ch;
    Parent* p = &ch;
    ch.getThis()->printType();  // Child* → Child::printType()
    p->getThis()->printType();  // Child* → але через Parent*, тому Parent::printType()
}
