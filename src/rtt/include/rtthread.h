#ifndef RT_THREAD_H
#define RT_THREAD_H

#include "rtdef.h"

rt_err_t rt_thread_init(rt_thread_t thread,
    void (*entry)(void* parameter),
    void* parameter,
    void* stack_start,
    rt_uint32_t stack_size);

#endif
