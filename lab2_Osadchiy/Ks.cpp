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
    std::cout << "КС ID: " << id << std::endl;
    std::cout << "  Название: " << name << std::endl;
    std::cout << "  Цехов всего: " << countWorkshop << std::endl;
    std::cout << "  Цехов работает: " << countWorkshopInWork << std::endl;
    std::cout << "  Незадействовано: " << unusedPercent << "%" << std::endl;
    std::cout << "------------------------" << std::endl;
}

double KS::getUnusedPercent() const {
    if (countWorkshop == 0) return 0;
    return ((countWorkshop - countWorkshopInWork) * 100.0) / countWorkshop;
}

// Функции ввода (объявим здесь, определим в utils)
int inputInt();
double inputDouble();

void addKS(std::vector<KS>& kss) {
    KS newKS;
    std::cout << "Введите название КС: ";
    std::getline(std::cin, newKS.name);
    std::cout << "Введите общее количество цехов: ";
    newKS.totalWorkshops = inputInt();
    std::cout << "Введите количество работающих цехов: ";
    newKS.workingWorkshops = inputInt();

    while (newKS.workingWorkshops > newKS.totalWorkshops) {
        std::cout << "Ошибка! Работающих цехов не может быть больше общего количества!" << std::endl;
        std::cout << "Введите количество работающих цехов: ";
        newKS.workingWorkshops = inputInt();
    }

    kss.push_back(newKS);
    std::cout << "КС добавлена! ID: " << newKS.id << std::endl;
}

void showAllKS(const std::vector<KS>& kss) {
    if (kss.empty()) {
        std::cout << "КС не найдены!" << std::endl;
        return;
    }
    for (const auto& ks : kss) {
        ks.show();
    }
}

void searchKS(const std::vector<KS>& kss) {
    std::cout << "Поиск КС:" << std::endl;
    std::cout << "1. По названию" << std::endl;
    std::cout << "2. По проценту незадействованных цехов" << std::endl;
    std::cout << "Выберите вариант: ";

    int choice = inputInt();

    if (choice == 1) {
        std::cout << "Введите название для поиска: ";
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
            std::cout << "КС не найдены!" << std::endl;
        }
    }
    else if (choice == 2) {
        std::cout << "Введите минимальный процент незадействованных цехов: ";
        double minPercent = inputDouble();

        bool found = false;
        for (const auto& ks : kss) {
            if (ks.getUnusedPercent() >= minPercent) {
                ks.show();
                found = true;
            }
        }
        if (!found) {
            std::cout << "КС не найдены!" << std::endl;
        }
    }
}