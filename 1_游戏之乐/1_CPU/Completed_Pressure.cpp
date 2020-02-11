#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

struct
{
	char tmp[100];
	int count_tmp;
}name, vh, pp, mm;

void usage(FILE* fp, int rc)
{
	fprintf(fp, "Usage: ./pressure [-h?v] [-m <count>] [-p <count>] [-t <time>] \n\n");
	fprintf(fp, "        -h?            this help\n");
	fprintf(fp, "        -v             print version info\n");
	fprintf(fp, "        -m count       used MB of memory\n");
	fprintf(fp, "        -p count       cpu occupancy num\n");
	fprintf(fp, "        -t time        run some seconds\n");
	exit(rc);
}

int change(int* argc, char** argv[])
{
	name.count_tmp = 0;
	vh.count_tmp = 0;
	pp.count_tmp = 0;
	mm.count_tmp = 0;

	int sleep_time = -1, i = 0;
	int True = 1, False = 0;
	int flag_t = True, flag_m = True, flag_p = True;
	for (i = 0; (*argv)[i] != NULL; ++i)
	{
		if (i == 0)
		{
			strcpy(name.tmp, (*argv)[i]);
			name.count_tmp = 1;
		}
		else if ((*argv)[i][0] != '-')
		{
			fprintf(stderr, "ERROR: unkown option '%s'\n", (*argv)[i]);
		}
		else
		{
			if ((*argv)[i][1] == 't')
			{
				if (flag_t)
				{
					char temp[100];
					if (((*argv)[i][2] <= '9') && ((*argv)[i][2] >= '0'))
					{
						int j = 2;
						for (j = 2; (*argv)[i][j] != '\0'; ++j)
						{
							if (!(((*argv)[i][j] <= '9') && ((*argv)[i][j] >= '0')))
							{
								break;
							}
						}
						if ((*argv)[i][j] != '\0')
						{
							fprintf(stderr, "ERROR: unkown option '%s'\n", (*argv)[i]);
						}
						else
						{
							strcpy(temp, (*argv)[i]);
							strcpy(temp, temp + 2);
							sscanf(temp, "%d", &sleep_time);
							flag_t = False;
						}
					}
					else if ((*argv)[i][2] == '\0')
					{
						if ((*argv)[i + 1] != NULL)
						{
							if (((*argv)[i + 1][0] <= '9') && ((*argv)[i + 1][0] >= '0'))
							{
								int j = 0;
								for (j = 0; (*argv)[i + 1][j] != '\0'; ++j)
								{
									if (!(((*argv)[i + 1][j] <= '9') && ((*argv)[i + 1][j] >= '0')))
									{
										break;
									}
								}
								if ((*argv)[i + 1][j] != '\0')
								{
									fprintf(stderr, "ERROR: unkown option '%s'\n", (*argv)[i + 1]);
									++i;
								}
								else
								{
									strcpy(temp, (*argv)[i]);
									strcat(temp, (*argv)[i + 1]);
									++i;
									strcpy(temp, temp + 2);
									sscanf(temp, "%d", &sleep_time);
									flag_t = False;
								}
							}
						}
					}
					else
					{
						fprintf(stderr, "ERROR: unkown option '%s'\n", (*argv)[i]);
					}
				}
			}
			else if (((*argv)[i][1] == 'p') || ((*argv)[i][1] == 'm'))
			{
				if ((((*argv)[i][1] == 'p') && flag_p) || (((*argv)[i][1] == 'm') && flag_m))
				{
					if (((*argv)[i][2] <= '9') && ((*argv)[i][2] >= '0'))
					{
						int j = 2;
						for (j = 2; (*argv)[i][j] != '\0'; ++j)
						{
							if (!(((*argv)[i][j] <= '9') && ((*argv)[i][j] >= '0')))
							{
								break;
							}
						}
						if ((*argv)[i][j] != '\0')
						{
							fprintf(stderr, "ERROR: unkown option '%s'\n", (*argv)[i]);
						}
						else
						{
							if ((*argv)[i][1] == 'p')
							{
								strcpy(pp.tmp, (*argv)[i]);
								pp.count_tmp = 1;
								flag_p = False;
							}
							else
							{
								strcpy(mm.tmp, (*argv)[i]);
								mm.count_tmp = 1;
								flag_m = False;
							}
						}
					}
					else if ((*argv)[i][2] == '\0')
					{
						if ((*argv)[i][1] == 'p')
						{
							strcpy(pp.tmp, (*argv)[i]);
							pp.count_tmp = 1;
						}
						else
						{
							strcpy(mm.tmp, (*argv)[i]);
							mm.count_tmp = 1;
						}
						if ((*argv)[i + 1] != NULL)
						{
							if (((*argv)[i + 1][0] <= '9') && ((*argv)[i + 1][0] >= '0'))
							{
								int j = 0;
								for (j = 0; (*argv)[i + 1][j] != '\0'; ++j)
								{
									if (!(((*argv)[i + 1][j] <= '9') && ((*argv)[i + 1][j] >= '0')))
									{
										break;
									}
								}
								if ((*argv)[i + 1][j] != '\0')
								{
									fprintf(stderr, "ERROR: unkown option '%s'\n", (*argv)[i + 1]);
									++i;
								}
								else
								{
									if ((*argv)[i][1] == 'p')
									{
										strcat(pp.tmp, (*argv)[i + 1]);
										flag_p = False;
									}
									else
									{
										strcat(mm.tmp, (*argv)[i + 1]);
										flag_m = False;
									}
									++i;
								}
							}
						}
					}
					else
					{
						fprintf(stderr, "ERROR: unkown option '%s'\n", (*argv)[i]);
					}
				}
			}
			else
			{
				if ((*argc) == 2)
				{
					if (((*argv)[i][1] == 'h') && ((*argv)[i][2] == '\0'))
					{
						strcpy(vh.tmp, (*argv)[i]);
						vh.count_tmp = 1;
					}
					else if (((*argv)[i][1] == '?') && ((*argv)[i][2] == '\0'))
					{
						strcpy(vh.tmp, (*argv)[i]);
						vh.count_tmp = 1;
					}
					else if (((*argv)[i][1] == 'v') && ((*argv)[i][2] == '\0'))
					{
						strcpy(vh.tmp, (*argv)[i]);
						vh.count_tmp = 1;
					}
					else
					{
						fprintf(stderr, "ERROR: unkown option '%s'\n", (*argv)[i]);
					}
				}
				else
				{
					fprintf(stderr, "ERROR: unkown option '%c'\n", (*argv)[i][1]);
				}
			}
		}
	}
	if (!((((*argc) == 2) && ((*argv)[1][1] == '?')) || (((*argc) == 2) && ((*argv)[1][1] == 'h')) || (((*argc) == 2) && ((*argv)[1][1] == 'v'))))
	{
		int FLAG = 0;
		if (flag_t)
		{
			printf("loss option 't'!!! or option 't' requires an argument!!!\n");
		}
		if (flag_m && (mm.count_tmp == 1))
		{
			printf("option requires an argument -- 'm'\n");
			FLAG = 1;
		}
		if (flag_p && (pp.count_tmp == 1))
		{
			printf("option requires an argument -- 'p'\n");
			FLAG = 1;
		}
		if (FLAG)
		{
			usage(stdout, 0);
		}
	}
	*argc = name.count_tmp + vh.count_tmp + pp.count_tmp + mm.count_tmp;
	int A = 0, B = 1, C = 2, D = 3;
	if ((*argc) == 2)
	{
		C = 1;
		D = 2;
	}
	else if ((*argc) == 1)
	{
		D = 1;
	}
	if (name.count_tmp)
	{
		(*argv)[A] = name.tmp;
	}
	if (pp.count_tmp)
	{
		(*argv)[C] = pp.tmp;
	}
	if (mm.count_tmp)
	{
		(*argv)[B] = mm.tmp;
	}
	if (vh.count_tmp)
	{
		(*argv)[B] = vh.tmp;
	}
	(*argv)[D] = NULL;
	return sleep_time;
}

