# elevator-scheduling(normal)

## 问题描述

题目描述基础：一栋10层的大楼（楼层编号1-10），设有一台无限载重的电梯，初始时电梯停在1层。电梯移动1层的耗时为1，在某一层停靠的耗时为1（时间初始为0）。为了使得乘客等待的时间（电梯在目的层的停靠时刻 - 乘客发出请求时刻）总和最小，请你编写一个程序来进行电梯调度。

本次作业是在上一次的电梯调度的代码上进行改善迭代，不仅加入新的功能，也对程序的输入输出提出了新的要求。

## 思路

问题给出的要求是实现一个正常的电梯调度算法，因此在之前代码的基础上稍微改改就行了。。

**电梯每一秒执行如下操作：**

1. 遍历乘客信息，获取有效的目的地信息。

```
目的地指：【已发出请求的未上电梯的乘客的起始楼层】 以及 【已上电梯的乘客的去往楼层】。
```

2. 把所有目的地归纳为三大类：**向上，向下，停靠**。

3. 对运行目标按照以下规则进行选择：

```
main.cpp: 估计当前 向上、向下、停靠 三类行动的耗时，采用预估耗时最少的
```

4. 执行当前运行目标。

注：初始运行目标为停靠。