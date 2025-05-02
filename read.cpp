// UserReader.cpp
#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    const std::string filepath = "/Users/user/chat/messages.txt";
    std::ifstream in(filepath);

    if (!in) 
    {
        std::cerr << "Не вдалося відкрити файл для читання!" << std::endl;
        return 1;
    }

    std::string line;
    std::cout << "Вміст чату:\n";
    while (std::getline(in, line)) 
    {
        std::cout << line << std::endl;
    }

    in.close();
    return 0;
}

