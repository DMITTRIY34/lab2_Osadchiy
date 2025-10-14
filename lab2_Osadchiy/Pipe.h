#pragma once
#include <iostream>
#include <unordered_map>
#include "Utils.h"
#include <string>

using namespace std;

class Pipe {
    int id;
    string name;
    double length;
    int diameter;
    bool inRepair;
public:
    static int nextId;

    Pipe();
    void show() const;

    friend ostream& operator << (ostream& out, const Pipe& pipe);
    friend istream& operator >> (istream& in, Pipe& pipe);
    friend ofstream& operator << (ofstream& out, const Pipe& pipe);
    friend ifstream& operator >> (ifstream& in, Pipe& pipe);

    friend void addPipe(unordered_map<int, Pipe>& pipes);
};

// Функции для работы с трубами

void showAllPipes(const unordered_map<int, Pipe>& pipes);
void searchPipes(const unordered_map<int, Pipe>& pipes);
void batchEditPipes(unordered_map<int, Pipe>& pipes);

