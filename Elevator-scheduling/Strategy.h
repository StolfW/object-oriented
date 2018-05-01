#pragma once
#include "Elevator.h"
#include <vector>
#include <algorithm>

class Strategy {
public:
	static Strategy* getInstance();

	Indicator decisionMaking();

	void setElevator(const Elevator*);

private:
	Strategy() {};
	const Elevator* elevator;
	static Strategy* instance;
};