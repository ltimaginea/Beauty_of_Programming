// simple_CPU_pressure1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
int temp_argc = 0;
int change(int * argc, char * * argv[])
{
	int work_time = 0;
	if ((*argc == 4) && ((*argv)[1][1] == 'p') && ((*argv)[2][1] == 'm'))
	{
		char * temp;
		temp = (*argv)[1];
		(*argv)[1] = (*argv)[2];
		(*argv)[2] = temp;
	}
	temp_argc = --(*argc);
	sscanf((*argv)[*argc] + 2, "%d", &work_time);
	(*argv)[*argc] = NULL;
	return work_time;
}
void addMem(int cnt, int work_time)
{
	int * ptr = NULL;
	int some_memory = 1024 * 1024 * cnt;
	ptr = (int *)malloc(some_memory);
	if (ptr != NULL)
	{
		memset(ptr, 0, some_memory);
		printf("malloc %d MB.\n", cnt);
	}
	else
	{
		printf("malloc is false!!!\n");
		return;
	}
	if (temp_argc < 3)
	{
		sleep(work_time);
	}
}
void addCPU(int cnt, int work_time)
{
	printf("cpu occupancy %d%%.\n", cnt);
	typedef unsigned int u32;
	struct timespec now_timer;
	u32 TIME_0, TIME_1, TIME_2;
	clock_gettime(CLOCK_MONOTONIC, &now_timer);
	TIME_0 = (u32)(1000 * now_timer.tv_sec + now_timer.tv_nsec / 1000000);
	int period = 500;
	int busyTime = cnt * period / 100;
	int idleTime = 1000 * (period - busyTime);
	while (1)
	{
		clock_gettime(CLOCK_MONOTONIC, &now_timer);
		TIME_1 = (u32)(1000 * now_timer.tv_sec + now_timer.tv_nsec / 1000000);
		TIME_2 = TIME_1;
		if (((TIME_2 - TIME_0) / 1000) > work_time)
		{
			break;
		}
		for (; (TIME_2 - TIME_1) < busyTime; )
		{
			clock_gettime(CLOCK_MONOTONIC, &now_timer);
			TIME_2 = (u32)(1000 * now_timer.tv_sec + now_timer.tv_nsec / 1000000);
		}
		usleep(idleTime);
	}
}
int main(int argc, char *argv[])
{
	int cnt = 1, c;
	int work_time = change(&argc, &argv);
	while ((c = getopt(argc, argv, "m:p:")) > 0)
	{
		switch (c) {
		case 'm':
			cnt = atoi(optarg);
			addMem(cnt, work_time);
			break;
		case 'p':
			cnt = atoi(optarg);
			addCPU(cnt, work_time);
		}
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
