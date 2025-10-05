#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

class KS {
public:
    int id;
    std::string name;
    int countWorkshop;
    int countWorkshopInWork;
    string other;

    static int nextId;

    KS();
    void show() const;
    double getUnusedPercent() const;
};

// Функции для работы с КС
void addKS(unordered_map<int, KS>& kss);
//void showAllKS(const unordered_map<int, KS>& kss);
//void searchKS(const unordered_map<int, KS>& kss);