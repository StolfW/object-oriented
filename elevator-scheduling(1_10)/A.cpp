#include <iostream>
#include <cmath>
using namespace std;

const size_t MAX = 5; // 乘客上限
size_t timer = 0; // 计时变量
size_t now_floor = 1; // 当前楼层
size_t cnt = 0; // 计数变量
size_t total = 0; // 总时长

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
	cout << timer << "时，停靠在" << now_floor << "楼：";

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
	cout << In << " 人上，" << Out << " 人下" << endl;
	timer++;
}

int main()
{

	for (size_t i = 0, dir; i < MAX; i++) { // 输入
		Passenger& p = passenger[i];
		cin >> p.request_time >> p.initial_floor >> dir;
		p.destination = dir ? 1 : 10; // 去往楼层 1 or 10
	}

	do
	{
		size_t dest_num[3]{ 0 }, dest_time[3]{ 0 }; // 0 - UP, 1 - DOWN, 2 - STOP, 归纳三类行动的人数和耗时
		dest_time[STOP] = 1; // 停靠只消耗1时刻

		for (size_t i = 0; i < MAX; i++) {
			Passenger& p = passenger[i];
			size_t* tmp = nullptr;
			size_t extra = 0; // 乘客发出请求时，可以知道其去往方向，送达过程作为额外时间花费纳入统计

			if (p.waiting_time != -1) {
				// 获取向下、向下、停靠这三类行动的人数和耗时
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
		
		// 计算三类行动中若选择其中一种，另外两类的等待时间
		size_t up = dest_time[UP] * (dest_num[DOWN] + dest_num[STOP]); // 若选择向上，则向下和停靠的乘客需要等待的时间
		size_t down = dest_time[DOWN] * (dest_num[UP] + dest_num[STOP]); // 以此类推
		size_t stop = dest_time[STOP] * (dest_num[UP] + dest_num[DOWN]); // ...

		if (!dest_num[UP] && !dest_num[DOWN] && !dest_num[STOP]) { // 若当前没有乘客发出请求，则原地停留1s
			timer++;
			continue;
		}
		if (!dest_num[UP] && !dest_num[DOWN]) { // 若只有停靠这类行动有人需要执行，则直接执行
			op_stop();
		}
		else if (!dest_num[UP] && !dest_num[STOP]) { // 若只有向下这类行动有人需要执行，则直接执行
			op_down();
		}
		else if (!dest_num[STOP] && !dest_num[DOWN]) { // 若只有向上这类行动有人需要执行，则直接执行
			op_up();
		}
		else if (!dest_num[UP]) { // 若向上无人需要执行，则只比较停靠和向下，以此类推
			if (down < stop) {
				op_down();
			}
			else if (down > stop) {
				op_stop();
			}
			else { // 若权值相同，则人多优先
				if (dest_num[DOWN] > dest_num[STOP]) {
					op_down();
				}
				else {
					op_stop();
				}
			}
		}
		else if (!dest_num[DOWN]) { // ...
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
		else if (!dest_num[STOP]) { // ...
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
		else { // 若三类行动都有人需要执行，则比较三者
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
	} while (cnt < MAX); // 是否所有乘客抵达

	cout << endl << "各乘客的等待时间总和: " << total << endl;
}
