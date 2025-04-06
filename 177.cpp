#include <iostream>
/* Проблема "Алмаз смерті"

Якщо клас наслідує декілька класів, які в свою чергу наслідують один спільний базовий клас,
то при створенні об'єкта наслідного класу цей базовий клас буде створений декілька разів. 
Це може призвести до непередбачуваних наслідків, як у наступному прикладі: */
class PoweredDevice 
{
public:
    PoweredDevice(int power) 
    {
        std::cout << "PoweredDevice: " << power << '\n';
    }
};

class Scanner : public PoweredDevice 
{
public:
    Scanner(int scanner, int power) : PoweredDevice(power) 
    {
        std::cout << "Scanner: " << scanner << '\n';
    }
};

class Printer : public PoweredDevice 
{
public:
    Printer(int printer, int power) : PoweredDevice(power) {
        std::cout << "Printer: " << printer << '\n' << std::endl;
    }
};

class Copier : public Scanner, public Printer 
{
public:
    Copier(int scanner, int printer, int power)
        : Scanner(scanner, power), Printer(printer, power) {}
};
/* Як видно з результату, базовий клас PoweredDevice створюється двічі, кожен раз через Scanner та Printer. */

/* Віртуальні базові класи

Щоб уникнути цієї проблеми, можна використовувати віртуальні базові класи. 
Віртуальні базові класи дозволяють створити тільки одну копію базового класу, 
незалежно від того, скільки класів його наслідують.

Ось як виглядатиме код із віртуальними базовими класами: */
class PoweredDevice1
{
public:
    PoweredDevice1(int power1) 
    {
        std::cout << "PoweredDevice1: " << power1 << '\n';
    }
};

class Scanner1 : virtual public PoweredDevice1 
{
public:
    Scanner1(int scanner1, int power1) : PoweredDevice1(power1) 
    {
        std::cout << "Scanner1: " << scanner1 << '\n';
    }
};

class Printer1 : virtual public PoweredDevice1
{
public:
    Printer1(int printer1, int power1) : PoweredDevice1(power1) 
    {
        std::cout << "Printer1: " << printer1 << '\n';
    }
};

class Copier1 : public Scanner1, public Printer1
{
public:
    Copier1(int scanner1, int printer1, int power1)
        : Scanner1(scanner1, power1), Printer1(printer1, power1), PoweredDevice1(power1) {}
};
/* Тепер, замість двох копій базового класу, створюється лише одна. Вся відповідальність за створення базового класу лягає на найнижчий (найдочірніший) клас у ієрархії, тобто на Copier. */


int main() 
{
    Copier copier(1, 2, 3);
    Copier1 copier1(1, 2, 3);

}

/* Пояснення

Віртуальні базові класи: Ключове слово virtual у оголошеннях класів Scanner та Printer вказує на те, що клас PoweredDevice є віртуальним базовим класом. Це означає, що створюється тільки одна копія об'єкта PoweredDevice, і ця копія буде спільною для всіх класів, що наслідують PoweredDevice.
Хто відповідає за створення об'єкта базового класу?: Клас Copier, будучи найнижчим класом у ієрархії спадкування, відповідає за створення об'єкта PoweredDevice. Конструктори класів Scanner та Printer більше не викликають конструктор PoweredDevice.
Ієрархія спадкування та порядок ініціалізації: Віртуальні базові класи ініціалізуються перед іншими (невіртуальними) базовими класами. Це забезпечує правильну побудову об'єкта. */