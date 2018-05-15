#pragma once
#include "Elevator.h"

class EvenElevator : public Elevator {
public:
	EvenElevator(const int& maxFloor) : Elevator(maxFloor) { }

	virtual bool availableInFloor(int); // 判断可停靠楼层
	virtual std::string type() const;
	virtual void outputPosition(const int& timer) const;

private:

};