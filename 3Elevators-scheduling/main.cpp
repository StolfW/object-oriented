#include <iostream>
#include <fstream>
#include <string>
#include "Elevator.h"
#include "OddElevator.h"
#include "EvenElevator.h"
#include "Scheduling.h"
const int maxFloor = 10;
bool debug = false;

std::string inputFile = "input.txt";
std::string outputFile[3] = { "output1.txt", "output2.txt", "output3.txt" };

void commandLine(int argc, char* cArgv[]) {
	std::string argv[100];
	for (int i = 0; i < argc; i++) {
		argv[i] = cArgv[i];
	}
	if (argc == 2) {
		inputFile = argv[1];
	}
	else if (argc == 3) {
		if (argv[1] == "mode") {
			if (argv[2] == "debug") {
				debug = true;
			}
			else if (argv[2] == "normal") {
				debug = false;
			}
			else {
				std::cout << argv[2] << ' ';
				std::cout << "Param Error!\n";
			}
		}
		else {
			std::cout << argv[1] << ' ';
			std::cout << "Param Error!\n";
		}
	}
	else if (argc == 5) {
		inputFile = argv[1];
		outputFile[0] = argv[2];
		outputFile[1] = argv[3];
		outputFile[2] = argv[4];
	}
	else if (argc > 1) {
		std::cout << "Param Error!\n";
	}
}

int main(int argc, char* argv[]) {
	commandLine(argc, argv);
	std::ifstream fin(inputFile);
	std::ofstream fout1(outputFile[0]), fout2(outputFile[1]), fout3(outputFile[2]), fDebug;
	if (debug) {
		fDebug.open("debug.txt");
	}
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
		if (debug) {
			RUN->outputPosition(fDebug);
		}
	} while (!RUN->allArrived());
	fout1 << *oddElevator;
	fout2 << *elevator;
	fout3 << *evenElevator;
	RUN->clear();
	fin.close();
	fout1.close(), fout2.close(), fout3.close();
	return 0;
}