﻿# elevator-scheduling

## 问题描述

一栋10层的大楼（楼层编号1-10），设有一台无限载重的电梯，初始时电梯停在1层。电梯移动1层的耗时为1，在某一层停靠的耗时为1（时间初始为0）。为了使得乘客等待的时间（**电梯在目的层的停靠时刻 - 乘客发出请求时刻**）总和最小，请你编写一个程序来进行电梯调度。
 
输入有5个请求，每个请求一行，格式为```请求时刻 起始楼层数 去往方向```，其中方向为```0```代表向上去往10层，为```1```代表向下去往1层。 

输出每次对应的决策，每一行的输出格式为```xx时，停靠在x楼```。其中，“xx时刻”指的是在某层楼**停靠的时刻**，且**不算入在该层的停靠时间**。如：

1. 当0时刻时，电梯此时在1层，输入有```0 1 0```，那么电梯从1层接客（1s）前往10层（9s），应输出```10时，停靠在10楼```（1+9=10）。此时，该乘客等待时间为(10-0=)10。

2. 当0时刻时，电梯此时在1层，输入有```0 2 0```，那么电梯从1层前往2层（1s），接上乘客（1s），前往10层（8s），应输出```10时，停靠在10楼```（1+1+8=10）。此时，该乘客等待时间为(10-0=)10s。

最后输出完成5个请求（所有乘客都到达目的地）后，各乘客的等待时间总和。

## 思路

问题给出的要求是实现一个简化的电梯调度算法，考虑到电梯**不能预知请求**，所以如果要保证所有乘客等待总时长最短，应该采取**贪心策略**。

**乘客的信息全部保存在结构体数组中，成员变量如下：**

```
1. 请求时刻
2. 起始楼层数
3. 去往方向
4. 是否在电梯内
5. 等待时间
```

**电梯每一秒执行如下操作：**

0. 若当前时刻没有任何新的请求。-> 4.

1. 遍历乘客信息，获取当前所有目的地，并记录每一个目的地的人数。

```
目的地指：**已发出请求的未上电梯的乘客的起始楼层**以及**已上电梯的乘客的去往方向**
```

2. 把所有目的地归纳为三大类：**向上，向下，停靠**，并在归类时添加权值，权值为针对**每一个具体目的**的优先级指标。

```
权值 = 人数 * 耗时
```

3. 把运行目标设定为三类目的地中权值最大的一个，若相同则设定为停靠。

4. 执行当前运行目标。

注：初始运行目标为停靠。
