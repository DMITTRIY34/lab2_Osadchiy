#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


class KS {
private:
    int id;
    string name;
    int countWorkshop;
    int countWorkshopInWork;
    string other;
public:
    static int nextId;

    KS();

    void show() const;

    // �������, ����� �������� ��������, ��� �������
    int getId() const { return id; }
    string getName() const { return name; }
    

    double getUnusedPercent() const;

    friend ostream& operator << (ostream& out, const KS& ks);
    friend istream& operator >> (istream& in, KS& ks);
    friend ofstream& operator << (ofstream& out, const KS& ks);
    friend ifstream& operator >> (ifstream& in, KS& ks);
};

// ������� ��� ������ � ��
void addKS(unordered_map<int, KS>& kss);
void showAllKS(const unordered_map<int, KS>& kss);
void searchKS(const unordered_map<int, KS>& kss);
