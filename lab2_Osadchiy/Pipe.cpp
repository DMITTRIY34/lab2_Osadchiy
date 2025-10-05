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
    std::cout << "Труба ID: " << id << std::endl;
    std::cout << "  Название: " << name << std::endl;
    std::cout << "  Длина: " << length << " км" << std::endl;
    std::cout << "  Диаметр: " << diameter << " мм" << std::endl;
    std::cout << "  В ремонте: " << (inRepair ? "Да" : "Нет") << std::endl;
    std::cout << "------------------------" << std::endl;
}

// Функции ввода (объявим здесь, определим в utils)
int inputInt();
double inputDouble();
bool inputBool();

void addPipe(std::vector<Pipe>& pipes) {
    Pipe newPipe;
    std::cout << "Введите название трубы: ";
    std::getline(std::cin, newPipe.name);
    std::cout << "Введите длину трубы (км): ";
    newPipe.length = inputDouble();
    std::cout << "Введите диаметр трубы (мм): ";
    newPipe.diameter = inputInt();
    std::cout << "Труба в ремонте? (1-да, 0-нет): ";
    newPipe.inRepair = inputBool();

    pipes.push_back(newPipe);
    std::cout << "Труба добавлена! ID: " << newPipe.id << std::endl;
}

void showAllPipes(const std::vector<Pipe>& pipes) {
    if (pipes.empty()) {
        std::cout << "Трубы не найдены!" << std::endl;
        return;
    }
    for (const auto& pipe : pipes) {
        pipe.show();
    }
}

void searchPipes(const std::vector<Pipe>& pipes) {
    std::cout << "Поиск труб:" << std::endl;
    std::cout << "1. По названию" << std::endl;
    std::cout << "2. По статусу ремонта" << std::endl;
    std::cout << "Выберите вариант: ";

    int choice = inputInt();

    if (choice == 1) {
        std::cout << "Введите название для поиска: ";
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
            std::cout << "Трубы не найдены!" << std::endl;
        }
    }
    else if (choice == 2) {
        std::cout << "Искать трубы в ремонте? (1-да, 0-нет): ";
        bool searchStatus = inputBool();

        bool found = false;
        for (const auto& pipe : pipes) {
            if (pipe.inRepair == searchStatus) {
                pipe.show();
                found = true;
            }
        }
        if (!found) {
            std::cout << "Трубы не найдены!" << std::endl;
        }
    }
}

void batchEditPipes(std::vector<Pipe>& pipes) {
    std::cout << "Пакетное редактирование труб:" << std::endl;
    std::cout << "1. Редактировать все трубы" << std::endl;
    std::cout << "2. Выбрать трубы для редактирования" << std::endl;
    std::cout << "Выберите вариант: ";

    int choice = inputInt();
    std::vector<int> selectedIds;

    if (choice == 1) {
        // Выбираем все трубы
        for (const auto& pipe : pipes) {
            selectedIds.push_back(pipe.id);
        }
    }
    else if (choice == 2) {
        std::cout << "Введите ID труб через пробел (0 для завершения): ";
        int id;
        while (std::cin >> id && id != 0) {
            selectedIds.push_back(id);
        }
        std::cin.ignore(10000, '\n');
    }

    if (selectedIds.empty()) {
        std::cout << "Нет выбранных труб!" << std::endl;
        return;
    }

    std::cout << "Новый статус ремонта (1-в ремонте, 0-работает): ";
    bool newStatus = inputBool();

    int count = 0;
    for (auto& pipe : pipes) {
        if (std::find(selectedIds.begin(), selectedIds.end(), pipe.id) != selectedIds.end()) {
            pipe.inRepair = newStatus;
            count++;
        }
    }

    std::cout << "Изменено " << count << " труб" << std::endl;
}