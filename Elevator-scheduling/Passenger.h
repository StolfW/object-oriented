#pragma once
#include <iostream>

class Passenger { // 存储乘客信息
public:
	Passenger() : isInside(false), isAchieved(false), waitingTime(0) { }
	int requestTime; // 请求时刻
	int initialFloor; // 起始楼层
	int destination; // 去往楼层
	int waitingTime; // 等待时间
	bool isInside; // 是否在电梯内
	bool isAchieved; // 是否到达目的地
	friend std::istream &operator>> (std::istream&, Passenger&);
};