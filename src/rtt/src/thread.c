#include "rtdef.h"
#include "rtservice.h"


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
    
}
                        