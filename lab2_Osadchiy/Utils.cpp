#include "Utils.h"
#include "Pipe.h"
#include "KS.h"
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

string GetName()
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

void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, KS>& kss) {
    cout << "Введите имя файла для сохранения: ";
    string filename = GetName();

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    // Сохраняем трубы
    file << pipes.size() << endl;
    for (const auto& item : pipes) {
        file << item.second;
    }

    // Сохраняем КС
    file << kss.size() << endl;
    for (const auto& item : kss) {
        file << item.second;
    }

    file.close();
    cout << "Данные сохранены в файл: " << filename << endl;
}

void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss) {
    cout << "Введите имя файла для загрузки: ";
    string filename = GetName();

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    // Очищаем текущие данные
    pipes.clear();
    kss.clear();

    // Загружаем трубы
    int pipeCount;
    file >> pipeCount;
    file.ignore();

    for (int i = 0; i < pipeCount; i++) {
        Pipe pipe;
        file >> pipe;
        pipes[pipe.getId()] = pipe;
    }

    // Загружаем КС
    int ksCount;
    file >> ksCount;
    file.ignore();

    for (int i = 0; i < ksCount; i++) {
        KS ks;
        file >> ks;
        kss[ks.getId()] = ks;
    }

    file.close();

    // Обновляем nextId
    int maxPipeId = 0, maxKSId = 0;
    for (const auto& item : pipes) {
        if (item.first > maxPipeId) maxPipeId = item.first;
    }
    for (const auto& item : kss) {
        if (item.first > maxKSId) maxKSId = item.first;
    }

    cout << "Данные загружены из файла: " << filename << endl;
}

void deleteObject(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss) {
    cout << "Что вы хотите удалить?" << endl;
    cout << "1. Трубу" << endl;
    cout << "2. КС" << endl;
    cout << "Выберите вариант: ";

    int choice = GetNumber<int>(1, 2);

    switch (choice) {
    case 1: {
        // Удаление трубы
        if (pipes.empty()) {
            cout << "Нет доступных труб для удаления!" << endl;
            return;
        }

        cout << "Доступные трубы:" << endl;
        for (const auto& item : pipes) {
            cout << "ID: " << item.first << " - " << item.second.getName() << endl;
        }

        cout << "Введите ID трубы для удаления: ";
        int id = GetNumber<int>(0);

        auto pipeIt = pipes.find(id);
        if (pipeIt != pipes.end()) {
            pipes.erase(pipeIt);
            cout << "Труба удалена!" << endl;
        }
        else {
            cout << "Труба с ID " << id << " не найдена!" << endl;
        }
        break;
    }

    case 2: {
        // Удаление КС
        if (kss.empty()) {
            cout << "Нет доступных КС для удаления!" << endl;
            return;
        }

        cout << "Доступные КС:" << endl;
        for (const auto& item : kss) {
            cout << "ID: " << item.first << " - " << item.second.getName() << endl;
        }

        cout << "Введите ID КС для удаления: ";
        int id = GetNumber<int>(0);

        auto ksIt = kss.find(id);
        if (ksIt != kss.end()) {
            kss.erase(ksIt);
            cout << "КС удалена!" << endl;
        }
        else {
            cout << "КС с ID " << id << " не найдена!" << endl;
        }
        break;
    }

    }
}

