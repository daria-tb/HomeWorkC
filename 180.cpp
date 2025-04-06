#include <iostream>
/* Проблема з перевантаженням operator<<
Виведення об’єктів класів через std::cout може бути проблематичним, коли клас має спадкоємців. Наприклад, якщо ми використовуємо віртуальні функції в класі-батьку, виведення через оператор не викликає коректний метод для дочірніх класів.
Перевантаження operator<<
Перевантаження оператора << дозволяє вивести об’єкти класів без використання розривів:

friend std::ostream& operator<<(std::ostream &out, const Parent &p) 
{
    out << "Parent";
    return out;
}
Чи можна зробити operator<< віртуальним?
Ні, оператора << не можна зробити віртуальним, оскільки це дружня функція, а не метод класу. Тільки методи можуть бути віртуальними.

 */
class Parent 
{
public:
    Parent() {}

    friend std::ostream& operator<<(std::ostream &out, const Parent &p) 
    {
        return p.print(out); // Делегуємо виведення методу print()
    }

    virtual std::ostream& print(std::ostream& out) const 
    {
        out << "Parent";
        return out;
    }
};

class Child : public Parent 
{
public:
    Child() {}

    virtual std::ostream& print(std::ostream& out) const override 
    {
        out << "Child";
        return out;
    }
};

int main() 
{
    Parent p;
    std::cout << p << '\n'; // Виведе "Parent"

    Child ch;
    std::cout << ch << '\n'; // Виведе "Child"

    Parent &pref = ch;
    std::cout << pref << '\n'; // Виведе "Child"
    
    return 0;
}
/* Пояснення:
Для об’єкта класу Parent викликається Parent::print().
Для об’єкта класу Child компілятор викликає operator<<, який делегує виклик віртуальної функції print(). Це дозволяє вивести "Child", навіть якщо оператор перевантажено тільки для базового класу.
Для посилання Parent &pref на об’єкт класу Child також викликається Child::print() завдяки віртуальності методу print(). */