#include "EvenElevator.h"

bool EvenElevator::availableInFloor(int floor) {
	return floor > 0 && floor <= this->maxFloor && (floor == 1 || !(floor & 1));
}

std::string EvenElevator::type() const {
	return "EvenElevator";
}

void EvenElevator::outputPosition(std::ofstream& fout) const {
	fout << "EvenElevator\t\t" << this->currentFloor;
}