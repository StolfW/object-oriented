#pragma once
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "Passenger.h"

enum Indicator {
	UP, DOWN, STOP, NONE
};

class Elevator {
public:
	Elevator(const int& maxFloor) : maxFloor(maxFloor), currentFloor(1), status(NONE) { }

	void up(); // ����
	void down(); // �½�
	void stop(); // ͣ��
	void idle(); // ����

	void pushPassenger(Passenger*); // ����˿�
	void pushOperation(const int&); // 

	int getMaxFloor() const;
	int getCurrentFloor() const;
	const std::vector<Passenger*>& getInsider() const;
	Indicator getStatus() const;

	virtual bool availableInFloor(int); // �жϿ�ͣ��¥��
	virtual std::string type() const;
	virtual void outputPosition(const int& timer) const;

protected:
	int maxFloor; // ���¥��
	int currentFloor; // ��ǰλ��
	Indicator status; // ��ǰ����״̬���ϻ��£�

	std::vector<Passenger*> insider; // �ѱ���������ݵĳ˿�

	std::vector<std::pair<int, int>> operations; // ������������

	friend std::ostream &operator<< (std::ostream&, const Elevator&);
};