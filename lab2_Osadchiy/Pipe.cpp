#include "Pipe.h"
#include "Utils.h"
#include <unordered_map>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;


int Pipe::nextId = 1;

Pipe::Pipe() {
    id = nextId++;
    name = "";
    length = 0;
    diameter = 0;
    inRepair = false;
}

void Pipe::show() const {
    cout << "Труба ID: " << id << endl;
    cout << "  Название: " << name << endl;
    cout << "  Длина: " << length << " км" << endl;
    cout << "  Диаметр: " << diameter << " мм" << endl;
    cout << "  В ремонте: " << (inRepair ? "Да" : "Нет") << endl;
    cout << "------------------------" << endl;
}

ostream& operator<<(ostream& out, const Pipe& pipe)
{
    cout << endl;
    cout << "------------------------" << endl;
    cout << "Труба ID: " << pipe.id << endl;
    cout << "Название: " << pipe.name << std::endl;
    cout << "Длина: " << pipe.length << " км" << std::endl;
    cout << "Диаметр: " << pipe.diameter << " мм" << std::endl;
    cout << "В ремонте: " << (pipe.inRepair ? "Да" : "Нет") << std::endl;
    cout << "------------------------" << endl;
    return out;
}

istream& operator>>(istream& in, Pipe& pipe) {
    cout << "Введите название Трубы: ";
    pipe.name = GetName();
    cout << "Введите длину трубы в км: ";
    pipe.length = GetNumber(0.01);
    cout << "Введите диаметр трубы в мм: ";
    pipe.diameter = GetNumber(1);
    cout << "Труба в ремонте (1 - ДА | 0 - НЕТ): ";
    pipe.inRepair = GetNumber(0,1);

    return in;
}

ofstream& operator<<(ofstream& out, const Pipe& pipe) {
    out << "PIPE" << endl;
    out << pipe.id << endl;
    out << pipe.name << endl;
    out << pipe.length << endl;
    out << pipe.diameter << endl;
    out << pipe.inRepair << endl;
    return out;
}

ifstream& operator>>(ifstream& in, Pipe& pipe) {
    in >> pipe.id;
    in.ignore();
    getline(in, pipe.name);
    in >> pipe.length >> pipe.diameter >> pipe.inRepair;
    in.ignore();
    return in;
}

void addPipe(unordered_map<int, Pipe>& pipes) {
    Pipe newPipe;
    cin >> newPipe;
    pipes[newPipe.id] = newPipe;
    cout << "Труба добавлена! ID: " << newPipe.id << endl;
    
}

//void showAllPipes(const vector<Pipe>& pipes) {
//    if (pipes.empty()) {
//        cout << "Трубы не найдены!" << endl;
//        return;
//    }
//    for (const auto& pipe : pipes) {
//        pipe.show();
//    }
//}
//
//void searchPipes(const vector<Pipe>& pipes) {
//    cout << "Поиск труб:" << endl;
//    cout << "1. По названию" << endl;
//    cout << "2. По статусу ремонта" << endl;
//    cout << "Выберите вариант: ";
//
//    int choice = inputInt();
//
//    if (choice == 1) {
//        cout << "Введите название для поиска: ";
//        string searchName;
//        getline(cin, searchName);
//
//        bool found = false;
//        for (const auto& pipe : pipes) {
//            if (pipe.name.find(searchName) != string::npos) {
//                pipe.show();
//                found = true;
//            }
//        }
//        if (!found) {
//            cout << "Трубы не найдены!" << endl;
//        }
//    }
//    else if (choice == 2) {
//        cout << "Искать трубы в ремонте? (1-да, 0-нет): ";
//        bool searchStatus = inputBool();
//
//        bool found = false;
//        for (const auto& pipe : pipes) {
//            if (pipe.inRepair == searchStatus) {
//                pipe.show();
//                found = true;
//            }
//        }
//        if (!found) {
//            cout << "Трубы не найдены!" << endl;
//        }
//    }
//}
//
//void batchEditPipes(vector<Pipe>& pipes) {
//    cout << "Пакетное редактирование труб:" << endl;
//    cout << "1. Редактировать все трубы" << endl;
//    cout << "2. Выбрать трубы для редактирования" << endl;
//    cout << "Выберите вариант: ";
//
//    int choice = inputInt();
//    vector<int> selectedIds;
//
//    if (choice == 1) {
//        // Выбираем все трубы
//        for (const auto& pipe : pipes) {
//            selectedIds.push_back(pipe.id);
//        }
//    }
//    else if (choice == 2) {
//        cout << "Введите ID труб через пробел (0 для завершения): ";
//        int id;
//        while (cin >> id && id != 0) {
//            selectedIds.push_back(id);
//        }
//        cin.ignore(10000, '\n');
//    }
//
//    if (selectedIds.empty()) {
//        cout << "Нет выбранных труб!" << endl;
//        return;
//    }
//
//    cout << "Новый статус ремонта (1-в ремонте, 0-работает): ";
//    bool newStatus = inputBool();
//
//    int count = 0;
//    for (auto& pipe : pipes) {
//        if (find(selectedIds.begin(), selectedIds.end(), pipe.id) != selectedIds.end()) {
//            pipe.inRepair = newStatus;
//            count++;
//        }
//    }
//
//    cout << "Изменено " << count << " труб" << endl;
//}