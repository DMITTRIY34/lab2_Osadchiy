#include "Pipe.h"
#include <vector>
#include <algorithm>

int Pipe::nextId = 1;

Pipe::Pipe() {
    id = nextId++;
    name = "";
    length = 0;
    diameter = 0;
    inRepair = false;
}

void Pipe::show() const {
    std::cout << "����� ID: " << id << std::endl;
    std::cout << "  ��������: " << name << std::endl;
    std::cout << "  �����: " << length << " ��" << std::endl;
    std::cout << "  �������: " << diameter << " ��" << std::endl;
    std::cout << "  � �������: " << (inRepair ? "��" : "���") << std::endl;
    std::cout << "------------------------" << std::endl;
}

// ������� ����� (������� �����, ��������� � utils)
int inputInt();
double inputDouble();
bool inputBool();

void addPipe(std::vector<Pipe>& pipes) {
    Pipe newPipe;
    std::cout << "������� �������� �����: ";
    std::getline(std::cin, newPipe.name);
    std::cout << "������� ����� ����� (��): ";
    newPipe.length = inputDouble();
    std::cout << "������� ������� ����� (��): ";
    newPipe.diameter = inputInt();
    std::cout << "����� � �������? (1-��, 0-���): ";
    newPipe.inRepair = inputBool();

    pipes.push_back(newPipe);
    std::cout << "����� ���������! ID: " << newPipe.id << std::endl;
}

void showAllPipes(const std::vector<Pipe>& pipes) {
    if (pipes.empty()) {
        std::cout << "����� �� �������!" << std::endl;
        return;
    }
    for (const auto& pipe : pipes) {
        pipe.show();
    }
}

void searchPipes(const std::vector<Pipe>& pipes) {
    std::cout << "����� ����:" << std::endl;
    std::cout << "1. �� ��������" << std::endl;
    std::cout << "2. �� ������� �������" << std::endl;
    std::cout << "�������� �������: ";

    int choice = inputInt();

    if (choice == 1) {
        std::cout << "������� �������� ��� ������: ";
        std::string searchName;
        std::getline(std::cin, searchName);

        bool found = false;
        for (const auto& pipe : pipes) {
            if (pipe.name.find(searchName) != std::string::npos) {
                pipe.show();
                found = true;
            }
        }
        if (!found) {
            std::cout << "����� �� �������!" << std::endl;
        }
    }
    else if (choice == 2) {
        std::cout << "������ ����� � �������? (1-��, 0-���): ";
        bool searchStatus = inputBool();

        bool found = false;
        for (const auto& pipe : pipes) {
            if (pipe.inRepair == searchStatus) {
                pipe.show();
                found = true;
            }
        }
        if (!found) {
            std::cout << "����� �� �������!" << std::endl;
        }
    }
}

void batchEditPipes(std::vector<Pipe>& pipes) {
    std::cout << "�������� �������������� ����:" << std::endl;
    std::cout << "1. ������������� ��� �����" << std::endl;
    std::cout << "2. ������� ����� ��� ��������������" << std::endl;
    std::cout << "�������� �������: ";

    int choice = inputInt();
    std::vector<int> selectedIds;

    if (choice == 1) {
        // �������� ��� �����
        for (const auto& pipe : pipes) {
            selectedIds.push_back(pipe.id);
        }
    }
    else if (choice == 2) {
        std::cout << "������� ID ���� ����� ������ (0 ��� ����������): ";
        int id;
        while (std::cin >> id && id != 0) {
            selectedIds.push_back(id);
        }
        std::cin.ignore(10000, '\n');
    }

    if (selectedIds.empty()) {
        std::cout << "��� ��������� ����!" << std::endl;
        return;
    }

    std::cout << "����� ������ ������� (1-� �������, 0-��������): ";
    bool newStatus = inputBool();

    int count = 0;
    for (auto& pipe : pipes) {
        if (std::find(selectedIds.begin(), selectedIds.end(), pipe.id) != selectedIds.end()) {
            pipe.inRepair = newStatus;
            count++;
        }
    }

    std::cout << "�������� " << count << " ����" << std::endl;
}