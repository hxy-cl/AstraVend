#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "llist.h"

#define MAX_NAME_LEN 50
#define ADMIN_PASSWORD "123"
#define DATETIME_LEN 30

// 商品结构体
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    double price;
    int stock;
    bool available;
} Product;

// 交易记录结构体
typedef struct {
    int product_id;
    char product_name[MAX_NAME_LEN];
    double price;
    int quantity;
    char datetime[DATETIME_LEN];
} Transaction;

// 全局变量声明
extern LLIST *product_list;      // 商品链表
extern LLIST *transaction_list;  // 交易记录链表
extern double total_revenue;     // 总收入

// 商品管理函数 (product.c)
void product_init(void);
void product_display_all(void);
void product_display_available(void);
Product *product_find_by_id(int id);
int product_add(Product *p);
int product_delete(int id);
int product_update(int id, Product *new_data);
void product_display_op(const void *data);
int product_cmp_id(const void *data1, const void *data2);

// 交易管理函数 (transaction.c)
void transaction_record(Product *p, int quantity);
void transaction_display_all(void);
void transaction_display_op(const void *data);
double transaction_get_total_revenue(void);
void get_current_datetime(char *datetime);

// 库存管理函数 (inventory.c)
int inventory_restock(int id, int quantity);
int inventory_get_stock(int id);
int inventory_get_total_stock(void);

// 管理员功能函数 (admin.c)
bool admin_login(void);
void admin_menu(void);
void admin_display_products(void);
void admin_add_product(void);
void admin_remove_product(void);
void admin_update_product(void);
void admin_restock_product(void);
void admin_view_transactions(void);
void admin_view_statistics(void);

// 顾客功能函数 (customer.c)
void customer_menu(void);
void customer_view_products(void);
void customer_purchase_product(void);

// 数据存储函数 (storage.c)
void storage_save_all(void);
void storage_load_all(void);
void storage_save_products(void);
void storage_load_products(void);
void storage_save_transactions(void);
void storage_load_transactions(void);
void storage_save_system(void);
void storage_load_system(void);

// 工具函数
void clear_screen(void);
void pause_screen(void);
void display_menu(void);

#endif
