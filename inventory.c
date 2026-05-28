/*
 * inventory.c - 库存管理模块
 * 功能：商品补货、库存查询、库存统计
 * 负责人：成员3
 */

#include "vending_machine.h"

// 获取指定商品的库存
int inventory_get_stock(int id) {
    Product *p = product_find_by_id(id);
    if (p == NULL) {
        return -1; // 商品不存在
    }
    return p->stock;
}

// 补货
int inventory_restock(int id, int quantity) {
    Product *p = product_find_by_id(id);
    if (p == NULL) {
        return -1; // 商品不存在
    }
    
    if (quantity <= 0) {
        return -2; // 补货数量无效
    }
    
    p->stock += quantity;
    p->available = true;
    
    return 0; // 成功
}

// 获取总库存
int inventory_get_total_stock(void) {
    int total = 0;
    
    if (product_list != NULL) {
        struct llist_node *cur;
        for (cur = product_list->head.next; cur != &product_list->head; cur = cur->next) {
            Product *p = (Product *)cur->data;
            if (p->available) {
                total += p->stock;
            }
        }
    }
    
    return total;
}
