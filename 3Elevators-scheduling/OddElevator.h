#pragma once
#include "Elevator.h"

class OddElevator : public Elevator {
public:
	OddElevator(const int& maxFloor) : Elevator(maxFloor) { }

	virtual bool availableInFloor(int); // �жϿ�ͣ��¥��
	virtual std::string type() const;
	virtual void outputPosition(const int& timer) const;

private:

};