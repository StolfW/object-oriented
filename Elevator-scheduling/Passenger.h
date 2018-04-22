#pragma once
#include <iostream>

class Passenger { // �洢�˿���Ϣ
public:
	Passenger() : isInside(false), isAchieved(false), waitingTime(0) { }
	int requestTime; // ����ʱ��
	int initialFloor; // ��ʼ¥��
	int destination; // ȥ��¥��
	int waitingTime; // �ȴ�ʱ��
	bool isInside; // �Ƿ��ڵ�����
	bool isAchieved; // �Ƿ񵽴�Ŀ�ĵ�
	friend std::istream &operator>> (std::istream&, Passenger&);
};