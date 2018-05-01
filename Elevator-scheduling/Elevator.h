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
	void goToFloor(int); // ǰ��ָ��¥��
	void stop(); // ͣ���ڵ�ǰ¥��
	void addPassenger(const Passenger&); // ��ӳ˿�
	bool isAllAchieved() const; // �Ƿ���ɵ���
	void Execute(Indicator); // ִ��ָ��
	int getMaxFloor() const;
	int getTimer() const;
	int getCurrentFloor() const;
	const std::vector<Passenger>& getPassengers() const;

private:
	int maxFloor; // ���¥��
	int timer; // ��ʱ��
	int currentFloor; // ��ǰλ��
	int achievedPassenger; // �ѵִ�˿���
	std::vector<Passenger> passengers; // �˿���
	std::queue<std::pair<int, int>> destinationQueue; // �������ж���

	friend std::ostream &operator<< (std::ostream&, Elevator&);
};