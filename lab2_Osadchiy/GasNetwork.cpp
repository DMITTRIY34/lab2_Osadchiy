#include "GasNetwork.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include "Connection.h"

using namespace std;

GasNetwork::GasNetwork() : nextConnectionId(0) {}

bool GasNetwork::connectKS(unordered_map<int, Pipe>& pipes, const unordered_map<int, KS>& kss, int startKS, int endKS, int diameter){

	if (kss.find(startKS) == kss.end()) {
		cout << "КС входа с ID " << startKS << " не найдена!" << endl;
		showAvailableKS(kss);
		return false;
	}
	if (kss.find(endKS) == kss.end()) {
		cout << "КС выхода с ID " << endKS << " не найдена!" << endl;
		showAvailableKS(kss);
		return false;
	}
	if (startKS == endKS) {
		cout << "Нельзя соединять КС саму с собой!" << endl;
		return false;
	}

	// Проверяем, нет ли уже соединения между этими КС
	if (connectionExists(startKS, endKS)) {
		cout << "Соединение между КС " << startKS << " и КС " << endKS << " уже существует!" << endl;
		cout << "Нельзя создавать параллельные или обратные соединения!" << endl;
		return false;
	}

	// Проверяем стандартные диаметры
	vector<int> allowedDiameters = { 500, 700, 1000, 1400 };
	bool diameterValid = false;
	for (int d : allowedDiameters) {
		if (d == diameter) {
			diameterValid = true;
			break;
		}
	}

	if (!diameterValid) {
		cout << "Диаметр " << diameter << " не поддерживается! Используйте: 500, 700, 1000, 1400 мм" << endl;
		return false;
	}

	int pipeId = findFreePipeByDiameter(pipes, diameter);

	if (pipeId == -1) {
		cout << "Свободной трубы с диаметром " << diameter << " мм не найдено!" << endl;
		cout << "Пожалуйста создайте такую трубу самостоятельно!" << endl;

		cout << "Хотите создать новую трубу ЭТОГО диаметра? (1-да, 0-нет): ";
		int createNew = GetNumber(0, 1);
		if (createNew == 1) {
			Pipe newPipe;
			cout << "Создание новой трубы диаметром " << diameter << " мм:" << endl;

			cout << "Введите название Трубы: ";
			newPipe.setName(GetName());
			cout << "Введите длину трубы в км: ";
			newPipe.setLength(GetNumber(0.01));
			newPipe.setDiameter(diameter);  // Устанавливаем наш диаметр
			cout << "Труба в ремонте (1 - ДА | 0 - НЕТ): ";
			newPipe.setRepair(GetNumber(0, 1));

			pipes.insert({ newPipe.getId(), newPipe });
			pipeId = newPipe.getId();
			cout << "Новая труба создана! ID: " << pipeId << endl;
		}
		else {
			cout << "Соединение не создано." << endl;
			return false;
		}
	}

	if (isPipeConnected(pipeId)) {
		cout << "Ошибка: труба " << pipeId << " уже используется в другом соединении!" << endl;
		return false;
	}

	Connection newConnection(nextConnectionId++, pipeId, startKS, endKS);
	connections[newConnection.getId()] = newConnection;

	cout << "Соединение создано! ID = " << newConnection.getId() << endl;
	cout << "КС входа " << startKS << " с трубой " << pipeId << " и с КС выхода" << endKS << endl;
	return true;
}

int GasNetwork::findFreePipeByDiameter(const unordered_map<int, Pipe>& pipes, int diameter) const {
	vector<int> allowedDiameters = { 500, 700, 1000, 1400 };
	bool diameterValid = false;
	for (int d : allowedDiameters) {
		if (d == diameter) {
			diameterValid = true;
			break;
		}
	}

	if (!diameterValid) {
		std::cout << "Диаметр " << diameter << " не поддерживается! Используйте: 500, 700, 1000, 1400 мм" << std::endl;
		return -1;
	}

	for (const auto& item : pipes) {
		const Pipe& pipe = item.second;
		if (pipe.getDiameter() == diameter && !isPipeConnected(pipe.getId()) && !pipe.isInRepair()) {
			return pipe.getId();
		}
	}
	return -1;
}

void GasNetwork::showAllConnections() const {
	if (connections.empty()) {
		cout << "Соединения отсутствуют" << endl;
		return;
	}

	cout << "---------------СОЕДИНЕНИЯ---------------" << endl;
	for (const auto& connection : connections) {
		connection.second.show();
	}
}

bool GasNetwork::disconnect(int connectionId) {
	auto it = connections.find(connectionId);
	if (it != connections.end()) {
		connections.erase(it);
		cout << "Соединение " << connectionId << " удалено!" << endl;
		return true;
	}

	cout << "Соединение с ID = " << connectionId << " не найдено!" << endl;
	return false;
}

bool GasNetwork::isKSConnected(int ksId) const {
	for (const auto& connection : connections) {
		const Connection& conn = connection.second;
		if (conn.getStartKS() == ksId || conn.getEndKS() == ksId) {
			return true;
		}
	}
	return false;
}

bool GasNetwork::isPipeConnected(int pipeId) const {
	for (const auto& connection : connections) {
		if (connection.second.getPipeId() == pipeId) {
			return true;
		}
	}
	return false;
}

vector<int> GasNetwork::topologicalSort(const unordered_map<int, KS>& kss) const {
	vector<int> sort1 = { 1,2,3 };
	return sort1;
}

void GasNetwork::showTopologicalOrder(const unordered_map<int, KS>& kss) const {

}

void GasNetwork::addConnection(const Connection& connection) {
	connections[connection.getId()] = connection;
	if (connection.getId() >= nextConnectionId) {
		nextConnectionId = connection.getId() + 1;
	}
}

void GasNetwork::clear() {
	connections.clear();
	nextConnectionId = 1;
}

bool GasNetwork::connectionExists(int startKS, int endKS) const {
	for (const auto& connection : connections) {
		const Connection& conn = connection.second;
		if ((conn.getStartKS() == startKS && conn.getEndKS() == endKS) or (conn.getStartKS() == endKS && conn.getEndKS() == startKS)) {
			return true;
		}
	}
	return false;
}