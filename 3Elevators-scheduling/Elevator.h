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
	Elevator(const int& maxFloor) : maxFloor(maxFloor), currentFloor(1), arrivalNumber(0), status(NONE) { }

	void up(); // 上升
	void down(); // 下降
	void stop(); // 停靠
	void idle(); // 闲置

	void pushPassenger(Passenger*); // 分配乘客
	void pushOperation(const int&); // 

	int getMaxFloor() const;
	int getCurrentFloor() const;
	int getArrivalNumber() const;
	const std::vector<Passenger*>& getInsider() const;
	Indicator getStatus() const;

	virtual bool availableInFloor(int); // 判断可停靠楼层
	virtual std::string type() const;
	virtual void outputPosition(const int& timer) const;

protected:
	int maxFloor; // 最大楼层
	int currentFloor; // 当前位置
	int arrivalNumber; // 已抵达乘客数
	Indicator status;

	std::vector<Passenger*> insider; // 已被分配给电梯的乘客

	std::vector<std::pair<int, int>> operations; // 电梯运行序列

	friend std::ostream &operator<< (std::ostream&, const Elevator&);
};