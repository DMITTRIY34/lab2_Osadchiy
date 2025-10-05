#include "KS.h"
#include <vector>

int KS::nextId = 1;

KS::KS() {
    id = nextId++;
    name = "";
    countWorkshop = 0;
    countWorkshopInWork = 0;
}

void KS::show() const {
    double unusedPercent = getUnusedPercent();
    std::cout << "�� ID: " << id << std::endl;
    std::cout << "  ��������: " << name << std::endl;
    std::cout << "  ����� �����: " << countWorkshop << std::endl;
    std::cout << "  ����� ��������: " << countWorkshopInWork << std::endl;
    std::cout << "  ���������������: " << unusedPercent << "%" << std::endl;
    std::cout << "------------------------" << std::endl;
}

double KS::getUnusedPercent() const {
    if (countWorkshop == 0) return 0;
    return ((countWorkshop - countWorkshopInWork) * 100.0) / countWorkshop;
}

// ������� ����� (������� �����, ��������� � utils)
int inputInt();
double inputDouble();

void addKS(std::vector<KS>& kss) {
    KS newKS;
    std::cout << "������� �������� ��: ";
    std::getline(std::cin, newKS.name);
    std::cout << "������� ����� ���������� �����: ";
    newKS.totalWorkshops = inputInt();
    std::cout << "������� ���������� ���������� �����: ";
    newKS.workingWorkshops = inputInt();

    while (newKS.workingWorkshops > newKS.totalWorkshops) {
        std::cout << "������! ���������� ����� �� ����� ���� ������ ������ ����������!" << std::endl;
        std::cout << "������� ���������� ���������� �����: ";
        newKS.workingWorkshops = inputInt();
    }

    kss.push_back(newKS);
    std::cout << "�� ���������! ID: " << newKS.id << std::endl;
}

void showAllKS(const std::vector<KS>& kss) {
    if (kss.empty()) {
        std::cout << "�� �� �������!" << std::endl;
        return;
    }
    for (const auto& ks : kss) {
        ks.show();
    }
}

void searchKS(const std::vector<KS>& kss) {
    std::cout << "����� ��:" << std::endl;
    std::cout << "1. �� ��������" << std::endl;
    std::cout << "2. �� �������� ����������������� �����" << std::endl;
    std::cout << "�������� �������: ";

    int choice = inputInt();

    if (choice == 1) {
        std::cout << "������� �������� ��� ������: ";
        std::string searchName;
        std::getline(std::cin, searchName);

        bool found = false;
        for (const auto& ks : kss) {
            if (ks.name.find(searchName) != std::string::npos) {
                ks.show();
                found = true;
            }
        }
        if (!found) {
            std::cout << "�� �� �������!" << std::endl;
        }
    }
    else if (choice == 2) {
        std::cout << "������� ����������� ������� ����������������� �����: ";
        double minPercent = inputDouble();

        bool found = false;
        for (const auto& ks : kss) {
            if (ks.getUnusedPercent() >= minPercent) {
                ks.show();
                found = true;
            }
        }
        if (!found) {
            std::cout << "�� �� �������!" << std::endl;
        }
    }
}