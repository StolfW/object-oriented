#pragma once
#include <iostream>

class Passenger{ // 存储乘客信息
public:
	Passenger() : isInside(false), isArrived(false), isAssigned(false) { }
	int getRequestTime() const;
	int getInitialFloor() const;
	int getTerminalFloor() const;
	bool inside() const;
	bool arrived() const;
	bool assigned() const;
	void setInside();
	void setArrived();
	void setAssigned();

private:
	int requestTime; // 请求时刻
	int initialFloor; // 起始楼层
	int terminalFloor; // 去往楼层
	bool isInside; // 是否在电梯内
	bool isArrived; // 是否到达目的地
	bool isAssigned; // 是否已分配给电梯
	friend std::istream &operator>> (std::istream&, Passenger&);
};