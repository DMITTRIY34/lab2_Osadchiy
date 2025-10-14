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

ostream& operator<<(ostream& out, const KS& ks)
{
    double unusedPercent = ks.getUnusedPercent();
    cout << endl;
    cout << "------------------------" << endl;
    cout << "�� ID: " << ks.id << endl;
    cout << "��������: " << ks.name << std::endl;
    cout << "����� �����: " << ks.countWorkshop << std::endl;
    cout << "Number of active workshops: " << ks.countWorkshopInWork << std::endl;
    cout << "���������������: " << unusedPercent << "%" << std::endl;
    cout << "����� �������: " << ks.other << endl;
    cout << "------------------------" << endl;
    return out;
}

istream& operator>>(istream& in, KS& ks) {
    cout << "������� �������� ��: ";
    ks.name = GetName();
    cout << "������� ����� ���������� �����: ";
    ks.countWorkshop = GetNumber(1);
    cout << "������� ���������� ���������� �����: ";
    ks.countWorkshopInWork = GetNumber(0, ks.countWorkshop);
    cout << "������� ����� ������� (string): ";
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