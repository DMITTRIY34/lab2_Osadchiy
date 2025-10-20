#include "KS.h"
#include "Utils.h"
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

int KS::nextId = 0;


KS::KS() {
    id = nextId++;
    name = "";
    countWorkshop = 0;
    countWorkshopInWork = 0;
    other = "";
}

void KS::show() const {
    double unusedPercent = getUnusedPercent();
    cout << endl;
    cout << "------------------------" << endl;
    cout << "�� ID: " << id << endl;
    cout << "��������: " << name << std::endl;
    cout << "����� �����: " << countWorkshop <<endl;
    cout << "����� � ������: " << countWorkshopInWork << std::endl;
    cout << "���������������: " << unusedPercent << "%" << std::endl;
    cout << "����� �������: " << other << endl;
    cout << "------------------------" << endl;
}

ostream& operator<<(ostream& out, const KS& ks)
{
    double unusedPercent = ks.getUnusedPercent();
    cout << endl;
    cout << "------------------------" << endl;
    cout << "�� ID: " << ks.id << endl;
    cout << "��������: " << ks.name << std::endl;
    cout << "����� �����: " << ks.countWorkshop << std::endl;
    cout << "����� � ������: " << ks.countWorkshopInWork << std::endl;
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
    //out << "KS" << endl;
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
    kss.insert({ newKS.getId(), newKS });
    cout << "�� ���������! ID: " << newKS.getId() << endl;
}

void showAllKS(const unordered_map<int, KS>& kss) {
    if (kss.empty()) {
        cout << "�� �� �������!" << endl;
        return;
    }
    for (const auto& item : kss) {
        item.second.show();
    }
}

void searchKS(const unordered_map<int, KS>& kss) {
    cout << "����� ��:" << endl;
    cout << "1. �� ��������" << endl;
    cout << "2. �� �������� ����������������� �����" << endl;
    cout << "�������� �������: ";

    int choice = GetNumber(1,2);
    string searchName;
    bool found;
    switch (choice) {
    case 1:
        cout << "������� �������� ��� ������: ";
        searchName = GetName();

        found = false;
        for (const auto& item : kss) {
            if (item.second.getName().find(searchName) != string::npos) {
                item.second.show();
                found = true;
            }
        }
        if (!found) {
            cout << "�� �� �������!" << endl;
        }
        break;
    case 2:
        cout << "������� ����������� ������� ����������������� �����: ";
        float minPercent = GetNumber(0,100);

        bool found = false;
        for (const auto& item : kss) {
            if (item.second.getUnusedPercent() >= minPercent) {
                item.second.show();
                found = true;
            }
        }
        if (!found) {
            cout << "�� �� �������!" << endl;
        }
        break;
    }
}

// ������ ��� ���������� ������
void KS::startWorkshops(int count) {
    int available = countWorkshop - countWorkshopInWork;
    if (count > available) {
        throw invalid_argument("������ ��������� ������ " + to_string(available) + " �����");
    }
    countWorkshopInWork += count;
}

void KS::stopWorkshops(int count) {
    if (count > countWorkshopInWork) {
        throw invalid_argument("������ ���������� ������ " + to_string(countWorkshopInWork) + " �����");
    }
    countWorkshopInWork -= count;
}

void editKS(unordered_map<int, KS>& kss) {
    if (kss.empty()) {
        cout << "��� ��������� �� ��� ��������������!" << endl;
        return;
    }

    cout << "��������� ��:" << endl;
    for (const auto& item : kss) {
        cout << "ID: " << item.first << " - " << item.second.getName() << endl;
    }

    cout << "������� ID �� ��� ��������������: ";
    int id = GetNumber(0);

    auto it = kss.find(id);
    if (it == kss.end()) {
        cout << "�� � ID " << id << " �� �������!" << endl;
        return;
    }

    KS& ks = it->second;

    int choice;
    do {
        cout << "\n=== �������������� �� '" << ks.getName() << "' ===" << endl;
        cout << "1. ��������� ����" << endl;
        cout << "2. ���������� ����" << endl;
        cout << "0. ��������� � ����" << endl;
        cout << "�������� ��������: ";

        choice = GetNumber<int>(0, 2);

        switch (choice) {
        case 1: {
            int available = ks.getCountWorkshop() - ks.getCountWorkshopInWork();
            if (available == 0) {
                cout << "��� ���� ��� ��������!" << endl;
                break;
            }
            cout << "����� ��������� �� " << available << " �����: ";
            int count = GetNumber<int>(1, available);
            ks.startWorkshops(count);
            cout << "�������� " << count << " �����. ������ ��������: " << ks.getCountWorkshopInWork() << " �����" << endl;
            break;
        }
        case 2: {
            if (ks.getCountWorkshopInWork() == 0) {
                cout << "��� ���������� �����!" << endl;
                break;
            }
            cout << "����� ���������� �� " << ks.getCountWorkshopInWork() << " �����: ";
            int count = GetNumber(1, ks.getCountWorkshopInWork());
            ks.stopWorkshops(count);
            cout << "����������� " << count << " �����. ������ ��������: " << ks.getCountWorkshopInWork() << " �����" << endl;
            break;
        }
        case 0:
            cout << "����� �� �������������� ��" << endl;
            break;
        }
    } while (choice != 0);
}