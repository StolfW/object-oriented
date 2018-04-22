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
		elevator.passengers.push_back(pass);
	}
	do {
		Strategy::getInstance()->elevator = &elevator;
		elevator.Execute(Strategy::getInstance()->decisionMaking());
	} while (elevator.achievedPassenger < N);
	fout << elevator;
	fin.close();
	fout.close();
}