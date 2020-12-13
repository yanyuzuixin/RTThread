
#include "rtdef.h"
#include "rtservice.h"
#include "rtthread.h"

#include "rtconfig.h"

ALIGN(RT_ALIGN_SIZE)

/* 定义线程栈 */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];

/* 定义线程控制块 */
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;

rt_uint32_t flag1;
rt_uint32_t flag2;

void delay(rt_uint32_t n)
{
    for (; n != 0; n--) {
    }
}

void flag1_thread_entry(void* p_arg)
{
    for (;;) {
        flag1 = 0;
        delay(100);
        flag1 = 1;
        delay(100);
    }
}

void flag2_thread_entry(void* p_arg)
{
    for (;;) {
        flag2 = 0;
        delay(100);
        flag2 = 1;
        delay(100);
    }
}



int main(void)
{
    /* 硬件初始化 */
    /* 将硬件相关的初始化放在这里，如果是软件仿真则没有相关的初始化代码 */

    /* 初始化线程 */
    rt_thread_init(&rt_flag1_thread,
        flag1_thread_entry,
        RT_NULL,
        &rt_flag1_thread_stack[0],
        sizeof(rt_flag1_thread_stack));
    rt_thread_init(&rt_flag2_thread,
        flag2_thread_entry,
        RT_NULL,
        &rt_flag2_thread_stack[0],
        sizeof(rt_flag2_thread_stack));
}

