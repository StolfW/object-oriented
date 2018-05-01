#include "Strategy.h"

Strategy* Strategy::getInstance() {
	return instance;
}

Strategy* Strategy::instance = new Strategy();

Indicator Strategy::decisionMaking() {
	const int maxFloor = elevator->getMaxFloor();
	const int timer = elevator->getTimer();
	const int currentFloor = elevator->getCurrentFloor();
	const std::vector<Passenger> &passengers = elevator->getPassengers();

	int dest_num[3]{ 0 }, dest_time[3]{ 0 }; // 0 - UP, 1 - DOWN, 2 - STOP, 统计三类行动的人数和耗时
	int up_to_floor = -1, down_to_floor = maxFloor;

	for (int i = 0; i < int(passengers.size()); i++) {
		const Passenger& p = passengers[i];
		const int* tmp = nullptr;
		if (!p.isAchieved) {
			if (p.isInside) {
				tmp = &p.destination;
			}
			else if (p.requestTime <= timer) {
				tmp = &p.initialFloor;
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

	size_t stop_cnt = 0, up_extra = 0, down_extra = 0;
	for (size_t i = 0; i < int(passengers.size()); i++) {
		const Passenger& p = passengers[i];

		if (!p.isAchieved) {
			if (dest_num[UP]) {
				if (p.isInside) {
					dest_time[UP] +=
						abs(up_to_floor - currentFloor)
						+ abs(up_to_floor - p.destination);

					if (p.destination != up_to_floor) {
						dest_time[UP]++;
					}
				}
				else if (p.requestTime <= timer) {
					dest_time[UP] +=
						abs(up_to_floor - currentFloor)
						+ abs(up_to_floor - p.initialFloor)
						+ abs(p.destination - p.initialFloor);

					if (p.destination != up_to_floor) {
						dest_time[UP]++;
					}
				}
			}

			if (dest_num[DOWN]) {
				if (p.isInside) {
					dest_time[DOWN] +=
						abs(down_to_floor - currentFloor)
						+ abs(down_to_floor - p.destination);

					if (p.destination != down_to_floor) {
						dest_time[DOWN]++;
					}
				}
				else if (p.requestTime <= timer) {
					dest_time[DOWN] +=
						abs(down_to_floor - currentFloor)
						+ abs(down_to_floor - p.initialFloor)
						+ abs(p.destination - p.initialFloor);

					if (p.destination != down_to_floor) {
						dest_time[DOWN]++;
					}
				}
			}

			if (dest_num[STOP]) {
				if (p.isInside) {
					if (p.destination != currentFloor) {
						dest_time[STOP]++;
					}
					else {
						stop_cnt++;
					}
				}
				else if (p.requestTime <= timer) {
					if (p.initialFloor != currentFloor) {
						//dest_time[STOP]++;
					}
					else {
						stop_cnt++;
						if (p.destination < currentFloor) {
							up_extra = currentFloor - p.destination;
						}
						else if (p.destination > currentFloor) {
							down_extra = p.destination - currentFloor;
						}
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
		if (dest_time[STOP] * (down_extra + 1) > stop_cnt * ((abs(down_to_floor - currentFloor)) * 2 + 1)) {
			return DOWN;
		}
		else {
			return STOP;
		}
	}
	else if (!dest_num[DOWN]) {
		if (dest_time[STOP] * (up_extra + 1) > stop_cnt * ((abs(up_to_floor - currentFloor)) * 2 + 1)) {
			return UP;
		}
		else {
			return STOP;
		}
	}
	else if (!dest_num[STOP]) {
		if (dest_time[UP] < dest_time[DOWN]) {
			return UP;
		}
		else {
			return DOWN;
		}
	}
	else {
		if (dest_time[UP] < dest_time[DOWN]) {
			if (dest_time[STOP] * (up_extra + 1) > stop_cnt * ((abs(up_to_floor - currentFloor) * 2 + 1))) {
				return UP;
			}
			else {
				return STOP;
			}
		}
		else {
			if (dest_time[STOP] * (down_extra + 1) > stop_cnt * ((abs(down_to_floor - currentFloor) * 2 + 1))) {
				return DOWN;
			}
			else {
				return STOP;
			}
		}
	}
}

void Strategy::setElevator(const Elevator* ele) {
	this->elevator = ele;
}