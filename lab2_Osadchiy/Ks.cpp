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
    cout << "�� ID: " << id << endl;
    cout << "  ��������: " << name << endl;
    cout << "  ����� �����: " << countWorkshop << endl;
    cout << "  ����� ��������: " << countWorkshopInWork << endl;
    cout << "  ���������������: " << unusedPercent << "%" << endl;
    cout << "  ����� �������: " << other << endl;
    cout << "------------------------" << endl;
}

double KS::getUnusedPercent() const {
    if (countWorkshop == 0) return 0;
    return ((countWorkshop - countWorkshopInWork) * 100.0) / countWorkshop;
}

void addKS(unordered_map<int, KS>& kss) {
    KS newKS;
    cout << "������� �������� ��: ";
    getline(cin, newKS.name);
    cout << "������� ����� ���������� �����: ";
    newKS.countWorkshop = inputInt();
    cout << "������� ���������� ���������� �����: ";
    newKS.countWorkshopInWork = inputInt();

    while (newKS.countWorkshopInWork > newKS.countWorkshop) {
        cout << "������! ���������� ����� �� ����� ���� ������ ������ ����������!" << endl;
        cout << "������� ���������� ���������� �����: ";
        newKS.countWorkshopInWork = inputInt();
    }

    cout << "������� ����� �������: ";
    cin >> newKS.other;

    kss[newKS.id] = newKS;
    cout << "�� ���������! ID: " << newKS.id << endl;
}

//void showAllKS(const vector<KS>& kss) {
//    if (kss.empty()) {
//        cout << "�� �� �������!" << endl;
//        return;
//    }
//    for (const auto& ks : kss) {
//        ks.show();
//    }
//}
//
//void searchKS(const vector<KS>& kss) {
//    cout << "����� ��:" << endl;
//    cout << "1. �� ��������" << endl;
//    cout << "2. �� �������� ����������������� �����" << endl;
//    cout << "�������� �������: ";
//
//    int choice = inputInt();
//
//    if (choice == 1) {
//        cout << "������� �������� ��� ������: ";
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
//            cout << "�� �� �������!" << endl;
//        }
//    }
//    else if (choice == 2) {
//        cout << "������� ����������� ������� ����������������� �����: ";
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
//            cout << "�� �� �������!" << endl;
//        }
//    }
//}