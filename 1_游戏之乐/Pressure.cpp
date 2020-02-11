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

//
int main(int argc, char* argv[])
{
	return 0;
}
