#pragma once
#include <iostream>
#include <string>

class KS {
public:
    int id;
    std::string name;
    int countWorkshop;
    int countWorkshopInWork;

    static int nextId;

    KS();
    void show() const;
    double getUnusedPercent() const;
};

// Функции для работы с КС
void addKS(std::vector<KS>& kss);
void showAllKS(const std::vector<KS>& kss);
void searchKS(const std::vector<KS>& kss);