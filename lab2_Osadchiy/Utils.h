#pragma once
#include <iostream>

using namespace std;

// ������� ��� ����� ������
template <typename N>
N GetNumber(const N left_border = 0, const N right_border = std::numeric_limits<N>::max())
{
    N x;
    while (((std::cin >> x).fail()) || (std::cin.peek() != '\n') || (x < left_border) || (x > right_border))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "������������ ����! ���������� �������� �����: " << std::endl;
    }
    std::cerr << x << std::endl;
    return x;
};

std::string GetName()
{
    string name;
    while (true)
    {
        cin.ignore(1000, '\n');
        getline(cin, name);
        if (!name.empty())
        {
            return name;
        }
        else
        {
            cout << "������������ ����! ������� ���������� ���������� ���: " << endl;
        }
    }
    return std::string();
}

//// ������� ��� ������ � �������
//void saveToFile(const vector<Pipe>& pipes, const vector<KS>& kss);
//void loadFromFile(vector<Pipe>& pipes, vector<KS>& kss);
//
//// ������� ��� ������ � ���������
//void deleteObject(vector<Pipe>& pipes, vector<KS>& kss);
//
//// �����������
//void logAction(const string& action);