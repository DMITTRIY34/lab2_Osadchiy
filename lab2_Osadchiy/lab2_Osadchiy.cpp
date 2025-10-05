#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "Ks.h"
#include "Utils.h"

using namespace std;


bool isNumber(const string& s) {
    if (s.empty()) return false;

    size_t start = 0;
    if (s[0] == '-') {
        start = 1;
        if (s.length() == 1) return false;
    }

    for (size_t i = start; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

int inputInt() {
    string numIn;
    int num;
    while (true) {
        cin >> numIn;
        if (isNumber(numIn)) {
            num = stoi(numIn);
            if ((cin.fail() or num <= 0)) {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "Ошибка: Введено некорректное значение. Попробуйте снова" << endl;
                cout << "Ввод: ";
            }
            else {
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                return num;
            }
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Ошибка: Введено некорректное значение. Попробуйте снова" << endl;
            cout << "Ввод: ";
        }

    }
}

float inputFloat() {
    float num;
    while (true) {
        cin >> num;
        if (cin.fail() or num <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Ошибка: Введено некорректное значение. Попробуйте снова" << endl;
            cout << "Ввод: ";
        }
        else {
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            return num;
        }
    }
}

void addPipe(Pipe& P) {
    cout << "Введите название трубы: ";
    getline(cin, P.name, '\n');
    cout << "Введите длину трубы (в км): ";
    P.length = inputFloat();
    cout << "Введите диаметр трубы (в мм): ";
    P.diameter = inputInt();
    cout << "Труба в ремонте? (1 если да и 0 если не в ремонте): ";

    int repair;
    while (true) {
        cin >> repair;
        if (cin.fail() or (repair != 0 and repair != 1)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Вы ввели некорректные данные. Попробуйте ещё раз!" << endl;
            cout << "Труба в ремонте? (1 если да и 0 если не в ремонте): ";
        }
        else {
            P.inRepair = repair;
            break;
        }
    }
}

void addKs(Ks& K) {
    cout << "Введите название КС: ";
    getline(cin, K.name, '\n');
    cout << "Введите количество цехов: ";
    K.countWorkshop = inputInt();
    cout << "Введите количество цехов в работе: ";
    K.countWorkshopInWork = inputInt();
    while (true) {
        if (K.countWorkshopInWork > K.countWorkshop) {
            cout << "Количество цехов в работе не может быть больше количества цехов. Попробуйте ещё раз!" << endl;
            K.countWorkshopInWork = inputInt();
        }
        else break;
    }
    cout << "Введите класс станции (некий показатель, обобщающий различные специфические характеристики): ";
    cin >> K.other;
}

void showPipe(Pipe& pipe) {
    cout << "------------------------------" << endl;
    cout << "Название трубы: " << pipe.name << endl;
    cout << "Длина трубы: " << pipe.length << " км." << endl;
    cout << "Диаметер трубы: " << pipe.diameter << " мм." << endl;
    cout << "Труба в ремонте: " << (pipe.inRepair ? "Да" : "Нет") << endl;
    cout << "------------------------------" << endl;
}

void showKs(Ks& ks) {
    cout << "------------------------------" << endl;
    cout << "Название КС: " << ks.name << endl;
    cout << "Количество цехов: " << ks.countWorkshop << endl;
    cout << "Количество цехов в работе: " << ks.countWorkshopInWork << endl;
    cout << "Класс станции: " << ks.other << endl;
    cout << "------------------------------" << endl;
}

void showAll(Pipe& pipe, Ks& ks) {
    int choice;

    cout << "Выберите что хотите просмотреть(1 - труба, 2 - кс, 3 - все): ";
    choice = inputInt();

    while (true) {
        if (choice > 3) {
            cout << "Попробуйте выбрать ещё раз: ";
            choice = inputInt();
        }
        else break;
    }
    switch (choice) {
    case 1:
    {
        if (pipe.diameter > 0) {
            showPipe(pipe);
        }
        else {
            cout << "Труба ещё не создана" << endl;
        }
        break;
    }
    case 2:
    {
        if (ks.countWorkshop > 0) {
            showKs(ks);
        }
        else {
            cout << "КС ещё не создана" << endl;
        }
        break;
    }
    case 3:
    {
        if (pipe.diameter > 0 and ks.countWorkshop > 0) {
            showPipe(pipe);
            showKs(ks);
        }
        else {
            cout << "У вас отстутсвует труба или КС. Попробуйте просмотреть что-то одно" << endl;
        }
        break;
    }
    }
}

void changeStatusRepair(Pipe& pipe) {
    pipe.inRepair = !pipe.inRepair;
    cout << "Статус ремонта изменён, теперь труба " << (pipe.inRepair ? "в ремонте!\n" : "работает!\n") << endl;
}

void startWorkshop(Ks& ks) {
    int count;
    cout << "Введите количество цехов для запуска. Можно запустить до " << ks.countWorkshop - ks.countWorkshopInWork << " цехов: ";
    count = inputInt();
    while (true) {
        if (count > (ks.countWorkshop - ks.countWorkshopInWork)) {
            cout << "Вы не можете запустить столько цехов. Попробуйте ещё раз!";
            count = inputInt();
        }
        else {
            ks.countWorkshopInWork += count;
            cout << "Вы успешно запустили ещё " << count << " цехов в работу! Всего работает " << ks.countWorkshopInWork << " цехов!" << endl;
            break;
        }
    }
}
void stopWorkshop(Ks& ks) {
    int count;
    cout << "Введите количество цехов для остановки. Можно остановить до " << ks.countWorkshopInWork << " цехов: ";
    count = inputInt();
    while (true) {
        if (count > (ks.countWorkshopInWork)) {
            cout << "Вы не можете остановить столько цехов. Попробуйте ещё раз!";
            count = inputInt();
        }
        else {
            ks.countWorkshopInWork -= count;
            cout << "Вы успешно остановили ещё " << count << " цехов! Всего работает " << ks.countWorkshopInWork << " цехов!" << endl;
            break;
        }
    }
}

void changePipe(Pipe& pipe) {
    int number;
    while (true) {
        cout << "Выберите что хотите изменить в трубе\n" << endl;
        cout << "1. Изменить название" << endl;
        cout << "2. Изменить длину" << endl;
        cout << "3. Изменить диаметр" << endl;
        cout << "4. Изменить статус в ремонте" << endl;
        cout << "5. Выйти из меню изменения" << endl;
        cout << "Выберите действие: ";

        number = inputInt();
        cout << endl;
        switch (number) {
        case 1:
        {
            cout << "Введите новое имя: ";
            getline(cin, pipe.name, '\n');
            break;
        }
        case 2:
        {
            float newLen;
            cout << "Введите новую длину: ";
            newLen = inputFloat();
            pipe.length = newLen;
            break;
        }
        case 3:
        {
            int newDiam;
            cout << "Введите новый диаметр: ";
            newDiam = inputInt();
            pipe.diameter = newDiam;
            break;
        }
        case 4:
        {
            changeStatusRepair(pipe);
            break;
        }
        case 5:
        {
            cout << "Выход из изменений!" << endl;
            return;
        }
        }
    }
}

void changeKs(Ks& ks) {
    int number;
    while (true) {
        cout << "Выберите что хотите изменить в КС\n" << endl;
        cout << "1. Изменить название" << endl;
        cout << "2. Изменить количество цехов" << endl;
        cout << "3. Запуск цехов " << endl;
        cout << "4. Остановка цехов" << endl;
        cout << "5. Изменить класс станции" << endl;
        cout << "6. Выйти из меню изменения" << endl;
        cout << "Выберите действие: ";

        number = inputInt();
        cout << endl;
        switch (number) {
        case 1:
        {
            cout << "Введите новое имя: ";
            getline(cin, ks.name, '\n');
            break;
        }
        case 2:
        {
            int newCountWorkshop;
            cout << "Введите новое количество цехов: ";
            newCountWorkshop = inputInt();
            ks.countWorkshop = newCountWorkshop;
            break;
        }
        case 3:
        {
            startWorkshop(ks);
            break;
        }
        case 4:
        {
            stopWorkshop(ks);
            break;
        }
        case 5:
        {
            string newClass;
            cout << "Введите новый класс станции: ";
            cin >> newClass;
            ks.other = newClass;
            break;
        }
        case 6:
        {
            cout << "Выход из изменений!" << endl;
            return;
        }
        }
    }
}

void saveToFile(const Pipe& pipe, const Ks& ks, const string& filename = "file.txt") {
    ofstream file(filename);

    if (file.is_open()) {
        // Сохраняем данные для трубы
        file << "PIPE" << endl;
        file << pipe.name << endl;
        file << pipe.length << endl;
        file << pipe.diameter << endl;
        file << pipe.inRepair << endl;

        // Сохраняем данные КС
        file << "KS" << endl;
        file << ks.name << endl;
        file << ks.countWorkshop << endl;
        file << ks.countWorkshopInWork << endl;
        file << ks.other << endl;

        cout << "Данные были успешно сохранены в файл под названием'" << filename << "'!\n" << endl;
    }
    else {
        cout << "Ошибка в открытии файла для записи!\n" << endl;
    }
    file.close();
}


bool loadFromFile(Pipe& pipe, Ks& ks, const string& filename = "file.txt") {
    ifstream file(filename);

    if (file.is_open()) {
        string line;

        getline(file, line);
        if (line != "PIPE") {
            cout << "Файл был изменён!\n" << endl;
            file.close();
            return false;
        }

        // Читаем данные трубы
        getline(file, pipe.name);
        file >> pipe.length;
        file >> pipe.diameter;
        file >> pipe.inRepair;
        file.ignore(); // пропускаем символ новой строки

        // Проверяем формат файла - КС
        getline(file, line);
        if (line != "KS") {
            cout << "Файл был изменён!\n" << endl;
            file.close();
            return false;
        }

        // Читаем данные КС
        getline(file, ks.name);
        file >> ks.countWorkshop;
        file >> ks.countWorkshopInWork;
        file.ignore(); // пропускаем символ новой строки
        getline(file, ks.other);


        cout << "Данные успешно загружены из файла '" << filename << "'!\n" << endl;
        return true;
    }
    else {
        cout << "Файл '" << filename << "' не найден!\n" << endl;
        return false;
    }
    file.close();
}

void menu(Pipe& pipe, Ks& ks) {
    bool pipe_existence = false;
    bool ks_existence = false;
    int number;
    while (true)
    {
        cout << "1. Добавить трубу" << endl;
        cout << "2. Добавить КС" << endl;
        cout << "3. Просмотр всех объектов" << endl;
        cout << "4. Редактировать трубу" << endl;
        cout << "5. Редактировать КС" << endl;
        cout << "6. Сохранить" << endl;
        cout << "7. Загрузить" << endl;
        cout << "8. Выход" << endl;
        cout << "Выберите действие: ";

        number = inputInt();
        cout << endl;
        switch (number) {
        case 1:
        {
            addPipe(pipe);
            pipe_existence = true;
            cout << endl;
            cout << "Труба '" << pipe.name << "' была успешно добавлена!\n" << endl;
            break;
        }
        case 2:
        {
            addKs(ks);
            ks_existence = true;
            cout << endl;
            cout << "Компрессорная станция '" << ks.name << "' была успешно добавлена!\n" << endl;
            break;
        }
        case 3:
        {
            showAll(pipe, ks);
            break;
        }
        case 4:
        {
            if (pipe_existence) {
                changePipe(pipe);
            }
            else {
                cout << "У вас не создана труба!\n" << endl;
            }
            break;
        }
        case 5:
        {
            if (ks_existence) {
                changeKs(ks);
            }
            else {
                cout << "У вас не создана КС!\n" << endl;
            }
            break;
        }
        case 6:
        {
            if (pipe_existence or ks_existence) {
                saveToFile(pipe, ks);
            }
            else {
                cout << "Нет данных для сохранения!\n" << endl;
            }
            break;
        }
        case 7:
        {
            if (loadFromFile(pipe, ks)) {
                pipe_existence = (pipe.diameter > 0);
                ks_existence = (ks.countWorkshop > 0);
                cout << "Данные загружены успешно!\n" << endl;
            }
            break;
        }
        case 8:
        {
            cout << "Выход из программы!\n";
            return;
        }
        default:
            cout << "Попробуйте ввести ещё раз, такого числа нет!\n" << endl;
            break;
        };
    };
};

int main()
{
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Russian");
    Pipe pipe;
    Ks ks;
    menu(pipe, ks);
    return 0;
}
