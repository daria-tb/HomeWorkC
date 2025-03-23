#include <iostream>
//шаблон класу Repository8
template <class T> class Repository8
{
private:
    T m_array[8];

public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }

    const T& get(int index)
    {
        return m_array[index];
    }
};
//спеціалізація шаблону для Repository8<bool>
template <>
class Repository8<bool>
{
private:
    unsigned char m_array; //1 байт для зберігання 8 біт. значень

public:
    Repository8() : m_array(0) {}

    void set(int index, bool value)
    {
        if (value)
            m_array |= (1 << index); //ставилр біт у 1
        else
            m_array &= ~(1 << index); //скидаємо біт у 0
    }

    bool get(int index) const
    {
        return (m_array >> index) & 1; //отримуємо значення конкретного біта
    }
};

int main() 
{
    //запускаємо int
    Repository8<int> intRepository;
    for (int count = 0; count < 8; ++count)
        intRepository.set(count, count);

    std::cout << "Int Repository:\n";
    for (int count = 0; count < 8; ++count)
        std::cout << intRepository.get(count) << " ";
    std::cout << "\n\n";

    //запускаємо bool
    Repository8<bool> boolRepository;
    for (int count = 0; count < 8; ++count)
        boolRepository.set(count, count % 5);

    std::cout << "Bool Repository:\n";
    for (int count = 0; count < 8; ++count)
        std::cout << (boolRepository.get(count) ? "true" : "false") << " ";
    std::cout << "\n\n";

    std::cout << "Size of bool: " << sizeof(bool) << " bytes\n";

    return 0;
}
