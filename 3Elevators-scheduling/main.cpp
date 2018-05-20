#include <iostream>
#include <fstream>
#include "Elevator.h"
#include "OddElevator.h"
#include "EvenElevator.h"
#include "Scheduling.h"
using namespace std;
const int maxFloor = 10;

int main() {
	ifstream fin("input.txt");
	ofstream fout1("output1.txt"), fout2("output2.txt"), fout3("output3.txt");
	int N;
	fin >> N;
	Elevator* elevator = new Elevator(maxFloor);
	OddElevator* oddElevator = new OddElevator(maxFloor);
	EvenElevator* evenElevator = new EvenElevator(maxFloor);
	RUN->addElevator(elevator); // 添加电梯
	RUN->addElevator(oddElevator);
	RUN->addElevator(evenElevator);
	for (int i = 0; i < N; i++) {
		Passenger *pass = new Passenger;
		fin >> *pass;
		RUN->addPassenger(pass); // 添加乘客
	}
	do { // 电梯调度
		RUN->assignment();
		RUN->execute();
	} while (!RUN->allArrived());
	fout1 << *oddElevator;
	fout2 << *elevator;
	fout3 << *evenElevator;
	RUN->clear();
	fin.close();
	fout1.close(), fout2.close(), fout3.close();
}