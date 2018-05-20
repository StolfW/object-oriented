#include "Scheduling.h"

Scheduling* Scheduling::getInstance() {
	return instance;
}

Scheduling* Scheduling::instance = new Scheduling();

int Scheduling::timer = 0;

bool assignmentPriority(const Elevator* a, const Elevator* b) {
	const int& sizeA = a->getInsider().size();
	const int& sizeB = b->getInsider().size();
	const int& apartA = abs(initialTarget - a->getCurrentFloor());
	const int& apartB = abs(initialTarget - b->getCurrentFloor());
	if (sizeA && !sizeB) {
		return apartA * 2 < apartB;
	}
	if (!sizeA && sizeB) {
		return apartB * 2 >= apartA;
	}
	return apartA && apartB ? sizeA < sizeB : apartA < apartB;

	//return abs(a->getCurrentFloor() - initialTarget) < abs(b->getCurrentFloor() - initialTarget);

	//return a->getInsider().size() < b->getInsider().size();

	/*return a->getInsider().size() && b->getInsider().size()
		? abs(a->getCurrentFloor() - initialTarget) < abs(b->getCurrentFloor() - initialTarget) 
		: a->getInsider().size() < b->getInsider().size();*/

	/*return abs(a->getCurrentFloor() - initialTarget) && abs(b->getCurrentFloor() - initialTarget)
		? a->getInsider().size() < b->getInsider().size()
		: abs(a->getCurrentFloor() - initialTarget) < abs(b->getCurrentFloor() - initialTarget);*/
}

void Scheduling::assignment() {
	for (std::vector<Passenger*>::iterator pIt = this->passengers.begin(); pIt != this->passengers.end(); ) {
		if ((*pIt)->assigned()) {
			if ((*pIt)->arrived()) {
				this->arrivals.push_back(*pIt);
				pIt = this->passengers.erase(pIt);
				if (pIt == this->passengers.end()) {
					break;
				}
				continue;
			}
			pIt++;
			continue;
		}
		if ((*pIt)->getRequestTime() <= timer) {
			initialTarget = (*pIt)->getInitialFloor();
			terminalTarget = (*pIt)->getTerminalFloor();
			std::sort(this->elevators.begin(), this->elevators.end(), assignmentPriority);
			for (std::vector<Elevator*>::iterator eIt = this->elevators.begin(); eIt != this->elevators.end(); eIt++) {
				if ((*eIt)->availableInFloor((*pIt)->getInitialFloor()) && (*eIt)->availableInFloor((*pIt)->getTerminalFloor())) {
					(*eIt)->pushPassenger(*pIt);
					break;
				}
			}
			pIt++;
		}
		else {
			break; // 保证请求时刻单调不减
		}
	}
}

void Scheduling::execute() {
	for (Elevator* elevator : this->elevators) {
		switch (this->schedulingMaking(elevator)) {
		case STOP:
			elevator->stop();
			elevator->pushOperation(timer);
			break;
		case UP:
			elevator->up();
			break;
		case DOWN:
			elevator->down();
			break;
		default:
			elevator->idle();
			break;
		}
	}
	timer++;
}

Indicator Scheduling::schedulingMaking(const Elevator* elevator) {
	const int currentFloor = elevator->getCurrentFloor();
	const int maxFloor = elevator->getMaxFloor();
	const std::vector<Passenger*>& passengers = elevator->getInsider();

	int dest[3] = { 0 }; // 0 - UP, 1 - DOWN, 2 - STOP, 统计三类行动的人数
	int upToMax = 0, downToMin = maxFloor + 1;

	for (Passenger* passenger : passengers) {
		int tmpDest = 0;
		if (passenger->inside()) {
			tmpDest = passenger->getTerminalFloor();
		}
		else {
			tmpDest = passenger->getInitialFloor();
		}
		if (tmpDest) {
			upToMax = std::max(upToMax, tmpDest);
			downToMin = std::min(downToMin, tmpDest);
			if (tmpDest > currentFloor) {
				dest[UP]++;
			}
			else if (tmpDest < currentFloor) {
				dest[DOWN]++;
			}
			else {
				dest[STOP]++;
			}
		}
	}
	if (!dest[UP] && !dest[DOWN] && !dest[STOP]) {
		return NONE;
	}
	else if (!dest[STOP] && !dest[DOWN]) {
		return UP;
	}
	else if (!dest[UP] && !dest[STOP]) {
		return DOWN;
	}
	else if (!dest[UP] && !dest[DOWN]) {
		return STOP;
	}
	else if (!dest[UP]) {
		return STOP;
	}
	else if (!dest[DOWN]) {
		return STOP;
	}
	else if (!dest[STOP]) {
		if (upToMax - currentFloor < currentFloor - downToMin) {
			return UP;
		}
		else {
			return DOWN;
		}
		/*Indicator status = elevator->getStatus();
		if (status == NONE) {
			return UP;
		}
		else {
			return status;
		}*/
	}
	else {
		return STOP;
	}
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
	for (std::vector<Passenger*>::iterator it = this->arrivals.begin(); it != this->arrivals.end(); it++) {
		delete *it;
	}
	this->passengers.clear();
	this->arrivals.clear();
}

void Scheduling::addElevator(Elevator* ele) {
	this->elevators.push_back(ele);
}

void Scheduling::addPassenger(Passenger* pass) {
	this->passengers.push_back(pass);
}

bool Scheduling::allArrived() const {
	//std::cout << this->getArrivalNumber() << std::endl;
	return !this->passengers.size();
}

int Scheduling::getArrivalNumber() const {
	return this->arrivals.size();
}

int Scheduling::getPassengerNumber() const {
	return this->passengers.size() + this->arrivals.size();
}