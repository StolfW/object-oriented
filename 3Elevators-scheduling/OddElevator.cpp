#include "OddElevator.h"

bool OddElevator::availableInFloor(int floor) {
	return floor > 0 && floor <= this->maxFloor && floor & 1;
}

std::string OddElevator::type() const {
	return "OddElevator";
}

void OddElevator::outputPosition(std::ofstream& fout) const {
	fout << "OddElevator\t\t" << this->currentFloor;
}