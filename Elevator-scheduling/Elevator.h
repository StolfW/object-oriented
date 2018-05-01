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
	Elevator(int maxFloor) : maxFloor(maxFloor), timer(0), currentFloor(0), achievedPassenger(0) { }
	void goToFloor(int); // 前往指定楼层
	void stop(); // 停靠在当前楼层
	void addPassenger(const Passenger&); // 添加乘客
	bool isAllAchieved() const; // 是否完成调度
	void Execute(Indicator); // 执行指令
	int getMaxFloor() const;
	int getTimer() const;
	int getCurrentFloor() const;
	const std::vector<Passenger>& getPassengers() const;

private:
	int maxFloor; // 最大楼层
	int timer; // 计时器
	int currentFloor; // 当前位置
	int achievedPassenger; // 已抵达乘客数
	std::vector<Passenger> passengers; // 乘客们
	std::queue<std::pair<int, int>> destinationQueue; // 电梯运行队列

	friend std::ostream &operator<< (std::ostream&, Elevator&);
};