#include "Passenger.h"

int Passenger::getRequestTime() const {
	return this->requestTime;
}

int Passenger::getInitialFloor() const {
	return this->initialFloor;
}

int Passenger::getTerminalFloor() const {
	return this->terminalFloor;
}

bool Passenger::inside() const {
	return this->isInside;
}

bool Passenger::arrived() const {
	return this->isArrived;
}

bool Passenger::assigned() const {
	return this->isAssigned;
}

void Passenger::setInside() {
	this->isInside = true;
}

void Passenger::setArrived() {
	this->isArrived = true;
}

void Passenger::setAssigned() {
	this->isAssigned = true;
}

std::istream  &operator>> (std::istream &is, Passenger &pass) {
	is >> pass.requestTime >> pass.initialFloor >> pass.terminalFloor;
	if (!is) {
		pass = Passenger();
	}
	return is;
}