#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "Ks.h"
#include "Utils.h"

using namespace std;


void menu(vector<Pipe>& pipes, vector<KS>& kss) {
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
            addPipe(pipe);
            pipe_existence = true;
            cout << endl;
            cout << "Труба '" << pipe.name << "' была успешно добавлена!\n" << endl;
            break;
        }
        case 2:
        {
            addKs(ks);
            ks_existence = true;
            cout << endl;
            cout << "Компрессорная станция '" << ks.name << "' была успешно добавлена!\n" << endl;
            break;
        }
        case 3:
        {
            showAll(pipe, ks);
            break;
        }
        case 4:
        {
            if (pipe_existence) {
                changePipe(pipe);
            }
            else {
                cout << "У вас не создана труба!\n" << endl;
            }
            break;
        }
        case 5:
        {
            if (ks_existence) {
                changeKs(ks);
            }
            else {
                cout << "У вас не создана КС!\n" << endl;
            }
            break;
        }
        case 6:
        {
            if (pipe_existence or ks_existence) {
                saveToFile(pipe, ks);
            }
            else {
                cout << "Нет данных для сохранения!\n" << endl;
            }
            break;
        }
        case 7:
        {
            if (loadFromFile(pipe, ks)) {
                pipe_existence = (pipe.diameter > 0);
                ks_existence = (ks.countWorkshop > 0);
                cout << "Данные загружены успешно!\n" << endl;
            }
            break;
        }
        case 8:
        {
            cout << "Выход из программы!\n";
            return;
        }
        case 9:
        {
            cout << "Выход из программы!\n";
            return;
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

    vector<Pipe> pipes;
    vector<KS> kss;
    menu(pipes, kss);

    return 0;
}
