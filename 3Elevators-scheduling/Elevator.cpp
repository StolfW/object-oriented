#include "Elevator.h"

void Elevator::up() {
	status = UP;
	currentFloor++;
}

void Elevator::down() {
	status = DOWN;
	currentFloor--;
}

void Elevator::stop() {
	status = STOP;
	for (std::vector<Passenger*>::iterator it = insider.begin(); it != insider.end(); ) {
		if ((*it)->getInitialFloor() == currentFloor) {
			(*it)->setInside();
			it++;
		}
		else if ((*it)->getTerminalFloor() == currentFloor) { // 是否抵达目的地
			(*it)->setArrived();
			arrivalNumber++;
			it = insider.erase(it);
		}
		else {
			it++;
		}
	}
}

void Elevator::idle() {
	status = NONE;
}

void Elevator::pushPassenger(Passenger* pass) {
	this->insider.push_back(pass);
	pass->setAssigned();
}

void Elevator::pushOperation(const int& timer) {
	this->operations.push_back(std::make_pair(timer, currentFloor));
}

int Elevator::getMaxFloor() const {
	return this->maxFloor;
}

int Elevator::getCurrentFloor() const {
	return this->currentFloor;
}

int Elevator::getArrivalNumber() const {
	return this->arrivalNumber;
}

const std::vector<Passenger*>& Elevator::getInsider() const {
	return this->insider;
}

Indicator Elevator::getStatus() const {
	return this->status;
}

bool Elevator::availableInFloor(int floor) {
	return floor > 0 && floor <= maxFloor;
}

std::string Elevator::type() const {
	return "Elevator";
}

void Elevator::outputPosition(const int& timer) const {
	std::cout << std::endl;
	std::cout << timer << " : Elevator at Floor " << currentFloor;
	std::cout << std::endl;
}

std::ostream &operator<< (std::ostream &os, const Elevator& ele) {
	for (std::vector<std::pair<int, int>>::const_iterator it = ele.operations.begin(); it != ele.operations.end(); it++) {
		if (it == ele.operations.begin() && it->second == 1) {
			continue;
		}
		os << it->first << ' ' << it->second << std::endl;
	}
	return os;
}