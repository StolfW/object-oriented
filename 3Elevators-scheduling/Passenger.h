#pragma once
#include <iostream>

class Passenger{ // �洢�˿���Ϣ
public:
	Passenger() : isInside(false), isArrived(false), isAssigned(false) { }
	int getRequestTime() const;
	int getInitialFloor() const;
	int getTerminalFloor() const;
	bool inside() const;
	bool arrived() const;
	bool assigned() const;
	void setInside();
	void setArrived();
	void setAssigned();

private:
	int requestTime; // ����ʱ��
	int initialFloor; // ��ʼ¥��
	int terminalFloor; // ȥ��¥��
	bool isInside; // �Ƿ��ڵ�����
	bool isArrived; // �Ƿ񵽴�Ŀ�ĵ�
	bool isAssigned; // �Ƿ��ѷ��������
	friend std::istream &operator>> (std::istream&, Passenger&);
};