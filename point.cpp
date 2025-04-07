#include <iostream>
#include <cmath>
#include <ostream>

//клас Point (точка на площині)
class Point 
{
private:
    double x; //коорд. x 
    double y; //коорд. y 

public:
    //конструктор за замовчуванням
    Point() : x(0.0), y(0.0) {}

    //конструктор з параметрами для ініціалізації координат
    Point(double _x, double _y) : x(_x), y(_y) {}

    //метод для отримання значення x
    double getX() const 
    {
        return x;
    }

    //метод для отримання значення y
    double getY() const 
    {
        return y;
    }

    //метод для встановлення значення x
    void setX(double _x) 
    {
        x = _x;
    }

    //метод для встановлення значення y
    void setY(double _y) 
    {
        y = _y;
    }

    //перевантаження оператора виведення для об'єктів класу Point
    friend std::ostream& operator<<(std::ostream& os, const Point& point) 
    {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

//абстрактний клас Shape (геометрична фігура)
class Shape 
{
public:
    //чиста віртуальна ф-я для виведення інформації про фігуру
    virtual void print(std::ostream& os) const = 0;

    //перевантаження оператора виведення для об'єктів класу Shape
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) 
    {
        shape.print(os); // Викликаємо віртуальну ф-ю print()
        return os;
    }

    //пустий віртуальний деструктор
    virtual ~Shape() {}

    //чиста віртуальна ф-я для обчислення площі фігури
    virtual double Area() const = 0;
};

// Клас Triangle (трикутник), що наслідує клас Shape
class Triangle : public Shape 
{
private:
    Point p1; // Перша вершина трикутника
    Point p2; // Друга вершина трикутника
    Point p3; // Третя вершина трикутника

public:
    //конструктор для ініціалізації трикутника 3ма точками
    Triangle(const Point& _p1, const Point& _p2, const Point& _p3) : p1(_p1), p2(_p2), p3(_p3) {}

    //реалізація чистої віртуальної функції print() для трикутника
    void print(std::ostream& os) const override 
    {
        os << "Трикутник: " << p1 << ", " << p2 << ", " << p3;
    }

    //реалізація чистої віртуальної ф-ї Area() для трикутника
    double Area() const override 
    {
        //формула Герона для обчислення площі трикутника за координатами вершин
        double a = std::sqrt(std::pow(p2.getX() - p1.getX(), 2) + std::pow(p2.getY() - p1.getY(), 2));
        double b = std::sqrt(std::pow(p3.getX() - p2.getX(), 2) + std::pow(p3.getY() - p2.getY(), 2));
        double c = std::sqrt(std::pow(p1.getX() - p3.getX(), 2) + std::pow(p1.getY() - p3.getY(), 2));
        double s = (a + b + c) / 2.0; //півпериметр
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

//клас Circle (коло), що наслідує клас Shape
class Circle : public Shape 
{
private:
    Point center;
    int radius;

public:
    //конструктор для ініціалізації кола центром та радіусом
    Circle(const Point& _center, int _radius) : center(_center), radius(_radius) {}

    //реалізація чистої віртуальної функції print() для кола
    void print(std::ostream& os) const override 
    {
        os << "Коло: центр " << center << ", радіус " << radius;
    }

    //реалізація чистої віртуальної ф-ї Area() для кола
    double Area() const override 
    {
        return M_PI * radius * radius; //площа кола: π * r^2
    }
};

int main() 
{
    //створення об'єктів класу Point
    Point p_a(1.0, 2.0);
    Point p_b(4.0, 6.0);
    Point p_c(7.0, 1.0);
    Point center(3.0, 5.0);

    //створення об'єктів класів Triangle та Circle
    Triangle triangle(p_a, p_b, p_c);
    Circle circle(center, 5);

    //використання перевантаженого оператора << для виведення інформації
    std::cout << "Інформація про фігури:" << std::endl;
    std::cout << triangle << std::endl;
    std::cout << circle << std::endl;

    //виведення площі фігур
    std::cout << "\nПлощі фігур:" << std::endl;
    std::cout << "Площа трикутника: " << triangle.Area() << std::endl;
    std::cout << "Площа кола: " << circle.Area() << std::endl;

    return 0;
}

/*у головній ф-ї створюються об'єкти для точок і фігур.
виводиться інформ про фігури та їх площі.
Оператор << автоматично викликає метод print(). */