#include "Scheduling.h"

Scheduling* Scheduling::getInstance() {
	return instance;
}

Scheduling* Scheduling::instance = new Scheduling();

int Scheduling::timer = 0;

bool compare(const Elevator* a, const Elevator* b) {
	return a->getInsider().size() == b->getInsider().size()
		? abs(a->getCurrentFloor() - cmpTarget) < abs(b->getCurrentFloor() - cmpTarget) 
		: a->getInsider().size() < b->getInsider().size();
}

void Scheduling::schedule() {
	for (std::vector<Passenger*>::iterator pIt = passengers.begin(); pIt != passengers.end(); pIt++) {
		if ((*pIt)->assigned()) {
			continue;
		}
		if ((*pIt)->getRequestTime() <= timer) {
			cmpTarget = (*pIt)->getInitialFloor();
			std::sort(elevators.begin(), elevators.end(), compare);
			for (std::vector<Elevator*>::iterator eIt = elevators.begin(); eIt != elevators.end(); eIt++) {
				if ((*eIt)->availableInFloor((*pIt)->getInitialFloor()) && (*eIt)->availableInFloor((*pIt)->getTerminalFloor())) {
					(*eIt)->pushPassenger(*pIt);
					break;
				}
			}
		}
		else {
			break; // 保证请求时刻单调不减
		}
	}
}

Indicator Scheduling::decisionMaking(const Elevator* elevator) {
	const int maxFloor = elevator->getMaxFloor();
	const int currentFloor = elevator->getCurrentFloor();
	const std::vector<Passenger*>& passengers = elevator->getInsider();

	int dest_num[3]{ 0 }, dest_time[3]{ 0 }; // 0 - UP, 1 - DOWN, 2 - STOP, 统计三类行动的人数和耗时
	int up_to_floor = -1, down_to_floor = maxFloor;

	for (std::vector<Passenger*>::const_iterator it = passengers.begin(); it != passengers.end(); it++) {
		const int initialFloor = (*it)->getInitialFloor();
		const int terminalFloor = (*it)->getTerminalFloor();
		const int* tmp = nullptr;
		if (!(*it)->arrived()) {
			if ((*it)->inside()) {
				tmp = &terminalFloor;
			}
			else if ((*it)->getRequestTime() <= timer) {
				tmp = &initialFloor;
			}

			if (tmp != nullptr) {
				up_to_floor = std::max(up_to_floor, *tmp);
				down_to_floor = std::min(down_to_floor, *tmp);

				if (*tmp > currentFloor) {
					dest_num[UP]++;
				}
				else if (*tmp < currentFloor) {
					dest_num[DOWN]++;
				}
				else {
					dest_num[STOP]++;
				}
			}
		}
	}

	for (std::vector<Passenger*>::const_iterator it = passengers.begin(); it != passengers.end(); it++) {
		const int initialFloor = (*it)->getInitialFloor();
		const int terminalFloor = (*it)->getTerminalFloor();

		if (!(*it)->arrived()) {
			if (dest_num[UP]) {
				if ((*it)->inside()) {
					dest_time[UP] += abs(up_to_floor - currentFloor) + abs(up_to_floor - terminalFloor);
					if (terminalFloor != up_to_floor) {
						dest_time[UP]++;
					}
				}
				else {
					dest_time[UP] += abs(up_to_floor - currentFloor) + abs(up_to_floor - initialFloor) + abs(terminalFloor - initialFloor);
					if (terminalFloor != up_to_floor) {
						dest_time[UP]++;
					}
				}
			}

			if (dest_num[DOWN]) {
				if ((*it)->inside()) {
					dest_time[DOWN] += abs(down_to_floor - currentFloor) + abs(down_to_floor - terminalFloor);
					if (terminalFloor != down_to_floor) {
						dest_time[DOWN]++;
					}
				}
				else {
					dest_time[DOWN] += abs(down_to_floor - currentFloor) + abs(down_to_floor - initialFloor) + abs(terminalFloor - initialFloor);
					if (terminalFloor != down_to_floor) {
						dest_time[DOWN]++;
					}
				}
			}
		}
	}
	if (!dest_num[UP] && !dest_num[DOWN] && !dest_num[STOP]) {
		return NONE;
	}
	else if (!dest_num[UP] && !dest_num[DOWN]) {
		return STOP;
	}
	else if (!dest_num[STOP] && !dest_num[DOWN]) {
		return UP;
	}
	else if (!dest_num[UP] && !dest_num[STOP]) {
		return DOWN;
	}
	else if (!dest_num[UP]) {
		return STOP;
	}
	else if (!dest_num[DOWN]) {
		return STOP;
	}
	else if (!dest_num[STOP]) {
		Indicator status = elevator->getStatus();
		if (status == NONE || status == STOP) {
			if (dest_time[UP] < dest_time[DOWN]) {
				return UP;
			}
			else {
				return DOWN;
			}
		}
		else {
			return status;
		}
	}
	else {
		return STOP;
	}
}

void Scheduling::execute() {
	for (Elevator* elevator : elevators) {
		switch (decisionMaking(elevator)) {
		case STOP:
			elevator->stop();
			elevator->pushOperation(timer);
			//elevator->outputStatus(timer);
			break;
		case UP:
			elevator->up();
			//elevator->outputStatus(timer);
			break;
		case DOWN:
			elevator->down();
			//elevator->outputStatus(timer);
			break;
		default:
			elevator->idle();
			break;
		}
	}
	timer++;
}

void Scheduling::clear() {
	clearElevator();
	clearPassenger();
}

void Scheduling::clearElevator() {
	for (std::vector<Elevator*>::iterator it = elevators.begin(); it != elevators.end(); it++) {
		delete *it;
	}
	elevators.clear();
}

void Scheduling::clearPassenger() {
	for (std::vector<Passenger*>::iterator it = passengers.begin(); it != passengers.end(); it++) {
		delete *it;
	}
	passengers.clear();
}

void Scheduling::addElevator(Elevator* ele) {
	this->elevators.push_back(ele);
}

void Scheduling::addPassenger(Passenger* pass) {
	this->passengers.push_back(pass);
}

bool Scheduling::allArrived() const {
	return getArrivalNumber() == passengers.size();
}

int Scheduling::getArrivalNumber() const {
	int arrival = 0;
	for (std::vector<Elevator*>::const_iterator it = elevators.begin(); it != elevators.end(); it++) {
		arrival += (*it)->getArrivalNumber();
	}
	return arrival;
}