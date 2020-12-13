#ifndef RTSERVICE_H
#define RTSERVICE_H

#include "rtdef.h"

/* 初始化链表节点 */
rt_inline void rt_list_init(rt_list_t* list)
{
    list->next = list->prev = list;
}

/* 在双向链表头部后面加入一个节点 */
rt_inline void rt_list_insert_after(rt_list_t* list, rt_list_t* node)
{
    list->next->prev = node;
    node->prev = list;
    node->next = list->next;
    list->next = node;
}

/* 在双向链表头部前面加入一个节点 */
rt_inline void rt_list_insert_before(rt_list_t* list, rt_list_t* node)
{
    list->prev->next = node;
    node->next = list;
    node->prev = list->prev;
    list->prev = node;
}

/* 在双向链表中删除一个节点 */
rt_inline void rt_list_remove(rt_list_t* node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    
    node->next = node->prev = node;  /* 重新初始化该节点？ */
}

#endif
