#include "KS.h"
#include "Utils.h"
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

int KS::nextId = 0;

KS::KS() {
    id = nextId++;
}


void KS::show() const {
    double unusedPercent = getUnusedPercent();
    cout << endl;
    cout << "------------------------" << endl;
    cout << "КС ID: " << id << endl;
    cout << "Название: " << name << std::endl;
    cout << "Цехов всего: " << countWorkshop <<endl;
    cout << "Цехов в работе: " << countWorkshopInWork << std::endl;
    cout << "Незадействовано: " << unusedPercent << "%" << std::endl;
    cout << "Класс станции: " << other << endl;
    cout << "------------------------" << endl;
}

ostream& operator<<(ostream& out, const KS& ks)
{
    double unusedPercent = ks.getUnusedPercent();
    cout << endl;
    cout << "------------------------" << endl;
    cout << "КС ID: " << ks.id << endl;
    cout << "Название: " << ks.name << std::endl;
    cout << "Цехов всего: " << ks.countWorkshop << std::endl;
    cout << "Цехов в работе: " << ks.countWorkshopInWork << std::endl;
    cout << "Незадействовано: " << unusedPercent << "%" << std::endl;
    cout << "Класс станции: " << ks.other << endl;
    cout << "------------------------" << endl;
    return out;
}

istream& operator>>(istream& in, KS& ks) {
    cout << "Введите название КС: ";
    ks.name = GetName();
    cout << "Введите общее количество цехов: ";
    ks.countWorkshop = GetNumber(1);
    cout << "Введите количество работающих цехов: ";
    ks.countWorkshopInWork = GetNumber(0, ks.countWorkshop);
    cout << "Введите класс станции (string): ";
    ks.other = GetName();
    return in;
}

ofstream& operator<<(ofstream& out, const KS& ks)
{
    out << "KS" << endl;
    out << ks.id << endl;
    out << ks.name << endl;
    out << ks.countWorkshop << endl;
    out << ks.countWorkshopInWork << endl;
    out << ks.other << endl;
    return out;
}

ifstream& operator>>(ifstream& in, KS& ks)
{
    in >> ks.id;
    in.ignore();
    getline(in, ks.name);
    in >> ks.countWorkshop >> ks.countWorkshopInWork;
    in.ignore();
    getline(in, ks.other);
    return in;
}

double KS::getUnusedPercent() const {
    if (countWorkshop == 0) return 0;
    return ((countWorkshop - countWorkshopInWork) * 100.0) / countWorkshop;
}

void addKS(unordered_map<int, KS>& kss) {
    KS newKS;
    cin >> newKS;
    kss[newKS.getId()] = newKS;
    cout << "КС добавлена! ID: " << newKS.getId() << endl;
}

void showAllKS(const unordered_map<int, KS>& kss) {
    if (kss.empty()) {
        cout << "КС не найдены!" << endl;
        return;
    }
    for (const auto& item : kss) {
        item.second.show();
    }
}

void searchKS(const unordered_map<int, KS>& kss) {
    cout << "Поиск КС:" << endl;
    cout << "1. По названию" << endl;
    cout << "2. По проценту незадействованных цехов" << endl;
    cout << "Выберите вариант: ";

    int choice = GetNumber(1,2);
    string searchName;
    bool found;
    switch (choice) {
    case 1:
        cout << "Введите название для поиска: ";
        searchName = GetName();

        found = false;
        for (const auto& item : kss) {
            if (item.second.getName().find(searchName) != string::npos) {
                item.second.show();
                found = true;
            }
        }
        if (!found) {
            cout << "КС не найдены!" << endl;
        }
        break;
    case 2:
        cout << "Введите минимальный процент незадействованных цехов: ";
        float minPercent = GetNumber(0,100);

        bool found = false;
        for (const auto& item : kss) {
            if (item.second.getUnusedPercent() >= minPercent) {
                item.second.show();
                found = true;
            }
        }
        if (!found) {
            cout << "КС не найдены!" << endl;
        }
        break;
    }
}