#include <stdio.h>
#include "los_types.h"

#define TASK_NUM_MAX 16
static uint16 g_uiTaskPriority=0;
static struct losTaskBody g_slosTaskList[TASK_NUM_MAX];
static uint8 g_ucCurrentTaskCount=0;
/*
#函数名：setTaskPriority
#功能:设置任务的优先级，对g_uiTaskPriority进行操作，对应的bit置位
#参数：@priority：任务优先级，不能重复设置，取值范围0-15
#返回值：-1 设置优先级错误，0 设置优先级成功
#次函数并没有用到
*/

int8 setTaskPriority(uint8 priority)
{
	if((g_uiTaskPriority & (0x01<<priority)))
	{
		return -1;//优先级已经设置，不可以重复设置
	}
	else
	{
		g_uiTaskPriority |= 0x01<<priority;
	}
	return 0;
}
/*
#函数名：addTask2List
#函数功能：将任务结构体添加到任务列表
#参数：@task：需要添加的任务结构体
#返回值：-1 添加失败  0 添加成功
 */

int8 addTask2List(struct losTaskBody task)
{
	if(g_ucCurrentTaskCount >=16)
	{
		return -1;
	}
	else
	{
		g_slosTaskList[g_ucCurrentTaskCount].task=task.task;
		g_slosTaskList[g_ucCurrentTaskCount].priority=task.priority;
		g_slosTaskList[g_ucCurrentTaskCount].status=1;
		g_slosTaskList[g_ucCurrentTaskCount].data=task.data;
	}
	g_ucCurrentTaskCount++;
	return 0;
}
/*
#函数名：losCreateTask
#功能：创建任务
#参数：@task 任务所需要的执行函数
	@priority 任务优先级
	@data 传递给执行函数的参数
#返回值：-1  失败  0 成功
 */
int8 losCreateTask(void *task, uint8 priority,void *data)
{
	struct losTaskBody tempTaskBody;
	tempTaskBody.task=task;
	tempTaskBody.status=0;
	tempTaskBody.priority = priority;
	tempTaskBody.data = data;
	return addTask2List(tempTaskBody);
}
/*
#函数名：losSchedule
#函数功能：启动任务轮训
#参数：无
#返回值：无
#需要在while(1)中调用次函数
 */
void losSchedule(void)
{
	uint8 i;
	for(i=0;i<g_ucCurrentTaskCount;i++)
	{
		g_slosTaskList[i].task((void *)g_slosTaskList[i].data);
	}
}
