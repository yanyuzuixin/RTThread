#include "rtdef.h"
#include "rtservice.h"
#include "rthw.h"

rt_err_t rt_thread_init(rt_thread_t thread,
    void (*entry)(void* parameter),
    void* parameter,
    void* stack_start,
    rt_uint32_t stack_size)
{
    rt_list_init(&(thread->tlist));
    thread->entry = (void*)entry;
    thread->parameter = parameter;
    thread->stack_addr = stack_start;
    thread->stack_size = stack_size;
    /* 初始化线程栈，并返回栈顶指针 */
    thread->sp = (void*)rt_hw_stack_init(thread->entry,
        thread->parameter, 
        (rt_uint8_t*)thread->stack_addr + thread->stack_size - sizeof(rt_uint32_t)); /* @hjr为什么要-4 */
    return RT_EOK;
}
