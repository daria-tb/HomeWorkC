/* Віртуальні деструктори

Коли працюєш із наслідуванням, деструктори мають бути віртуальними.
Якщо деструктор не віртуальний, то при видаленні об’єкта через вказівник на батьківський клас буде викликаний лише деструктор батька. 

*/
#include <iostream>

class Parent 
{
public:
    // Деструктор не віртуальний
    ~Parent() 
    {
        std::cout << "Calling ~Parent()" << std::endl;
    }

    virtual const char* getName() 
    { 
        return "Parent"; 
    }
};

class Child : public Parent 
{
private:
    int* m_array;

public:
    // Конструктор за замовчуванням
    Child() : m_array(nullptr) 
    {
        std::cout << "Default constructor of Child" << std::endl;
    }
    // Конструктор для ініціалізації динамічного масиву
    Child(int length) 
    {
        m_array = new int[length];
    }

    // Деструктор віртуальний
    virtual ~Child() 
    {
        std::cout << "Calling ~Child()" << std::endl;
        delete[] m_array;  // Очищаємо пам'ять
    }

    // Перевизначення методу getName
    virtual const char* getName() 
    { 
        return "Child"; 
    }
};

int main() 
{
    // Частина 1: Деструктор без віртуальності
    std::cout << "Без віртуального деструктора:" << std::endl;
    Child* child = new Child(7);
    Parent* parent = child;
    delete parent;  // Викликається тільки ~Parent(), але не ~Child()
    std::cout << std::endl;

    // Частина 2: Віртуальний деструктор
    std::cout << "З віртуальним деструктором:" << std::endl;
    child = new Child(7);
    parent = child;
    delete parent;  // Викликаються обидва деструктори: ~Child() і ~Parent()
    std::cout << std::endl;

    // Частина 3: Ігнорування віртуальних функцій
    std::cout << "Ігнорування віртуальних функцій:" << std::endl;
    Child child2;
    Parent& parentRef = child2;

    // Викликається метод базового класу
    std::cout << parentRef.Parent::getName() << std::endl;

    return 0;
}
/* Пояснення:
Частина 1: Без віртуального деструктора. В результаті видаляється тільки деструктор базового класу (~Parent()), тому пам'ять для m_array не очищається.
Частина 2: З віртуальним деструктором. Тепер, при видаленні об'єкта через вказівник на базовий клас, викликаються деструктори обох класів: спочатку ~Child(), а потім ~Parent().
Частина 3: Ігнорування віртуальних функцій за допомогою Parent::. Це дозволяє явно викликати функцію з базового класу, навіть якщо вона була перевизначена в похідному. */