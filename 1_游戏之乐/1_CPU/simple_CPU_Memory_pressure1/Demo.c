#include <stdio.h>
#include <stdlib.h>
int main()
{
	
	//如果没有输入时间参数项，程序将一直运行，需要手动 killall 结束运行

	// pressure 程序占用内存50MB，压力状态维持60s，后台运行
	system("/tmp/upgrade/pressure -m50 -t60 &");
	
	// pressure 程序占用 CPU 50%，压力状态维持180s，后台运行
	system("/tmp/upgrade/pressure -p50 -t180 &");
	
	// pressure 程序占用 CPU 20%，同时占用内存50MB，压力状态维持360s，后台运行
	system("/tmp/upgrade/pressure -p20 -m50 -t360 &");
	
	//主动结束 pressure 程序
	system("killall pressure");
	
	exit(0);
}
