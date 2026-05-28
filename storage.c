/*
 * storage.c - 数据存储模块
 * 功能：数据的保存和加载
 * 负责人：成员6
 */

#include "vending_machine.h"

// 保存商品数据
void storage_save_products(void) {
    FILE *fp;
    
    fp = fopen("products.dat", "w");
    if (fp == NULL) {
        printf("警告：无法保存商品数据到文件！\n");
        return;
    }
    
    if (product_list != NULL) {
        int count = 0;
        struct llist_node *cur;
        for (cur = product_list->head.next; cur != &product_list->head; cur = cur->next) {
            count++;
        }
        
        fprintf(fp, "%d\n", count);
        for (cur = product_list->head.next; cur != &product_list->head; cur = cur->next) {
            Product *p = (Product *)cur->data;
            fprintf(fp, "%d\n", p->id);
            fprintf(fp, "%s\n", p->name);
            fprintf(fp, "%.2f\n", p->price);
            fprintf(fp, "%d\n", p->stock);
            fprintf(fp, "%d\n", p->available ? 1 : 0);
        }
    } else {
        fprintf(fp, "0\n");
    }
    
    fclose(fp);
}

// 加载商品数据
void storage_load_products(void) {
    FILE *fp;
    int count, temp_available;
    
    fp = fopen("products.dat", "r");
    if (fp == NULL) {
        return; // 文件不存在，使用默认初始化
    }
    
    if (fscanf(fp, "%d", &count) == 1) {
        if (product_list == NULL) {
            product_list = llist_create(sizeof(Product));
        }
        
        for (int i = 0; i < count; i++) {
            Product p;
            fscanf(fp, "%d", &p.id);
            fscanf(fp, "%s", p.name);
            fscanf(fp, "%lf", &p.price);
            fscanf(fp, "%d", &p.stock);
            fscanf(fp, "%d", &temp_available);
            p.available = (temp_available == 1);
            
            llist_insert(product_list, &p, TAILINSERT);
        }
    }
    
    fclose(fp);
}

// 保存交易记录
void storage_save_transactions(void) {
    FILE *fp;
    
    fp = fopen("transactions.dat", "w");
    if (fp == NULL) {
        printf("警告：无法保存交易数据到文件！\n");
        return;
    }
    
    if (transaction_list != NULL) {
        int count = 0;
        struct llist_node *cur;
        for (cur = transaction_list->head.next; cur != &transaction_list->head; cur = cur->next) {
            count++;
        }
        
        fprintf(fp, "%d\n", count);
        for (cur = transaction_list->head.next; cur != &transaction_list->head; cur = cur->next) {
            Transaction *t = (Transaction *)cur->data;
            fprintf(fp, "%d\n", t->product_id);
            fprintf(fp, "%s\n", t->product_name);
            fprintf(fp, "%.2f\n", t->price);
            fprintf(fp, "%d\n", t->quantity);
            fprintf(fp, "%s\n", t->datetime);
        }
    } else {
        fprintf(fp, "0\n");
    }
    
    fclose(fp);
}

// 加载交易记录
void storage_load_transactions(void) {
    FILE *fp;
    int count;
    
    fp = fopen("transactions.dat", "r");
    if (fp == NULL) {
        return;
    }
    
    if (fscanf(fp, "%d", &count) == 1) {
        if (transaction_list == NULL) {
            transaction_list = llist_create(sizeof(Transaction));
        }
        
        for (int i = 0; i < count; i++) {
            Transaction t;
            fscanf(fp, "%d", &t.product_id);
            fscanf(fp, "%s", t.product_name);
            fscanf(fp, "%lf", &t.price);
            fscanf(fp, "%d", &t.quantity);
            fscanf(fp, "%s", t.datetime);
            
            llist_insert(transaction_list, &t, TAILINSERT);
        }
    }
    
    fclose(fp);
}

// 保存系统统计信息
void storage_save_system(void) {
    FILE *fp;
    
    fp = fopen("system.dat", "w");
    if (fp == NULL) {
        printf("警告：无法保存系统数据到文件！\n");
        return;
    }
    
    fprintf(fp, "%.2f\n", total_revenue);
    fclose(fp);
}

// 加载系统统计信息
void storage_load_system(void) {
    FILE *fp;
    
    fp = fopen("system.dat", "r");
    if (fp != NULL) {
        fscanf(fp, "%lf", &total_revenue);
        fclose(fp);
    }
}

// 保存所有数据
void storage_save_all(void) {
    storage_save_products();
    storage_save_transactions();
    storage_save_system();
}

// 加载所有数据
void storage_load_all(void) {
    storage_load_products();
    storage_load_transactions();
    storage_load_system();
}
