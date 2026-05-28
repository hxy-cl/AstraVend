#ifndef __LLIST_H
#define __LLIST_H

#define HEADINSERT 0
#define TAILINSERT 1

typedef void (*llist_op)(const void *);//定义了函数指针类型
typedef int (*llist_cmp)(const void *, const void *);//定义了函数指针类型
    
struct llist_node//数据节点的结构
{   
    struct llist_node *prev;//前驱指针
    struct llist_node *next;//后继指针
    char data[0];//用来标记数据域的首地址
};

typedef struct llist_head//头节点的结构
{   
    int size;//用来存储用户指定数据域的大小
    struct llist_node head;//表示头节点
}LLIST;

LLIST *llist_create(int );
    
int llist_insert(LLIST *, const void *, int );
    
void llist_display(LLIST *, llist_op);

void llist_destroy(LLIST *);

void *llist_find(LLIST *, const void *, llist_cmp);
    
int llist_delete(LLIST *, const void *, llist_cmp);
    
int llist_fetch(LLIST *, const void *, llist_cmp, void *);

#endif
