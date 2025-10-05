#include "Pipe.h"
#include "Utils.h"
#include <unordered_map>
#include <algorithm>

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


void addPipe(unordered_map<int, Pipe>& pipes) {
    Pipe newPipe;
    cout << "Введите название трубы: ";
    getline(cin, newPipe.name);
    cout << "Введите длину трубы (км): ";
    newPipe.length = inputFloat();
    cout << "Введите диаметр трубы (мм): ";
    newPipe.diameter = inputInt();
    cout << "Труба в ремонте? (1-да, 0-нет): ";
    int repair;
    while (true) {
        cin >> repair;
        if (cin.fail() or (repair != 0 and repair != 1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Вы ввели некорректные данные. Попробуйте ещё раз!" << endl;
            cout << "Труба в ремонте? (1 если да и 0 если не в ремонте): ";
        }
        else {
            newPipe.inRepair = repair;
            break;
        }
    }

    pipes[newPipe.id]= newPipe;
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