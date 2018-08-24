#include <stdio.h>
#include <unistd.h>
#include "los_core.h"

void test1(void *data)
{
	printf("test1=%d\n",(int)data);
}

void test2(void *data)
{
	printf("test2=%d\n",(int)data);
}

int main()
{
	losCreateTask(test1,0,(void *)12);
	losCreateTask(test2,0,(void *)11);

	while(1)
	{
		losSchedule();
		sleep(1);
	}
}
