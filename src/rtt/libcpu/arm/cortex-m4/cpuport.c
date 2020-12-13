#include "rtdef.h"

struct exception_stack_frame {
    /* 异常发生时，自动加载到CPU寄存器的内容 @hjr为什么这些时自动加载的？ */
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r12;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t psr;
};

struct stack_frame {
    /* 异常发生时，需手动加载到CPU寄存器的内容 */
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t r11;
    struct exception_stack_frame exception_stack_frame;
};

rt_uint8_t* rt_hw_stack_init(void* entry, void* parameter, rt_uint8_t* stack_addr)
{
    struct stack_frame *stack_frame = RT_NULL;
    rt_uint8_t *stk = RT_NULL;

    /* 获取栈顶指针 rt_hw_stack_init在调用的时候，传给stack_addr的是栈顶指针-4 @hjr为什么？ */    
    stk = stack_addr + sizeof(rt_uint32_t);
    /* 让sdk指针向下8字节对齐 @hjr为什么要8字节对齐？兼容浮点数运算 */
    stk = (rt_uint8_t*)RT_ALIGN_DOWN((rt_uint32_t)stk, 8);
    /* stk指针继续向下移动sizeof(struct stack_frame)个偏移 */
    stk -= sizeof(struct stack_frame);
    /* 将stk指针强转为stack_frame类型后存到stack_frame */
    stack_frame = (struct stack_frame*)stk;
    /* 以 stack_frame 为起始地址，将栈空间里面的 sizeof(struct stack_frame) 个内存初始化为 0xdeadbeef */
    for (rt_uint32_t i = 0; i < sizeof(struct stack_frame) / sizeof(rt_uint32_t); i++) {
        ((rt_uint32_t*)stack_frame)[i] = 0xdeadbeef;
    }
    /* 初始化异常发生时自动保存的寄存器 */
    stack_frame->exception_stack_frame.r0 = (rt_uint32_t)parameter;
    stack_frame->exception_stack_frame.r1 = 0;
    stack_frame->exception_stack_frame.r2 = 0;
    stack_frame->exception_stack_frame.r3 = 0;
    stack_frame->exception_stack_frame.r12 = 0;
    stack_frame->exception_stack_frame.lr = 0;
    stack_frame->exception_stack_frame.pc = (rt_uint32_t)entry;
    stack_frame->exception_stack_frame.psr = 0x01000000L;
    return stk;
}
