/*
 * product.c - 商品管理模块
 * 功能：商品的添加、删除、修改、查看
 * 负责人：成员1
 */

#include "vending_machine.h"

// 全局商品链表
LLIST *product_list = NULL;

// 初始化商品系统
void product_init(void) {
    if (product_list == NULL) {
        product_list = llist_create(sizeof(Product));
        
        // 添加示例商品
        Product p1 = {1, "可口可乐", 3.5, 20, true};
        Product p2 = {2, "百事可乐", 3.5, 15, true};
        Product p3 = {3, "矿泉水", 2.0, 30, true};
        Product p4 = {4, "薯片", 5.0, 25, true};
        Product p5 = {5, "巧克力", 6.5, 18, true};
        
        llist_insert(product_list, &p1, TAILINSERT);
        llist_insert(product_list, &p2, TAILINSERT);
        llist_insert(product_list, &p3, TAILINSERT);
        llist_insert(product_list, &p4, TAILINSERT);
        llist_insert(product_list, &p5, TAILINSERT);
    }
}

// 商品ID比较函数
int product_cmp_id(const void *data1, const void *data2) {
    const Product *p1 = (const Product *)data1;
    const Product *p2 = (const Product *)data2;
    return p1->id == p2->id;
}

// 根据ID查找商品
Product *product_find_by_id(int id) {
    Product temp;
    temp.id = id;
    return (Product *)llist_find(product_list, &temp, product_cmp_id);
}

// 添加商品
int product_add(Product *p) {
    if (product_list == NULL) {
        product_list = llist_create(sizeof(Product));
    }
    
    // 检查ID是否已存在
    if (product_find_by_id(p->id) != NULL) {
        return -1; // ID已存在
    }
    
    return llist_insert(product_list, p, TAILINSERT);
}

// 删除商品（从链表中移除）
int product_delete(int id) {
    if (product_list == NULL) {
        return -1; // 链表不存在
    }
    
    Product temp;
    temp.id = id;
    
    // 使用链表的删除函数真正删除节点
    if (llist_delete(product_list, &temp, product_cmp_id) == 0) {
        return 0; // 删除成功
    } else {
        return -1; // 商品不存在
    }
}

// 修改商品信息
int product_update(int id, Product *new_data) {
    Product *p = product_find_by_id(id);
    if (p == NULL) {
        return -1; // 商品不存在
    }
    
    // 更新商品信息
    if (strlen(new_data->name) > 0) {
        strcpy(p->name, new_data->name);
    }
    if (new_data->price > 0) {
        p->price = new_data->price;
    }
    if (new_data->stock >= 0) {
        p->stock = new_data->stock;
    }
    p->available = new_data->available;
    
    return 0;
}

// 显示单个商品（用于链表遍历）
void product_display_op(const void *data) {
    const Product *p = (const Product *)data;
    if (p->available && p->stock > 0) {
        printf("%-5d %-20s %-10.2f %-10d %-10s\n", 
               p->id, p->name, p->price, p->stock, "有货");
    }
}

// 显示所有可用商品
void product_display_available(void) {
    clear_screen();
    printf("========================================\n");
    printf("           商品列表\n");
    printf("========================================\n");
    printf("%-5s %-20s %-10s %-10s %-10s\n", "编号", "商品名称", "价格(元)", "库存", "状态");
    printf("----------------------------------------\n");
    
    if (product_list != NULL) {
        llist_display(product_list, product_display_op);
    }
    
    printf("========================================\n");
}

// 显示所有商品（包括不可用的）
void product_display_all(void) {
    clear_screen();
    printf("========================================\n");
    printf("           所有商品列表\n");
    printf("========================================\n");
    printf("%-5s %-20s %-10s %-10s %-10s\n", "编号", "商品名称", "价格(元)", "库存", "状态");
    printf("----------------------------------------\n");
    
    if (product_list != NULL) {
        struct llist_node *cur;
        for (cur = product_list->head.next; cur != &product_list->head; cur = cur->next) {
            Product *p = (Product *)cur->data;
            printf("%-5d %-20s %-10.2f %-10d %-10s\n", 
                   p->id, p->name, p->price, p->stock, 
                   (p->available && p->stock > 0) ? "有货" : "缺货");
        }
    }
    
    printf("========================================\n");
}
