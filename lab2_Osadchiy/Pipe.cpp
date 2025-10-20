#include "Pipe.h"
#include "Utils.h"
#include <unordered_map>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;


int Pipe::nextId = 0;

Pipe::Pipe() {
    id = nextId++;   
    name = "";
    length = 0;
    diameter = 0;
    inRepair = false;
}


void Pipe::show() const {
    cout << "------------------------" << endl;
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
    //out << "PIPE" << endl;
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
    pipes[newPipe.getId()] = newPipe;
    cout << "����� ���������! ID: " << newPipe.getId() << endl;
}

void showAllPipes(const unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "����� �� �������!" << endl;
        return;
    }
    for (const auto& item : pipes) {
        item.second.show();
    }
}

void searchPipes(const unordered_map<int, Pipe>& pipes) {
    cout << "����� ����:" << endl;
    cout << "1. �� ��������" << endl;
    cout << "2. �� ������� �������" << endl;
    cout << "�������� �������: ";

    int choice = GetNumber(1,2);
    string searchName;
    string searchStatus;
    bool found;
    switch (choice) {
    case 1:
        cout << "������� �������� ��� ������: ";
        searchName = GetName();

        found = false;
        for (const auto& item : pipes) {
            if (item.second.getName().find(searchName) != string::npos) {
                item.second.show();
                found = true;
            }
        }
        if (!found) {
            cout << "����� �� �������!" << endl;
        }
        break;
    case 2:
        cout << "������ ����� � �������? (1-��, 0-���): ";
        bool searchStatus = GetNumber(0,1);

        bool found = false;
        for (const auto& item : pipes) {
            if (item.second.isInRepair() == searchStatus) {
                item.second.show();
                found = true;
            }
        }
        if (!found) {
            cout << "����� �� �������!" << endl;
        }
        break;
    }
}

void batchEditPipes(unordered_map<int, Pipe>& pipes) {
    unordered_map<int, Pipe> selectedPipes;
    cout << "�������� �������������� ����:" << endl;
    cout << "1. ������������� ��� �����" << endl;
    cout << "2. ������� ����� ��� ��������������" << endl;
    cout << "�������� �������: ";

    int choice = GetNumber(1,2);

    if (choice == 1) {
        selectedPipes = pipes;
    }
    else if (choice == 2) {
        cout << "������ ��� ������ ����:" << endl;
        cout << "1. �� ��������" << endl;
        cout << "2. �� ������� �������" << endl;
        cout << "�������� �������: ";

        int filterChoice = GetNumber(1, 2);

        if (filterChoice == 1) {
            cout << "������� �������� ��� ������: ";
            string searchName = GetName();
            for (const auto& item : pipes) {
                if (item.second.getName().find(searchName) != string::npos) {
                    selectedPipes[item.first] = item.second;
                }
            }
        }
        else if (filterChoice == 2) {
            cout << "������ ����� � �������? (1-��, 0-���): ";
            bool searchStatus = GetNumber(0, 1);
            for (const auto& item : pipes) {
                if (item.second.isInRepair() == searchStatus) {
                    selectedPipes[item.first] = item.second;
                }
            }
        }
    }
    if (selectedPipes.empty()) {
        cout << "��� ��������� ����!" << endl;
        return;
    }

    cout << "������� " << selectedPipes.size() << " ����:" << endl;
    for (const auto& item : selectedPipes) {
        cout << item.second;
    }

    cout << "����� ������ ������� (1-� �������, 0-��������): ";
    bool newStatus = GetNumber(0, 1);

    for (auto& item : selectedPipes) {
        pipes[item.first].setRepair(newStatus);
    }

    cout << "�������� " << selectedPipes.size() << " ����" << endl;
}