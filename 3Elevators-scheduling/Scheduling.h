#pragma once
#include "Elevator.h"
#define RUN Scheduling::getInstance()

class Scheduling {
public:
	static Scheduling* getInstance();
	void assignment(); // 进行乘客分配
	void execute(); // 执行分配的结果
	Indicator schedulingMaking(const Elevator*); // 进行电梯调度

	void clear();
	void clearElevator();
	void clearPassenger();

	void addElevator(Elevator*); // 添加电梯
	void addPassenger(Passenger*); // 添加乘客

	bool allArrived() const; // 是否完成调度
	int getArrivalNumber() const;
	int getPassengerNumber() const;

	static int timer;
	
private:
	Scheduling() { };
	static Scheduling* instance;

	std::vector<Elevator*> elevators; // 电梯们

	std::vector<Passenger*> passengers; // 待处理的乘客们
	std::vector<Passenger*> arrivals; // 已到达的乘客们;
};

static int initialTarget = 0;
static int terminalTarget = 0;
static bool assignmentPriority(const Elevator*, const Elevator*);