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
            cout << "������������ ����! ������� ���������� ���������� ���: " << endl;
        }
    }
    return std::string();
}

void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, KS>& kss) {
    cout << "������� ��� ����� ��� ����������: ";
    string filename = GetName();

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "������ �������� �����!" << endl;
        return;
    }

    // ��������� �����
    file << pipes.size() << endl;
    for (const auto& item : pipes) {
        file << item.second;
    }

    // ��������� ��
    file << kss.size() << endl;
    for (const auto& item : kss) {
        file << item.second;
    }

    file.close();
    cout << "������ ��������� � ����: " << filename << endl;
}

void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss) {
    cout << "������� ��� ����� ��� ��������: ";
    string filename = GetName();

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "������ �������� �����!" << endl;
        return;
    }

    // ������� ������� ������
    pipes.clear();
    kss.clear();

    // ��������� �����
    int pipeCount;
    file >> pipeCount;
    file.ignore();

    for (int i = 0; i < pipeCount; i++) {
        Pipe pipe;
        file >> pipe;
        pipes[pipe.getId()] = pipe;
    }

    // ��������� ��
    int ksCount;
    file >> ksCount;
    file.ignore();

    for (int i = 0; i < ksCount; i++) {
        KS ks;
        file >> ks;
        kss[ks.getId()] = ks;
    }

    file.close();

    // ��������� nextId
    int maxPipeId = 0, maxKSId = 0;
    for (const auto& item : pipes) {
        if (item.first > maxPipeId) maxPipeId = item.first;
    }
    for (const auto& item : kss) {
        if (item.first > maxKSId) maxKSId = item.first;
    }

    cout << "������ ��������� �� �����: " << filename << endl;
}

void deleteObject(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss) {
    cout << "��� �� ������ �������?" << endl;
    cout << "1. �����" << endl;
    cout << "2. ��" << endl;
    cout << "�������� �������: ";

    int choice = GetNumber<int>(1, 2);

    switch (choice) {
    case 1: {
        // �������� �����
        if (pipes.empty()) {
            cout << "��� ��������� ���� ��� ��������!" << endl;
            return;
        }

        cout << "��������� �����:" << endl;
        for (const auto& item : pipes) {
            cout << "ID: " << item.first << " - " << item.second.getName() << endl;
        }

        cout << "������� ID ����� ��� ��������: ";
        int id = GetNumber<int>(0);

        auto pipeIt = pipes.find(id);
        if (pipeIt != pipes.end()) {
            pipes.erase(pipeIt);
            cout << "����� �������!" << endl;
        }
        else {
            cout << "����� � ID " << id << " �� �������!" << endl;
        }
        break;
    }

    case 2: {
        // �������� ��
        if (kss.empty()) {
            cout << "��� ��������� �� ��� ��������!" << endl;
            return;
        }

        cout << "��������� ��:" << endl;
        for (const auto& item : kss) {
            cout << "ID: " << item.first << " - " << item.second.getName() << endl;
        }

        cout << "������� ID �� ��� ��������: ";
        int id = GetNumber<int>(0);

        auto ksIt = kss.find(id);
        if (ksIt != kss.end()) {
            kss.erase(ksIt);
            cout << "�� �������!" << endl;
        }
        else {
            cout << "�� � ID " << id << " �� �������!" << endl;
        }
        break;
    }

    }
}

