#ifndef _LOS_TYPES_H_
#define _LOS_TYPES_H_

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;

typedef char int8;
typedef int  int16;
typedef long int32;

struct  losTaskBody
{
	void (*task)(void *);//任务函数指针
	uint8 priority;//优先级
	uint8 status;//任务状态
	void *data;//任务创建传入的参数
};

#endif