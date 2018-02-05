#include <iostream>
#include <cmath>
using namespace std;

const size_t MAX = 5; // 乘客上限
size_t timer = 0; // 计时变量
size_t now_floor = 1; // 当前楼层
size_t cnt = 0; // 计数变量
size_t total = 0; // 总时长

struct Passenger { //  存储乘客信息
	size_t request_time;
	size_t initial_floor;
	size_t destination;
	bool is_inside = false;
	int waiting_time = 0; // 到达目的地统计完成后设为-1 
} passenger[MAX];

enum {
	UP, DOWN, STOP
};

void op_up()
{
	for (int i = 0; i < MAX; i++) {
		Passenger& p = passenger[i];
		if (p.waiting_time != -1) {
			if (timer >= p.request_time) {
				p.waiting_time++;
			}
		}
	}
	now_floor++;
	timer++;
}

void op_down()
{
	for (size_t i = 0; i < MAX; i++) {
		Passenger& p = passenger[i];
		if (p.waiting_time != -1) {
			if (timer >= p.request_time) {
				p.waiting_time++;
			}
		}
	}
	now_floor--;
	timer++;
}

void op_stop()
{
	cout << timer << "时，停靠在" << now_floor << "楼：";

	size_t In = 0, Out = 0;

	for (size_t i = 0; i < MAX; i++) {
		Passenger& p = passenger[i];
		if (p.waiting_time != -1) {
			if (p.is_inside) {
				if (p.destination == now_floor) {
					total += p.waiting_time;
					p.waiting_time = -1;
					cnt++;
					Out++;
				}
				else {
					p.waiting_time++;
				}
			}
			else {
				if (timer >= p.request_time) {
					if (p.initial_floor == now_floor) {
						p.is_inside = true;
						In++;
					}
					p.waiting_time++;
				}
			}
		}
	}
	cout << In << " 人上，" << Out << " 人下" << endl;
	timer++;
}

int main()
{

	for (size_t i = 0, dir; i < MAX; i++) {
		Passenger& p = passenger[i];
		cin >> p.request_time >> p.initial_floor >> dir;
		p.destination = dir ? 1 : 10;
	}

	do
	{
		size_t dest_num[3]{ 0 }, dest_time[3]{ 0 };
		dest_time[STOP] = 1;

		for (size_t i = 0; i < MAX; i++) {
			Passenger& p = passenger[i];
			size_t* tmp = nullptr;
			size_t extra = 0;

			if (p.waiting_time != -1) {
				if (p.is_inside) {
					tmp = &p.destination;
				}
				else if (p.request_time <= timer) {
					tmp = &p.initial_floor;
					extra = abs((int)*tmp - (int)p.destination);
				}

				if (tmp != nullptr) {
					if (*tmp > now_floor) {
						dest_num[UP]++;
						dest_time[UP] += *tmp - now_floor + extra;
					}
					else if (*tmp < now_floor) {
						dest_num[DOWN]++;
						dest_time[DOWN] += now_floor - *tmp + extra;
					}
					else {
						dest_num[STOP]++;
					}
				}
			}

		}

		size_t up = dest_time[UP] * (dest_num[DOWN] + dest_num[STOP]);
		size_t down = dest_time[DOWN] * (dest_num[UP] + dest_num[STOP]);
		size_t stop = dest_time[STOP] * (dest_num[UP] + dest_num[DOWN]);

		if (!dest_num[UP] && !dest_num[DOWN] && !dest_num[STOP]) {
			timer++;
			continue;
		}
		if (!dest_num[UP] && !dest_num[DOWN]) {
			op_stop();
		}
		else if (!dest_num[UP] && !dest_num[STOP]) {
			op_down();
		}
		else if (!dest_num[STOP] && !dest_num[DOWN]) {
			op_up();
		}
		else if (!dest_num[UP]) {
			if (down < stop) {
				op_down();
			}
			else if (down > stop) {
				op_stop();
			}
			else {
				if (dest_num[DOWN] > dest_num[STOP]) {
					op_down();
				}
				else {
					op_stop();
				}
			}
		}
		else if (!dest_num[DOWN]) {
			if (up < stop) {
				op_up();
			}
			else if (up > stop) {
				op_stop();
			}
			else {
				if (dest_num[UP] > dest_num[STOP]) {
					op_up();
				}
				else {
					op_stop();
				}
			}
		}
		else if (!dest_num[STOP]) {
			if (down < up) {
				op_down();
			}
			else if (down > up) {
				op_up();
			}
			else {
				if (dest_num[DOWN] > dest_num[UP]) {
					op_down();
				}
				else {
					op_up();
				}
			}
		}
		else {
			if (up < down) {
				if (up < stop) {
					op_up();
				}
				else if (up > stop) {
					op_stop();
				}
				else {
					if (dest_num[UP] > dest_num[STOP]) {
						op_up();
					}
					else {
						op_stop();
					}
				}
			}
			else if (up > down) {
				if (down < stop) {
					op_down();
				}
				else if (down > stop) {
					op_stop();
				}
				else {
					if (dest_num[STOP] > dest_num[DOWN]) {
						op_stop();
					}
					else {
						op_down();
					}
				}
			}
			else {
				if (dest_num[UP] > dest_num[DOWN]) {
					op_up();
				}
				else {
					op_down();
				}
			}
		}
	} while (cnt < MAX);

	cout << endl << "各乘客的等待时间总和: " << total << endl;
	system("pause");
}
