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
    cout << "����� ID: " << id << endl;
    cout << "  ��������: " << name << endl;
    cout << "  �����: " << length << " ��" << endl;
    cout << "  �������: " << diameter << " ��" << endl;
    cout << "  � �������: " << (inRepair ? "��" : "���") << endl;
    cout << "------------------------" << endl;
}

ostream& operator<<(ostream& out, const Pipe& pipe)
{
    cout << endl;
    cout << "------------------------" << endl;
    cout << "����� ID: " << pipe.id << endl;
    cout << "��������: " << pipe.name << std::endl;
    cout << "�����: " << pipe.length << " ��" << std::endl;
    cout << "�������: " << pipe.diameter << " ��" << std::endl;
    cout << "� �������: " << (pipe.inRepair ? "��" : "���") << std::endl;
    cout << "------------------------" << endl;
    return out;
}

istream& operator>>(istream& in, Pipe& pipe) {
    cout << "������� �������� �����: ";
    pipe.name = GetName();
    cout << "������� ����� ����� � ��: ";
    pipe.length = GetNumber(0.01);
    cout << "������� ������� ����� � ��: ";
    pipe.diameter = GetNumber(1);
    cout << "����� � ������� (1 - �� | 0 - ���): ";
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
    cout << "����� ���������! ID: " << newPipe.id << endl;
    
}

//void showAllPipes(const vector<Pipe>& pipes) {
//    if (pipes.empty()) {
//        cout << "����� �� �������!" << endl;
//        return;
//    }
//    for (const auto& pipe : pipes) {
//        pipe.show();
//    }
//}
//
//void searchPipes(const vector<Pipe>& pipes) {
//    cout << "����� ����:" << endl;
//    cout << "1. �� ��������" << endl;
//    cout << "2. �� ������� �������" << endl;
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
//        for (const auto& pipe : pipes) {
//            if (pipe.name.find(searchName) != string::npos) {
//                pipe.show();
//                found = true;
//            }
//        }
//        if (!found) {
//            cout << "����� �� �������!" << endl;
//        }
//    }
//    else if (choice == 2) {
//        cout << "������ ����� � �������? (1-��, 0-���): ";
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
//            cout << "����� �� �������!" << endl;
//        }
//    }
//}
//
//void batchEditPipes(vector<Pipe>& pipes) {
//    cout << "�������� �������������� ����:" << endl;
//    cout << "1. ������������� ��� �����" << endl;
//    cout << "2. ������� ����� ��� ��������������" << endl;
//    cout << "�������� �������: ";
//
//    int choice = inputInt();
//    vector<int> selectedIds;
//
//    if (choice == 1) {
//        // �������� ��� �����
//        for (const auto& pipe : pipes) {
//            selectedIds.push_back(pipe.id);
//        }
//    }
//    else if (choice == 2) {
//        cout << "������� ID ���� ����� ������ (0 ��� ����������): ";
//        int id;
//        while (cin >> id && id != 0) {
//            selectedIds.push_back(id);
//        }
//        cin.ignore(10000, '\n');
//    }
//
//    if (selectedIds.empty()) {
//        cout << "��� ��������� ����!" << endl;
//        return;
//    }
//
//    cout << "����� ������ ������� (1-� �������, 0-��������): ";
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
//    cout << "�������� " << count << " ����" << endl;
//}