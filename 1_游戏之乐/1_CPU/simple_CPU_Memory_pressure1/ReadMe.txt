压力测试程序概述:

<1>内存压力测试，通过malloc函数分配指定大小的内存，并往分配的内存区域写入数据，从而占用指定大小的内存。

<2>CPU压力测试，在任务管理器的一个刷新周期内，CPU忙碌(执行应用程序)的时间和刷新周期总时间的比率，就是CPU的占用率。
因此在任务管理器的一个刷新周期内，通过调节控制CPU忙碌(借助循环使CPU忙碌)与空闲(借助usleep函数使CPU空闲)的时间比例，从而控制CPU的占用率。



用法示例：
./pressure -m50 -p40 -t60 &					// pressure 程序占用内存 50MB 同时 占用 CPU 40% ,压力状态维持 60 秒,后台执行

用法:
<1>./pressure -m<count> -t<time>			// pressure 程序占用内存 <count>MB,压力状态维持<time>秒
<2>./pressure -p<count> -t<time>           	// pressure 程序占用CPU  <count>%, 压力状态维持<time>秒 
<3>./pressure -m<count> -p<count> -t<time> 	// pressure 程序占用内存 <count>MB 同时 占用 CPU <count>%,压力状态维持<time>秒
<4>./pressure -v                           	// pressure 程序的版本信息
<5>./pressure -h                           	// pressure 程序的帮助说明
<6>./pressure -?                           	// pressure 程序的帮助说明



备注:
<1>如果没有输入时间参数项 -t<time> ，pressure 程序将一直运行，需要手动 killall 结束运行
<2>若需要更新内存压力值或者CPU压力值时，可以利用 killall 命令主动结束正在运行的压力测试程序，然后输入新命令
<3>可以在执行命令时，在末尾添加一个 & 符号，这样命令将进入系统后台来执行
