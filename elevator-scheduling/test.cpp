#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int MAX = 5; // 乘客上限
int INF;
int cnt = 0;
int* total_time;
vector<int> pos;

struct Passenger { //  存储乘客信息
	Passenger() { }
	Passenger(int msg) {
		request_time = msg;
	}
	int request_time; // 请求时刻
	int initial_floor; // 起始楼层
	int destination; // 去往楼层
	bool is_inside = false; // 是否在电梯内
	bool is_finish = false;
} passenger[MAX];

int f(int n) 
{
	if (n <= 1) {
		return 1;
	}
	else {
		return n * f(n - 1);
	}
}
bool findp(Passenger* pass, const int& timer, const int& floor)
{
	for (int i = 0; i < MAX; i++) {
		Passenger* p = &pass[i];
		if (!p->is_finish && p->request_time <= timer) {
			if (p->is_inside) {
				if (p->destination == floor) {
					return true;
				}
			}
			else {
				if (p->initial_floor == floor) {
					return true;
				}
			}
		}
	}
	return false;
}
void process_stop(Passenger* pass, int& timer, const int& floor, int& fcnt)
{
	bool flag = false;
	for (int i = 0; i < MAX; i++) {
		Passenger& p = pass[i];
		if (p.is_finish) {
			continue;
		}
		else if (p.request_time <= timer) {
			if (p.is_inside) {
				if (p.destination == floor) {
					fcnt++;
					flag = true;
					p.is_finish = true;
				}
			}
			else if (p.initial_floor == floor) {
				flag = true;
				total_time[cnt]++;
				p.is_inside = true;
			}
		}
	}
	if (flag) {
		timer++;
	}
}
void process_updown(Passenger* pass, int num, int& timer, int& floor)
{
	for (int i = 0; i < MAX; i++) {
		Passenger& p = pass[i];
		if (!p.is_finish && p.request_time <= timer) {
			total_time[cnt] += abs(num);
		}
	}
	timer += abs(num);
	floor += num;
}
void process(int ins[])
{
	int timer = 0;
	int floor = 1;
	int fcnt = 0;
	Passenger *P = new Passenger[MAX];
	for (int i = 0; i < MAX; i++) {
		P[i] = passenger[i];
	}
	for (int i = 0; fcnt < MAX; i++) {
		while (!findp(P, timer, ins[i])) {
			timer++;
			if (timer > INF) {
				total_time[cnt] += timer;
				return;
			}
		}
		process_updown(P, ins[i] - floor, timer, floor);
		process_stop(P, timer, floor, fcnt);
	}
}
void dfs(int idx, int a[], bool b[]) 
{
	if (idx == -1) {
		memset(b, false, pos.size());
		dfs(0, a, b);
	}
	else if (idx == pos.size()) {
		process(a);
		cnt++;
	}
	else for (int i = 0; i < (int)pos.size(); i++) {
		if (b[i])
			continue;
		a[idx] = pos[i % pos.size()];
		b[i] = true;
		dfs(idx + 1, a, b);
		b[i] = false;
	}
}

int main()
{
	for (int i = 0, dir; i < MAX; i++) { // 输入
		Passenger& p = passenger[i];
		cin >> p.request_time >> p.initial_floor >> dir;
		INF = max(INF, p.request_time);
		p.destination = dir ? 1 : 10; // 去往楼层 1 or 10
		//if (find(pos.begin(), pos.end(), p.initial_floor) == pos.end()) {
			pos.push_back(p.initial_floor);
		//}
		//if (find(pos.begin(), pos.end(), p.destination) == pos.end()) {
			pos.push_back(p.destination);
		//}
	}
	INF *= MAX * 10;
	int fp = f(pos.size());
	total_time = new int[fp];
	memset(total_time, 0, 4 * fp);
	dfs(-1, new int[pos.size()], new bool[pos.size()]);
	sort(total_time, total_time + fp);
	cout << endl << "各乘客的等待时间总和: " << total_time[0] << endl;
	system("pause");
}
