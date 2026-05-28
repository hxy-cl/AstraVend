/*
 * transaction.c - 交易管理模块
 * 功能：交易记录、购买处理、收入统计
 * 负责人：成员2
 */

#include "vending_machine.h"

// 全局交易记录链表
LLIST *transaction_list = NULL;
double total_revenue = 0.0;

// 获取当前日期时间
void get_current_datetime(char *datetime) {
    time_t now;
    struct tm *timeinfo;
    
    time(&now);
    timeinfo = localtime(&now);
    
    sprintf(datetime, "%04d-%02d-%02d %02d:%02d:%02d",
            timeinfo->tm_year + 1900,
            timeinfo->tm_mon + 1,
            timeinfo->tm_mday,
            timeinfo->tm_hour,
            timeinfo->tm_min,
            timeinfo->tm_sec);
}

// 记录交易
void transaction_record(Product *p, int quantity) {
    if (transaction_list == NULL) {
        transaction_list = llist_create(sizeof(Transaction));
    }
    
    Transaction trans;
    trans.product_id = p->id;
    strcpy(trans.product_name, p->name);
    trans.price = p->price;
    trans.quantity = quantity;
    get_current_datetime(trans.datetime);
    
    llist_insert(transaction_list, &trans, TAILINSERT);
    
    // 更新总收入
    total_revenue += p->price * quantity;
}

// 显示单个交易记录（用于链表遍历）
void transaction_display_op(const void *data) {
    const Transaction *t = (const Transaction *)data;
    printf("%-5d %-20s %-10.2f %-10d %-10s\n",
           t->product_id,
           t->product_name,
           t->price,
           t->quantity,
           t->datetime);
}

// 显示所有交易记录
void transaction_display_all(void) {
    clear_screen();
    printf("========================================\n");
    printf("           交易记录\n");
    printf("========================================\n");
    
    if (transaction_list == NULL || transaction_list->head.next == &transaction_list->head) {
        printf("暂无交易记录\n");
    } else {
        printf("%-5s %-20s %-10s %-10s %-20s\n", "编号", "商品名称", "单价", "数量", "日期时间");
        printf("----------------------------------------\n");
        llist_display(transaction_list, transaction_display_op);
    }
    
    printf("========================================\n");
}

// 获取总收入
double transaction_get_total_revenue(void) {
    return total_revenue;
}
