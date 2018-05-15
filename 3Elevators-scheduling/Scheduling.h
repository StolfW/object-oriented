#pragma once
#include "Elevator.h"
#define RUN Scheduling::getInstance()

class Scheduling {
public:
	static Scheduling* getInstance();
	void schedule(); // ���о���
	Indicator decisionMaking(const Elevator*);
	void execute();

	void clear();
	void clearElevator();
	void clearPassenger();

	void addElevator(Elevator*); // ��ӵ���
	void addPassenger(Passenger*); // ��ӳ˿�

	bool allArrived() const; // �Ƿ���ɵ���
	int getArrivalNumber() const;

	static int timer;

private:
	Scheduling() { };
	static Scheduling* instance;

	std::vector<Elevator*> elevators; // ������
	std::vector<Passenger*> passengers; // �˿���
};

static int cmpTarget = 0;
bool compare(const Elevator*, const Elevator*);