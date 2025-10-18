#pragma once
#include <iostream>
#include "Ks.h"
#include "Pipe.h"
using namespace std;

// ������� ��� ����� ������
template <typename N>
N GetNumber(const N left_border = 0, const N right_border = std::numeric_limits<N>::max())
{
    N x;
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x < left_border) || (x > right_border))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "������������ ����! ���������� �������� �����: " << endl;
    }
    return x;
};

string GetName();

// ������� ��� ������ � �������
void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, KS>& kss);
void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss);

// ������� ��� ������ � ���������
void deleteObject(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss);

//// �����������
//void logAction(const string& action);