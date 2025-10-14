#pragma once
#include <iostream>

using namespace std;

// Функции для ввода данных
template <typename N>
N GetNumber(const N left_border = 0, const N right_border = std::numeric_limits<N>::max())
{
    N x;
    while (((std::cin >> x).fail()) || (std::cin.peek() != '\n') || (x < left_border) || (x > right_border))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Неправильный ввод! Пожалуйста измените число: " << std::endl;
    }
    std::cerr << x << std::endl;
    return x;
};

std::string GetName()
{
    string name;
    while (true)
    {
        cin.ignore(1000, '\n');
        getline(cin, name);
        if (!name.empty())
        {
            return name;
        }
        else
        {
            cout << "Неправильный ввод! Введите пожалуйста правильное имя: " << endl;
        }
    }
    return std::string();
}

//// Функции для работы с файлами
//void saveToFile(const vector<Pipe>& pipes, const vector<KS>& kss);
//void loadFromFile(vector<Pipe>& pipes, vector<KS>& kss);
//
//// Функции для работы с объектами
//void deleteObject(vector<Pipe>& pipes, vector<KS>& kss);
//
//// Логирование
//void logAction(const string& action);