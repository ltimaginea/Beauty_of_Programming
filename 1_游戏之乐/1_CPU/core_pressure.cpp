void addMem(int cnt)
{
	int * ptr = NULL;
	int some_memory = 1024 * 1024 * (cnt - 1);
	ptr = (int *)malloc(some_memory);
	if (ptr != NULL)
	{
		memset(ptr, 0, some_memory);
		printf("malloc is OK!\n");
	}
	else
	{
		printf("malloc is false!\n");
	}
	pause();
	//usleep(time);
}

void addCPU(int cnt)
{
	int period = 500;
	int busyTime = (cnt - 1)*period / 100;
	int idleTime = 100 * (period - busyTime);
	while (true)
	{
		clock_t t = clock();
		while ((((double)(clock() - t)) / CLOCK_PER_SEC * 1000) <= busyTime)
		{
			;
		}
		usleep(idleTime);
	}
}