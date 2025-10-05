#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Pipe {
public:
    int id;
    string name;
    double length;
    int diameter;
    bool inRepair;

    static int nextId;

    Pipe();
    void show() const;
};

// Функции для работы с трубами
void addPipe(unordered_map<int, Pipe>& pipes);
//void showAllPipes(const unordered_map<int, Pipe>& pipes);
//void searchPipes(const unordered_map<int, Pipe>& pipes);
//void batchEditPipes(unordered_map<int, Pipe>& pipes);

