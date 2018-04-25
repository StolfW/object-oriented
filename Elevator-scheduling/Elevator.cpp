#include "Elevator.h"

void Elevator::goToFloor(int floor) {
	for (int i = 0; i < int(passengers.size()); i++) {
		Passenger& p = passengers[i];
		if (!p.isAchieved) {
			if (timer >= p.requestTime) {
				p.waitingTime += abs(floor - currentFloor);
			}
		}
	}
	timer += abs(floor - currentFloor);
	currentFloor = floor;
}

void Elevator::stop() {
	destinationQueue.push(std::make_pair(timer, currentFloor));

	for (size_t i = 0; i < int(passengers.size()); i++) {
		Passenger& p = passengers[i];
		if (!p.isAchieved) {
			if (p.isInside) { // 判断乘客是否在电梯内
				if (p.destination == currentFloor) { // 判断是否下电梯
					p.isAchieved = true;
					achievedPassenger++;
				}
				else {
					p.waitingTime++;
				}
			}
			else {
				if (timer >= p.requestTime) {
					if (p.initialFloor == currentFloor) { // 判断是否上电梯
						p.isInside = true;
					}
					p.waitingTime++;
				}
			}
		}
	}
	timer++;
}

void Elevator::Execute(Indicator indicator) {
	if (indicator == UP) {
		goToFloor(currentFloor + 1);
	}
	else if (indicator == DOWN) {
		goToFloor(currentFloor - 1);
	}
	else if (indicator == STOP){
		stop();
	}
	else {
		timer++;
	}
}

std::ostream  &operator<< (std::ostream &os, Elevator &ele)
{
	while (ele.destinationQueue.size()) {
		std::pair<int, int> procedure = ele.destinationQueue.front();
		ele.destinationQueue.pop();
		os << procedure.first << ' ' << procedure.second << std::endl;
	}
	return os;
}