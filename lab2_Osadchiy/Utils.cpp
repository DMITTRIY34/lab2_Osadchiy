#include "utils.h"
#include "Pipe.h"
#include "KS.h"
#include <unordered_map>
#include <fstream>


using namespace std;


//void saveToFile(const std::vector<Pipe>& pipes, const std::vector<KS>& kss) {
//    cout << "Введите имя файла для сохранения: ";
//    std::string filename;
//    std::getline(cin, filename);
//
//    std::ofstream file(filename);
//    if (!file.is_open()) {
//        cout << "Ошибка открытия файла!" << endl;
//        return;
//    }
//
//    // Сохраняем трубы
//    file << pipes.size() << endl;
//    for (const auto& pipe : pipes) {
//        file << pipe.id << endl;
//        file << pipe.name << endl;
//        file << pipe.length << endl;
//        file << pipe.diameter << endl;
//        file << pipe.inRepair << endl;
//    }
//
//    // Сохраняем КС
//    file << kss.size() << endl;
//    for (const auto& ks : kss) {
//        file << ks.id << endl;
//        file << ks.name << endl;
//        file << ks.countWorkshop << endl;
//        file << ks.countWorkshopInWork << endl;
//    }
//
//    file.close();
//    cout << "Данные сохранены в файл: " << filename << endl;
//}
//
//void loadFromFile(std::vector<Pipe>& pipes, std::vector<KS>& kss) {
//    cout << "Введите имя файла для загрузки: ";
//    std::string filename;
//    std::getline(cin, filename);
//
//    std::ifstream file(filename);
//    if (!file.is_open()) {
//        cout << "Ошибка открытия файла!" << endl;
//        return;
//    }
//
//    // Очищаем текущие данные
//    pipes.clear();
//    kss.clear();
//
//    // Загружаем трубы
//    int pipeCount;
//    file >> pipeCount;
//    file.ignore();
//
//    for (int i = 0; i < pipeCount; i++) {
//        Pipe pipe;
//        file >> pipe.id;
//        file.ignore();
//        std::getline(file, pipe.name);
//        file >> pipe.length >> pipe.diameter >> pipe.inRepair;
//        file.ignore();
//        pipes.push_back(pipe);
//    }
//
//    // Загружаем КС
//    int ksCount;
//    file >> ksCount;
//    file.ignore();
//
//    for (int i = 0; i < ksCount; i++) {
//        KS ks;
//        file >> ks.id;
//        file.ignore();
//        std::getline(file, ks.name);
//        file >> ks.countWorkshop >> ks.countWorkshopInWork;
//        file.ignore();
//        kss.push_back(ks);
//    }
//
//    file.close();
//
//    // Обновляем nextId
//    int maxPipeId = 0, maxKSId = 0;
//    for (const auto& pipe : pipes) {
//        if (pipe.id > maxPipeId) maxPipeId = pipe.id;
//    }
//    for (const auto& ks : kss) {
//        if (ks.id > maxKSId) maxKSId = ks.id;
//    }
//
//    Pipe::nextId = maxPipeId + 1;
//    KS::nextId = maxKSId + 1;
//
//    cout << "Данные загружены из файла: " << filename << endl;
//}
//
//void deleteObject(std::vector<Pipe>& pipes, std::vector<KS>& kss) {
//    cout << "Введите ID объекта для удаления: ";
//    int id = inputInt();
//
//    // Ищем в трубах
//    for (auto it = pipes.begin(); it != pipes.end(); it++) {
//        if (it->id == id) {
//            pipes.erase(it);
//            cout << "Труба удалена!" << endl;
//            return;
//        }
//    }
//
//    // Ищем в КС
//    for (auto it = kss.begin(); it != kss.end(); it++) {
//        if (it->id == id) {
//            kss.erase(it);
//            cout << "КС удалена!" << endl;
//            return;
//        }
//    }
//
//    cout << "Объект с ID " << id << " не найден!" << endl;
//}
//
//void logAction(const std::string& action) {
//    std::ofstream logfile("log.txt", std::ios::app);
//    if (logfile.is_open()) {
//        logfile << action << endl;
//        logfile.close();
//    }
//    cout << "[LOG] " << action << endl;
//}