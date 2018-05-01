#include <iostream>
#include <fstream>
#include "Elevator.h"
#include "Strategy.h"

using namespace std;

const int maxFloor = 3;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int N;
	fin >> N;
	Elevator elevator(maxFloor);
	for (int i = 0; i < N; i++) {
		Passenger pass;
		fin >> pass;
		elevator.addPassenger(pass);
	}
	do {
		Strategy::getInstance()->setElevator(&elevator);
		elevator.Execute(Strategy::getInstance()->decisionMaking());
	} while (!elevator.isAllAchieved());
	fout << elevator;
	fin.close();
	fout.close();
}