// UserWriter.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

int main() 
{
    const std::string username = "[A]: ";
    const std::string filepath = "/Users/user/chat/messages.txt";

    while (true) 
    {
        std::ofstream out(filepath, std::ios::app); // дописування
        if (!out) {
            std::cerr << "Не вдалося відкрити файл для запису!" << std::endl;
            return 1;
        }

        std::string message;
        std::cout << "Введіть повідомлення: ";
        std::getline(std::cin, message);

        out << username << message << std::endl;
        out.close();
    }

    return 0;
}
