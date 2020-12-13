#include "rtdef.h"

struct exception stack frame {
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r12;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t psr;
};




rt_uint8_t* rt_hw_stack_init(void* entry, void* parameter, rt_uint8_t* stack_addr)
{
    
}