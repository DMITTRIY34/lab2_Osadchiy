#include "GasNetwork.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>
#include "Connection.h"
#include <queue>
#include <stack>

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
		cout << "Диаметр " << diameter << " не поддерживается! Используйте: 500, 700, 1000, 1400 мм" << endl;
		return -1;
	}

	for (const auto& item : pipes) {
		const Pipe& pipe = item.second;
		if (pipe.getDiameter() == diameter && !isPipeConnected(pipe.getId()) && !pipe.isInRepair()) {
			cout << "Выбрали трубу с id = " << pipe.getId() << endl;
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
	vector<int> res;
	
	if (connections.empty()) {
		cout << "В сети нет соединений!" << endl;
		for (const auto& ks : kss) {
			res.push_back(ks.first);
		}
		return res;
	}

	// Строим списки смежности и считаем полустепени захода
	unordered_map<int, vector<int>> adjList;
	unordered_map<int, int> inDegree;

	// Инициализируем наши словари для всех КС
	for (const auto& ksPair : kss) {
		int ksId = ksPair.first;
		adjList[ksId] = vector<int>();
		inDegree[ksId] = 0;
	}

	// Заполнение графа из соединений
	for (const auto& connectionPair : connections) {
		const Connection& conn = connectionPair.second;
		int start = conn.getStartKS();
		int end = conn.getEndKS();

		// Добавляем направленное ребро start -> end
		adjList[start].push_back(end);
		inDegree[end]++;
	}

	// Алгоритм Кана (топологическая сортировка)
	queue<int> q;

	// Находим все вершины с нулевой полустепенью захода
	for (const auto& degreePair : inDegree) {
		if (degreePair.second == 0) {
			q.push(degreePair.first);
		}
	}

	// Обрабатываем вершины
	while (!q.empty()) {
		int current = q.front(); // фронт - получаем без удаления элемент, поп - удаляем первый в очереди, пуш - в конец добавляем
		q.pop();
		res.push_back(current);

		// Уменьшаем полустепень захода для всех соседей
		for (int neighbor : adjList[current]) {
			inDegree[neighbor]--;
			if (inDegree[neighbor] == 0) {
				q.push(neighbor);
			}
		}
	}
	// Проверка на циклы
	if (res.size() != kss.size()) {
		cout << "Обнаружен цикл в газотранспортной сети! Топологическая сортировка невозможна." << endl;
		return vector<int>(); // Возвращаем пустой вектор
	}

	return res;
}

void GasNetwork::showTopologicalOrder(const unordered_map<int, KS>& kss) const {
	cout << "=== ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА ГАЗОТРАНСПОРТНОЙ СЕТИ ===" << endl;

	vector<int> order = topologicalSort(kss);

	if (order.empty()) {
		cout << "Невозможно выполнить топологическую сортировку из-за циклов в сети." << endl;
		return;
	}

	cout << "КС в порядке топологической сортировки (от источников к стокам):" << endl;

	for (size_t i = 0; i < order.size(); ++i) {
		auto it = kss.find(order[i]);
		if (it != kss.end()) {
			cout << i + 1 << ". " << it->second.getName() << " (ID: " << order[i] << ")";

			// Показываем информацию о соединениях для этой КС
			bool hasOutgoing = false;
			bool hasIncoming = false;

			for (const auto& conn : connections) {
				if (conn.second.getStartKS() == order[i]) {
					hasOutgoing = true;
				}
				if (conn.second.getEndKS() == order[i]) {
					hasIncoming = true;
				}
			}

			if (!hasIncoming && hasOutgoing) {
				cout << " [ИСТОЧНИК]";
			}
			else if (hasIncoming && !hasOutgoing) {
				cout << " [СТОК]";
			}
			else if (!hasIncoming && !hasOutgoing) {
				cout << " [ИЗОЛИРОВАНА]";
			}

			cout << endl;
		}
	}

	// Дополнительная информация о сети
	cout << "--- Статистика сети ---" << endl;
	cout << "Всего КС: " << kss.size() << endl;
	cout << "Всего соединений: " << connections.size() << endl;

	// Находим источники и стоки
	vector<int> sources, sinks;
	for (const auto& ksPair : kss) {
		int ksId = ksPair.first;
		bool hasIncoming = false;
		bool hasOutgoing = false;

		for (const auto& conn : connections) {
			if (conn.second.getStartKS() == ksId) hasOutgoing = true;
			if (conn.second.getEndKS() == ksId) hasIncoming = true;
		}

		if (!hasIncoming && hasOutgoing) sources.push_back(ksId);
		if (hasIncoming && !hasOutgoing) sinks.push_back(ksId);
	}

	if (!sources.empty()) {
		cout << "Источники (КС без входящих соединений): ";
		for (int src : sources) cout << src << " ";
		cout << endl;
	}

	if (!sinks.empty()) {
		cout << "Стоки (КС без исходящих соединений): ";
		for (int sink : sinks) cout << sink << " ";
		cout << endl;
	}
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
bool GasNetwork::disconnectAll() {
	if (connections.empty()) {
		cout << "В сети нет соединений для удаления!" << endl;
		return false;
	}

	int connectionCount = connections.size();

	cout << "=== УДАЛЕНИЕ ВСЕХ СОЕДИНЕНИЙ ===" << endl;
	cout << "Количество соединений для удаления: " << connectionCount << endl;

	// Запрашиваем подтверждение
	cout << "Вы уверены, что хотите удалить ВСЕ " << connectionCount << " соединений?" << endl;
	cout << "Это действие нельзя отменить! (1-да, 0-нет): ";
	int confirm = GetNumber(0, 1);

	if (confirm == 1) {
		connections.clear();
		cout << "Все " << connectionCount << " соединений успешно удалены!" << endl;
		cout << "Сеть очищена." << endl;
		return true;
	}
	else {
		cout << "Удаление отменено. Соединения сохранены." << endl;
		return false;
	}
}