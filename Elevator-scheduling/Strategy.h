#pragma once
#include "Elevator.h"
#include <vector>
#include <algorithm>

class Strategy {
public:
	static Strategy* getInstance();

	Indicator decisionMaking();

	const Elevator* elevator;

private:
	Strategy() {};
	static Strategy* instance;
};