void addMem(int cnt, int sleep_time)
{
	int temp_argc = name.count_tmp + vh.count_tmp + pp.count_tmp + mm.count_tmp;
	int* ptr = NULL;
	int some_memory = 1024 * 1024 * cnt;
	ptr = (int*)malloc(some_memory);
	if (ptr != NULL)
	{
		memset(ptr, 0, some_memory);
		printf("malloc %d MB\n", cnt);
	}
	else
	{
		printf("malloc is false!\n");
		exit(0);
	}
	if (temp_argc > 2)
	{
		;
	}
	else
	{
		if (sleep_time == -1)
		{
			pause();
		}
		else
		{
			sleep(sleep_time);
		}
	}
}

void addCPU(int cnt, int sleep_time)
{
	printf("cpu occupancy %d%%\n", cnt);
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
		if (sleep_time != -1)
		{
			if (((TIME_2 - TIME_0) / 1000) > sleep_time)
			{
				break;
			}
		}
		for (; (TIME_2 - TIME_1) < busyTime; )
		{
			clock_gettime(CLOCK_MONOTONIC, &now_timer);
			TIME_2 = (u32)(1000 * now_timer.tv_sec + now_timer.tv_nsec / 1000000);
		}
		usleep(idleTime);
	}
}

int main(int argc, char* argv[])
{
	char version[100] = { "v1.0_20191018" };
	int cnt = 1;
	int c = 0;
	int sleep_time = -1;
	if (argc >= 2)
	{
		sleep_time = change(&argc, &argv);
	}
	if (argc < 2)
	{
		usage(stdout, 0);
	}
	while ((c = getopt(argc, argv, "h?vm:p:")) > 0)
	{
		switch (c) {
		case 'v':
			printf("%s: version %s\n", argv[0], version);
			exit(0);
		case 'p':
			cnt = atoi(optarg);
			addCPU(cnt, sleep_time);
			break;
		case 'h':
		case '?':
			usage(stdout, 0);
			break;
		case 'm':
			cnt = atoi(optarg);
			addMem(cnt, sleep_time);
			break;
		default:
			fprintf(stderr, "ERROR: unkown option '%c'\n", c);
			usage(stderr, 1);
			break;
		}
	}
	exit(0);
}