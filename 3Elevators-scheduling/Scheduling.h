#pragma once
#include "Elevator.h"
#define RUN Scheduling::getInstance()

class Scheduling {
public:
	static Scheduling* getInstance();
	void schedule(); // 进行决策
	Indicator decisionMaking(const Elevator*);
	void execute();

	void clear();
	void clearElevator();
	void clearPassenger();

	void addElevator(Elevator*); // 添加电梯
	void addPassenger(Passenger*); // 添加乘客

	bool allArrived() const; // 是否完成调度
	int getArrivalNumber() const;

	static int timer;

private:
	Scheduling() { };
	static Scheduling* instance;

	std::vector<Elevator*> elevators; // 电梯们
	std::vector<Passenger*> passengers; // 乘客们
};

static int cmpTarget = 0;
bool compare(const Elevator*, const Elevator*);