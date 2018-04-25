#pragma once
#include <queue>
#include <vector>
#include <cmath>
#include <iostream>
#include "Passenger.h"

enum Indicator {
	UP, DOWN, STOP, NONE
};

class Elevator {
public:
	Elevator(int maxFloor) : maxFloor(maxFloor), timer(0), currentFloor(0), achievedPassenger(0) {}
	void goToFloor(int); // 前往指定楼层
	void stop(); // 停靠在当前楼层

	int maxFloor;
	int timer; // 计时器
	int currentFloor; // 当前位置
	std::vector<Passenger> passengers; // 乘客们
	int achievedPassenger;

	void Execute(Indicator);
private:
	std::queue<std::pair<int, int>> destinationQueue; //目的地队列

	friend std::ostream &operator<< (std::ostream&, Elevator&);
};