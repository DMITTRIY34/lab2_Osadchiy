#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "Ks.h"
#include "Utils.h"
#include <unordered_map>

using namespace std;

void menu(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss) {
    int number;
    while (true)
    {
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотр всех труб" << endl;
        cout << "4. Просмотр всех КС" << endl;
        cout << "5. Поиск труб" << endl;
        cout << "6. Поиск КС" << endl;
        cout << "7. Пакетное редактирование труб" << endl;
        cout << "8. Редактировать КС" << endl;
        cout << "9. Удалить объект" << endl;
        cout << "10. Сохранить в файл" << endl;
        cout << "11. Загрузить из файла" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";

        number = GetNumber(0,11);
        cout << endl;
        switch (number) {
        case 1:
        {
            addPipe(pipes);
            break;
        }
        case 2:
        {
            addKS(kss);
            break;
        }
        case 3:
        {
            showAllPipes(pipes);
            break;
        }
        case 4:
        {
            showAllKS(kss);
            break;
        }
        case 5:
        {
            searchPipes(pipes);
            break;
        }
        case 6:
        {
            searchKS(kss);
            break;
        }
        case 7:
        {
            batchEditPipes(pipes);
            break;
        }
        case 8:
        {
            editKS(kss);
            break;
        }
        case 9:
        {
            deleteObject(pipes, kss);
            break;
        }
        case 10:
        {
            saveToFile(pipes, kss);
            break;
        }
        case 11:
        {
            loadFromFile(pipes, kss);
            break;
        }
        case 0:
        {
            cout << "Выход из программы!\n";
            return;
        }
        default:
            cout << "Попробуйте ввести ещё раз, такого числа нет!\n" << endl;
            break;
        };
    };
};

int main()
{
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");

    // ПРИНУДИТЕЛЬНЫЙ СБРОС ПОТОКА ВВОДА
    std::cin.clear(); // Сбрасываем флаги ошибок (включая EOF)
    std::cin.seekg(0, std::ios::beg); // Перемещаемся в начало потока

    Logger::getInstance().init("session.txt");

    unordered_map<int,Pipe> pipes;
    unordered_map<int, KS> kss;

    menu(pipes, kss);
    return 0;
}
