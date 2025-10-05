#include "KS.h"
#include "Utils.h"
#include <unordered_map>

using namespace std;

int KS::nextId = 1;

KS::KS() {
    id = nextId++;
    name = "";
    countWorkshop = 0;
    countWorkshopInWork = 0;
    other = "";
}

void KS::show() const {
    double unusedPercent = getUnusedPercent();
    cout << "КС ID: " << id << endl;
    cout << "  Название: " << name << endl;
    cout << "  Цехов всего: " << countWorkshop << endl;
    cout << "  Цехов работает: " << countWorkshopInWork << endl;
    cout << "  Незадействовано: " << unusedPercent << "%" << endl;
    cout << "  Класс станции: " << other << endl;
    cout << "------------------------" << endl;
}

double KS::getUnusedPercent() const {
    if (countWorkshop == 0) return 0;
    return ((countWorkshop - countWorkshopInWork) * 100.0) / countWorkshop;
}

void addKS(unordered_map<int, KS>& kss) {
    KS newKS;
    cout << "Введите название КС: ";
    getline(cin, newKS.name);
    cout << "Введите общее количество цехов: ";
    newKS.countWorkshop = inputInt();
    cout << "Введите количество работающих цехов: ";
    newKS.countWorkshopInWork = inputInt();

    while (newKS.countWorkshopInWork > newKS.countWorkshop) {
        cout << "Ошибка! Работающих цехов не может быть больше общего количества!" << endl;
        cout << "Введите количество работающих цехов: ";
        newKS.countWorkshopInWork = inputInt();
    }

    cout << "Введите класс стацнии: ";
    cin >> newKS.other;

    kss[newKS.id] = newKS;
    cout << "КС добавлена! ID: " << newKS.id << endl;
}

//void showAllKS(const vector<KS>& kss) {
//    if (kss.empty()) {
//        cout << "КС не найдены!" << endl;
//        return;
//    }
//    for (const auto& ks : kss) {
//        ks.show();
//    }
//}
//
//void searchKS(const vector<KS>& kss) {
//    cout << "Поиск КС:" << endl;
//    cout << "1. По названию" << endl;
//    cout << "2. По проценту незадействованных цехов" << endl;
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
//        for (const auto& ks : kss) {
//            if (ks.name.find(searchName) != string::npos) {
//                ks.show();
//                found = true;
//            }
//        }
//        if (!found) {
//            cout << "КС не найдены!" << endl;
//        }
//    }
//    else if (choice == 2) {
//        cout << "Введите минимальный процент незадействованных цехов: ";
//        float minPercent = inputFloat();
//
//        bool found = false;
//        for (const auto& ks : kss) {
//            if (ks.getUnusedPercent() >= minPercent) {
//                ks.show();
//                found = true;
//            }
//        }
//        if (!found) {
//            cout << "КС не найдены!" << endl;
//        }
//    }
//}