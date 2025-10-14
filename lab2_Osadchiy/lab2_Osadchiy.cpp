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
    bool pipe_existence = false;
    bool ks_existence = false;
    int number;
    while (true)
    {
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотр всех объектов" << endl;
        cout << "4. Поиск" << endl;
        cout << "5. Редактировать трубу" << endl;
        cout << "6. Редактировать КС" << endl;
        cout << "7. Сохранить в файл" << endl;
        cout << "8. Загрузить из файла" << endl;
        cout << "9. Удалить объект" << endl;
        cout << "10. Выход" << endl;
        cout << "Выберите действие: ";

        number = inputInt();
        cout << endl;
        switch (number) {
        case 1:
        {

        }
        case 2:
        {

        }
        case 3:
        {

        }
        case 4:
        {

        }
        case 5:
        {

        }
        case 6:
        {

        }
        case 7:
        {

        }
        case 8:
        {

        }
        case 9:
        {

        }
        case 10:
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

    unordered_map<int,Pipe> pipes;
    unordered_map<int, KS> kss;
    menu(pipes, kss);

    return 0;
}
