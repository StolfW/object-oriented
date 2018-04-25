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
	void goToFloor(int); // ǰ��ָ��¥��
	void stop(); // ͣ���ڵ�ǰ¥��

	int maxFloor;
	int timer; // ��ʱ��
	int currentFloor; // ��ǰλ��
	std::vector<Passenger> passengers; // �˿���
	int achievedPassenger;

	void Execute(Indicator);
private:
	std::queue<std::pair<int, int>> destinationQueue; //Ŀ�ĵض���

	friend std::ostream &operator<< (std::ostream&, Elevator&);
};