#pragma once
#include <iostream>
#include "Ks.h"
#include "Pipe.h"
#include "Logger.h"

using namespace std;

// ������ ��� �������� �����������
#define LOG(message) Logger::getInstance().log(message)

// ������� ��� ����� ������
template <typename N>
N GetNumber(const N left_border = 0, const N right_border = std::numeric_limits<N>::max())
{
    N x;
    while (true)
    {
        cin >> x;
        cout << x;
        // ��������� ���������� ����� � ��� ��������� ������ - ����� ������
        if (cin.good() && cin.peek() == '\n' && x >= left_border && x <= right_border)
        {
            cin.ignore(1000, '\n'); // ������� �����
            LOG(to_string(x));
            return x;
        }
        else
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "������������ ����! ���������� �������� �����: " << endl;
            LOG(to_string(x));
        }
    }
};


string GetName();

// ������� ��� ������ � �������
void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, KS>& kss);
void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss);

// ������� ��� ������ � ���������
void deleteObject(unordered_map<int, Pipe>& pipes, unordered_map<int, KS>& kss);

