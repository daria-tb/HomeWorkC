#include <iostream>
#include <string>
/* Застосовуючи поліморфізм на практиці ви часто стикатиметеся з ситуаціями, 
коли у вас є вказівник на батьківський клас, але вам потрібно отримати доступ до даних, 
які є тільки в дочірньому класі.
Мова C++ дозволяє нам неявно конвертувати вказівник класу Child у вказівник класу Parent 
(фактично, це і робить getObject()). Ця конвертація називається приведенням до базового типу 
(або «підвищуючим приведенням типу»). Однак, що, якби ми могли конвертувати вказівник класу Parent назад 
у вказівник класу Child? Таким чином, ми могли б напряму викликати Child::getName(), 
використовуючи той же вказівник, і взагалі не морочитися з віртуальними функціями.
У мові C++ оператор dynamic_cast використовується саме для цього. Хоча динамічне приведення дозволяє 
виконувати не тільки конвертацію вказівників батьківського класу у вказівники дочірнього класу, 
це є найбільш поширеним застосуванням оператора dynamic_cast. Цей процес називається приведенням до 
дочірнього типу (або «понижуючим приведенням типу»).

Використання dynamic_cast майже ідентичне використанню static_cast. */
// Клас батьків
class Parent
{
protected:
    int m_value;

public:
    Parent(int value) : m_value(value) {}

    virtual ~Parent() {}
};

// Клас нащадка
class Child : public Parent
{
protected:
    std::string m_name;

public:
    Child(int value, std::string name) : Parent(value), m_name(name) {}

    const std::string& getName() { return m_name; }
};

// Функція для отримання об'єкта
Parent* getObject(bool bReturnChild)
{
    if (bReturnChild)
        return new Child(1, "Banana");
    else
        return new Parent(2);
}

int main()
{
    Parent *p = getObject(true);

    // Використовуємо dynamic_cast для приведення вказівника Parent до вказівника Child
    Child *ch = dynamic_cast<Child*>(p);

    if (ch) // Перевірка на нульовий вказівник
        std::cout << "The name of the Child is: " << ch->getName() << '\n';
    else
        std::cout << "Conversion failed\n";

    delete p;

    return 0;
}
/* Пояснення:
Клас Parent — базовий клас з полем m_value.
Клас Child — клас нащадок, що розширює Parent, додаючи поле m_name та метод getName().
getObject() — функція, що повертає вказівник на об'єкт класу Parent або Child, залежно від параметра.
У main() ми використовуємо оператор dynamic_cast, щоб виконати динамічне приведення вказівника з класу Parent до класу Child. 
Перевірка на нульовий вказівник гарантує безпечність операції. */