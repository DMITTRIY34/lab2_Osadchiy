#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Pipe {
private:
    int id;
    string name;
    double length;
    int diameter;
    bool inRepair;

public:
    static int nextId;

    Pipe();

    void show() const;

    // Геттеры, чтобы получать значение
    int getId() const { return id; }
    string getName() const { return name; }
    bool isInRepair() const { return inRepair; }

    // Сеттеры
    void setRepair(bool repair) { inRepair = repair; }


    friend ostream& operator << (ostream& out, const Pipe& pipe);
    friend istream& operator >> (istream& in, Pipe& pipe);
    friend ofstream& operator << (ofstream& out, const Pipe& pipe);
    friend ifstream& operator >> (ifstream& in, Pipe& pipe);
    
};

// Функции для работы с трубами
void addPipe(unordered_map<int, Pipe>& pipes);
void searchPipes(const unordered_map<int, Pipe>& pipes);
void showAllPipes(const unordered_map<int, Pipe>& pipes);
void batchEditPipes(unordered_map<int, Pipe>& pipes);

