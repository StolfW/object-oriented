#pragma once
#include "Elevator.h"
#define RUN Scheduling::getInstance()

class Scheduling {
public:
	static Scheduling* getInstance();
	void assignment(); // ���г˿ͷ���
	void execute(); // ִ�з���Ľ��
	Indicator schedulingMaking(const Elevator*); // ���е��ݵ���

	void clear();
	void clearElevator();
	void clearPassenger();

	void addElevator(Elevator*); // ��ӵ���
	void addPassenger(Passenger*); // ��ӳ˿�

	bool allArrived() const; // �Ƿ���ɵ���
	int getArrivalNumber() const;
	int getPassengerNumber() const;

	static int timer;
	
private:
	Scheduling() { };
	static Scheduling* instance;

	std::vector<Elevator*> elevators; // ������

	std::vector<Passenger*> passengers; // ������ĳ˿���
	std::vector<Passenger*> arrivals; // �ѵ���ĳ˿���;
};

static int initialTarget = 0;
static int terminalTarget = 0;
static bool assignmentPriority(const Elevator*, const Elevator*);