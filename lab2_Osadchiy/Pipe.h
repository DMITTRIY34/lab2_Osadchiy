#pragma once
#pragma once
#include <iostream>
#include <string>

class Pipe {
public:
    int id;
    std::string name;
    double length;
    int diameter;
    bool inRepair;

    static int nextId;

    Pipe();
    void show() const;
};

// Функции для работы с трубами
void addPipe(std::vector<Pipe>& pipes);
void showAllPipes(const std::vector<Pipe>& pipes);
void searchPipes(const std::vector<Pipe>& pipes);
void batchEditPipes(std::vector<Pipe>& pipes);

