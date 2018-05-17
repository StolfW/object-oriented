#include "Scheduling.h"

Scheduling* Scheduling::getInstance() {
	return instance;
}

Scheduling* Scheduling::instance = new Scheduling();

int Scheduling::timer = 0;

bool compare(const Elevator* a, const Elevator* b) {
	/*return a->getInsider().size() && b->getInsider().size()
		? abs(a->getCurrentFloor() - cmpTarget) < abs(b->getCurrentFloor() - cmpTarget) 
		: a->getInsider().size() < b->getInsider().size();*/
	return a->getInsider().size() < b->getInsider().size();
}

void Scheduling::schedule() {
	for (std::vector<Passenger*>::iterator pIt = this->passengers.begin(); pIt != this->passengers.end(); pIt++) {
		if ((*pIt)->assigned()) {
			if ((*pIt)->arrived()) {
				this->arrivals.push_back(*pIt);
				pIt = this->passengers.erase(pIt);
				if (pIt == this->passengers.end()) {
					break;
				}
			}
			else {
				continue;
			}
		}
		if ((*pIt)->getRequestTime() <= timer) {
			//cmpTarget = (*pIt)->getInitialFloor();
			std::sort(this->elevators.begin(), this->elevators.end(), compare);
			for (std::vector<Elevator*>::iterator eIt = this->elevators.begin(); eIt != this->elevators.end(); eIt++) {
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
	const int currentFloor = elevator->getCurrentFloor();
	const std::vector<Passenger*>& passengers = elevator->getInsider();

	int dest[3] = { 0 }; // 0 - UP, 1 - DOWN, 2 - STOP, 统计三类行动的人数和耗时

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
				if (*tmp > currentFloor) {
					dest[UP]++;
				}
				else if (*tmp < currentFloor) {
					dest[DOWN]++;
				}
				else {
					dest[STOP]++;
				}
			}
		}
	}
	if (!dest[UP] && !dest[DOWN] && !dest[STOP]) {
		return NONE;
	}
	else if (!dest[UP] && !dest[DOWN]) {
		return STOP;
	}
	else if (!dest[STOP] && !dest[DOWN]) {
		return UP;
	}
	else if (!dest[UP] && !dest[STOP]) {
		return DOWN;
	}
	else if (!dest[UP]) {
		return STOP;
	}
	else if (!dest[DOWN]) {
		return STOP;
	}
	else if (!dest[STOP]) {
		Indicator status = elevator->getStatus();
		if (status == NONE) {
			if (dest[UP]) {
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
	for (Elevator* elevator : this->elevators) {
		switch (this->decisionMaking(elevator)) {
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
	this->clearElevator();
	this->clearPassenger();
}

void Scheduling::clearElevator() {
	for (std::vector<Elevator*>::iterator it = this->elevators.begin(); it != this->elevators.end(); it++) {
		delete *it;
	}
	this->elevators.clear();
}

void Scheduling::clearPassenger() {
	for (std::vector<Passenger*>::iterator it = this->passengers.begin(); it != this->passengers.end(); it++) {
		delete *it;
	}
	this->passengers.clear();
}

void Scheduling::addElevator(Elevator* ele) {
	this->elevators.push_back(ele);
}

void Scheduling::addPassenger(Passenger* pass) {
	this->passengers.push_back(pass);
}

bool Scheduling::allArrived() const {
	//std::cout << getArrivalNumber() << std::endl;
	return !this->passengers.size();
}

int Scheduling::getArrivalNumber() const {
	return this->arrivals.size();
}