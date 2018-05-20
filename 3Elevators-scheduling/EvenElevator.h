#pragma once
#include "Elevator.h"

class EvenElevator : public Elevator {
public:
	EvenElevator(const int& maxFloor) : Elevator(maxFloor) { }

	virtual bool availableInFloor(int); // �жϿ�ͣ��¥��
	virtual std::string type() const;
	virtual void outputPosition(const int& timer) const;

private:

};