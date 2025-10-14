#pragma once
#include <iostream>
#include <unordered_map>
#include "Utils.h"
#include <string>

using namespace std;


class KS {
    int id;
    string name;
    int countWorkshop;
    int countWorkshopInWork;
    string other;
public:
    static int nextId;

    KS();
    void show() const;
    double getUnusedPercent() const;


    friend ostream& operator << (ostream& out, const KS& ks);
    friend istream& operator >> (istream& in, KS& ks);
    friend ofstream& operator << (ofstream& out, const KS& ks);
    friend ifstream& operator >> (ifstream& in, KS& ks);

    friend void addKS(unordered_map<int, KS>& kss);
};

// Функции для работы с КС

//void showAllKS(const unordered_map<int, KS>& kss);
//void searchKS(const unordered_map<int, KS>& kss);
