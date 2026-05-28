/*
 * customer.c - 顾客功能模块
 * 功能：浏览商品、购买商品
 * 负责人：成员5
 */

#include "vending_machine.h"

// 顾客查看商品
void customer_view_products(void) {
    product_display_available();
    pause_screen();
}

// 顾客购买商品
void customer_purchase_product(void) {
    int id, quantity;
    double payment, total;
    
    product_display_available();
    printf("\n请输入要购买的商品编号: ");
    scanf("%d", &id);
    
    Product *p = product_find_by_id(id);
    if (p == NULL || !p->available) {
        printf("商品不存在或已下架！\n");
        pause_screen();
        return;
    }
    
    if (p->stock <= 0) {
        printf("该商品已售罄！\n");
        pause_screen();
        return;
    }
    
    printf("请输入购买数量: ");
    scanf("%d", &quantity);
    
    if (quantity <= 0) {
        printf("购买数量必须大于0！\n");
        pause_screen();
        return;
    }
    
    if (quantity > p->stock) {
        printf("库存不足！当前库存: %d\n", p->stock);
        pause_screen();
        return;
    }
    
    total = p->price * quantity;
    printf("\n商品: %s\n", p->name);
    printf("单价: %.2f 元\n", p->price);
    printf("数量: %d\n", quantity);
    printf("总计: %.2f 元\n", total);
    printf("\n请输入支付金额: ");
    scanf("%lf", &payment);
    
    if (payment < total) {
        printf("支付金额不足！\n");
        pause_screen();
        return;
    }
    
    // 更新库存
    p->stock -= quantity;
    if (p->stock == 0) {
        p->available = false;
    }
    
    // 记录交易
    transaction_record(p, quantity);
    
    // 保存数据
    storage_save_products();
    storage_save_transactions();
    storage_save_system();
    
    printf("\n购买成功！\n");
    printf("找零: %.2f 元\n", payment - total);
    pause_screen();
}

// 顾客菜单
void customer_menu(void) {
    int choice;
    while (1) {
        clear_screen();
        printf("========================================\n");
        printf("           顾客模式\n");
        printf("========================================\n");
        printf("1. 查看商品列表\n");
        printf("2. 购买商品\n");
        printf("3. 返回主菜单\n");
        printf("========================================\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                customer_view_products();
                break;
            case 2:
                customer_purchase_product();
                break;
            case 3:
                return;
            default:
                printf("无效的选择，请重新输入！\n");
                pause_screen();
                break;
        }
    }
}
