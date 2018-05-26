#pragma once
#include "Elevator.h"

class OddElevator : public Elevator {
public:
	OddElevator(const int& maxFloor) : Elevator(maxFloor) { }

	virtual bool availableInFloor(int); // 判断可停靠楼层
	virtual std::string type() const;
	virtual void outputPosition(std::ofstream& fout) const;

private:

};