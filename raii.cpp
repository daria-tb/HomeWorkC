#include <iostream>
#include <memory>
#include <fstream>
#include <stdexcept>

// Простой класс с управлением памятью через RAII
class SmartPointer {
public:
    SmartPointer() {
        data = new int[100]; // Выделение памяти
    }
    ~SmartPointer() {
        delete[] data; // Освобождение памяти
    }
private:
    int* data;
};

// Использование std::unique_ptr
void uniquePtrExample() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    std::cout << *ptr << std::endl;
} // Память освобождается автоматически

// Использование std::shared_ptr
void sharedPtrExample() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::shared_ptr<int> ptr2 = ptr1;
    std::cout << *ptr1 << " " << *ptr2 << std::endl;
} // Память освобождается при уничтожении последнего shared_ptr

// RAII-класс для управления файлом
class FileRAII {
public:
    FileRAII(const std::string& filename) : file_(filename) {
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
    }
    ~FileRAII() {
        if (file_.is_open()) {
            file_.close();
        }
    }
    void Write(const std::string& data) {
        file_ << data;
    }
private:
    std::ofstream file_;
};

// RAII-класс для управления файлами с обработкой исключений
class FileHandler {
public:
    FileHandler(const std::string& filename) {
        file_.open(filename);
        if (!file_.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
    }
    ~FileHandler() {
        file_.close();
    }
private:
    std::fstream file_;
};

// Пример использования FileRAII с обработкой исключений
void fileExample() {
    try {
        FileRAII file("example.txt");
        file.Write("Hello, RAII!");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    SmartPointer sp;
    uniquePtrExample();
    sharedPtrExample();
    fileExample();
    
    return 0;
}
