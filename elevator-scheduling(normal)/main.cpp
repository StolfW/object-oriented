#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

const size_t MAX = 5; // 乘客上限
const size_t TOP = 10; // 楼层上限
size_t timer = 0; // 计时变量
size_t now_floor = 1; // 当前楼层
size_t cnt = 0; // 计数变量
size_t total = 0; // 总时长
ifstream fin;
ofstream fout;

struct Passenger { //  存储乘客信息
	size_t request_time; // 请求时刻
	size_t initial_floor; // 起始楼层
	size_t destination; // 去往楼层
	bool is_inside = false; // 是否在电梯内
	int waiting_time = 0; // 等待时间，到达去往楼层统计完成后设为-1 
} passenger[MAX];

enum {
	UP, DOWN, STOP
};

void op_up() // 电梯向上运行
{
	for (int i = 0; i < MAX; i++) { // 已发出请求但未到达去往楼层的乘客等待时间+1
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

void op_down() // 电梯向下运行
{
	for (size_t i = 0; i < MAX; i++) { // 已发出请求但未到达去往楼层的乘客等待时间+1
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

void op_stop() // 电梯停靠
{
	fout << timer << "时，停靠在" << now_floor << "楼：";

	size_t In = 0, Out = 0; // 统计上下人数

	for (size_t i = 0; i < MAX; i++) {
		Passenger& p = passenger[i];
		if (p.waiting_time != -1) {
			if (p.is_inside) { // 判断乘客是否在电梯内
				if (p.destination == now_floor) { // 判断是否下电梯
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
					if (p.initial_floor == now_floor) { // 判断是否上电梯
						p.is_inside = true;
						In++;
					}
					p.waiting_time++;
				}
			}
		}
	}
	fout << In << " 人上，" << Out << " 人下" << endl;
	timer++;
}

int main()
{
	fin.open("input.txt");
	fout.open("output.txt");
	for (int T = 1; T <= 5; T++) {
		timer = 0; // 计时变量
		now_floor = 1; // 当前楼层
		cnt = 0; // 计数变量
		total = 0; // 总时长
		fout << "==========\n\n" << "第 " << T << " 组数据：\n\n";
		for (size_t i = 0; i < MAX; i++) { // 输入
			Passenger& p = passenger[i];
			p.is_inside = false;
			p.waiting_time = 0;
			fin >> p.request_time >> p.initial_floor >> p.destination;
		}
		do
		{
			size_t dest_num[3]{ 0 }, dest_time[3]{ 0 }; // 0 - UP, 1 - DOWN, 2 - STOP, 统计三类行动的人数和耗时
			size_t up_to_floor = 0, down_to_floor = TOP + 1;

			for (size_t i = 0; i < MAX; i++) {
				Passenger& p = passenger[i];
				size_t* tmp = nullptr;

				if (p.waiting_time != -1) {
					if (p.is_inside) {
						tmp = &p.destination;
					}
					else if (p.request_time <= timer) {
						tmp = &p.initial_floor;
					}

					if (tmp != nullptr) {
						up_to_floor = max(up_to_floor, *tmp);
						down_to_floor = min(down_to_floor, *tmp);

						if (*tmp > now_floor) {
							dest_num[UP]++;
						}
						else if (*tmp < now_floor) {
							dest_num[DOWN]++;
						}
						else {
							dest_num[STOP]++;
						}
					}
				}
			}

			size_t stop_cnt = 0, up_extra = 0, down_extra = 0;
			for (size_t i = 0; i < MAX; i++) {
				Passenger& p = passenger[i];

				if (p.waiting_time != -1) {
					if (dest_num[UP]) {
						if (p.is_inside) {
							dest_time[UP] +=
								abs((int)up_to_floor - (int)now_floor)
								+ abs((int)up_to_floor - (int)p.destination);

							if (p.destination != up_to_floor) {
								dest_time[UP]++;
							}
						}
						else if (p.request_time <= timer) {
							dest_time[UP] +=
								abs((int)up_to_floor - (int)now_floor)
								+ abs((int)up_to_floor - (int)p.initial_floor)
								+ abs((int)p.destination - (int)p.initial_floor);

							if (p.destination != up_to_floor) {
								dest_time[UP]++;
							}
						}
					}

					if (dest_num[DOWN]) {
						if (p.is_inside) {
							dest_time[DOWN] +=
								abs((int)down_to_floor - (int)now_floor)
								+ abs((int)down_to_floor - (int)p.destination);

							if (p.destination != down_to_floor) {
								dest_time[DOWN]++;
							}
						}
						else if (p.request_time <= timer) {
							dest_time[DOWN] +=
								abs((int)down_to_floor - (int)now_floor)
								+ abs((int)down_to_floor - (int)p.initial_floor)
								+ abs((int)p.destination - (int)p.initial_floor);

							if (p.destination != down_to_floor) {
								dest_time[DOWN]++;
							}
						}
					}

					if (dest_num[STOP]) {
						if (p.is_inside) {
							if (p.destination != now_floor) {
								dest_time[STOP]++;
							}
							else {
								stop_cnt++;
							}
						}
						else if (p.request_time <= timer) {
							if (p.initial_floor != now_floor) {
								//dest_time[STOP]++;
							}
							else {
								stop_cnt++;
								if (p.destination < now_floor) {
									up_extra = now_floor - p.destination;
								}
								else if (p.destination > now_floor) {
									down_extra = p.destination - now_floor;
								}
							}
						}
					}
				}
			}
			if (!dest_num[UP] && !dest_num[DOWN] && !dest_num[STOP]) {
				timer++;
			}
			else if (!dest_num[UP] && !dest_num[DOWN]) {
				op_stop();
			}
			else if (!dest_num[STOP] && !dest_num[DOWN]) {
				op_up();
			}
			else if (!dest_num[UP] && !dest_num[STOP]) {
				op_down();
			}
			else if (!dest_num[UP]) {
				if (dest_time[STOP] * (down_extra + 1) > stop_cnt * ((abs((int)down_to_floor - (int)now_floor)) * 2 + 1)) {
					op_down();
				}
				else {
					op_stop();
				}
			}
			else if (!dest_num[DOWN]) {
				if (dest_time[STOP] * (up_extra + 1) > stop_cnt * ((abs((int)up_to_floor - (int)now_floor)) * 2 + 1)) {
					op_up();
				}
				else {
					op_stop();
				}
			}
			else if (!dest_num[STOP]) {
				if (dest_time[UP] < dest_time[DOWN]) {
					op_up();
				}
				else {
					op_down();
				}
			}
			else {
				if (dest_time[UP] < dest_time[DOWN]) {
					if (dest_time[STOP] * (up_extra + 1) > stop_cnt * ((abs((int)up_to_floor - (int)now_floor)) * 2 + 1)) {
						op_up();
					}
					else {
						op_stop();
					}
				}
				else {
					if (dest_time[STOP] * (down_extra + 1) > stop_cnt * ((abs((int)down_to_floor - (int)now_floor)) * 2 + 1)) {
						op_down();
					}
					else {
						op_stop();
					}
				}
			}
		} while (cnt < MAX); // 是否所有乘客抵达
		fout << endl << "各乘客的等待时间总和: " << total << endl << endl;
	}
	fout << "==========\n";
	fin.close();
	fout.close();
	system("pause");
}
