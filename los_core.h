#ifndef _LOS_CORE_H_
#define _LOS_CORE_H_
#include "los_types.h"

int8 losCreateTask(void *task, uint8 priority,void *data);
void losSchedule(void);

#endif
