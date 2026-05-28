/*
 * admin.c - 管理员功能模块
 * 功能：管理员登录、商品管理、交易查看、统计信息
 * 负责人：成员4
 */

#include "vending_machine.h"

// 管理员登录
bool admin_login(void) {
    char password[50];
    int attempts = 3;
    
    while (attempts > 0) {
        clear_screen();
        printf("========================================\n");
        printf("           管理员登录\n");
        printf("========================================\n");
        printf("请输入密码 (剩余尝试次数: %d): ", attempts);
        scanf("%s", password);
        
        if (strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("\n登录成功！\n");
            pause_screen();
            return true;
        } else {
            attempts--;
            printf("\n密码错误！\n");
            if (attempts > 0) {
                pause_screen();
            }
        }
    }
    
    printf("\n登录失败，已超过最大尝试次数！\n");
    pause_screen();
    return false;
}

// 管理员查看商品
void admin_display_products(void) {
    product_display_all();
    pause_screen();
}

// 管理员添加商品
void admin_add_product(void) {
    if (product_list == NULL) {
        product_list = llist_create(sizeof(Product));
    }
    
    clear_screen();
    printf("========================================\n");
    printf("           添加商品\n");
    printf("========================================\n");
    
    Product new_product;
    printf("请输入商品编号: ");
    scanf("%d", &new_product.id);
    
    if (product_find_by_id(new_product.id) != NULL) {
        printf("该商品编号已存在！\n");
        pause_screen();
        return;
    }
    
    printf("请输入商品名称: ");
    scanf("%s", new_product.name);
    printf("请输入商品价格: ");
    scanf("%lf", &new_product.price);
    printf("请输入商品库存: ");
    scanf("%d", &new_product.stock);
    new_product.available = true;
    
    if (product_add(&new_product) == 0) {
        storage_save_products();
        printf("\n商品添加成功！\n");
    } else {
        printf("\n商品添加失败！\n");
    }
    pause_screen();
}

// 管理员删除商品
void admin_remove_product(void) {
    int id;
    char confirm;
    clear_screen();
    printf("========================================\n");
    printf("           删除商品\n");
    printf("========================================\n");
    product_display_all();
    printf("\n请输入要删除的商品编号: ");
    scanf("%d", &id);
    
    // 检查商品是否存在
    Product *p = product_find_by_id(id);
    if (p == NULL) {
        printf("未找到该商品！\n");
        pause_screen();
        return;
    }
    
    // 显示要删除的商品信息并确认
    printf("\n要删除的商品信息:\n");
    printf("编号: %d\n", p->id);
    printf("名称: %s\n", p->name);
    printf("价格: %.2f\n", p->price);
    printf("库存: %d\n", p->stock);
    printf("\n确认删除？(y/n): ");
    scanf(" %c", &confirm);
    
    if (confirm != 'y' && confirm != 'Y') {
        printf("取消删除操作。\n");
        pause_screen();
        return;
    }
    
    // 执行删除
    if (product_delete(id) == 0) {
        storage_save_products();
        printf("\n商品已成功删除！\n");
        
        // 显示删除后的商品列表
        printf("\n当前商品列表:\n");
        product_display_all();
    } else {
        printf("删除失败！\n");
    }
    pause_screen();
}

// 管理员修改商品
void admin_update_product(void) {
    int id;
    clear_screen();
    printf("========================================\n");
    printf("           修改商品信息\n");
    printf("========================================\n");
    product_display_all();
    printf("\n请输入要修改的商品编号: ");
    scanf("%d", &id);
    
    Product *p = product_find_by_id(id);
    if (p == NULL) {
        printf("未找到该商品！\n");
        pause_screen();
        return;
    }
    
    printf("\n当前商品信息:\n");
    printf("名称: %s\n", p->name);
    printf("价格: %.2f\n", p->price);
    printf("库存: %d\n", p->stock);
    
    Product new_data = *p;
    
    printf("\n请输入新的商品名称 (直接回车保持原值): ");
    char temp[100];
    getchar();
    fgets(temp, sizeof(temp), stdin);
    if (strlen(temp) > 1) {
        temp[strlen(temp) - 1] = '\0';
        strcpy(new_data.name, temp);
    }
    
    printf("请输入新的商品价格 (输入0保持原值): ");
    double new_price;
    scanf("%lf", &new_price);
    if (new_price > 0) {
        new_data.price = new_price;
    }
    
    printf("请输入新的商品库存 (输入-1保持原值): ");
    int new_stock;
    scanf("%d", &new_stock);
    if (new_stock >= 0) {
        new_data.stock = new_stock;
    }
    
    if (product_update(id, &new_data) == 0) {
        storage_save_products();
        printf("\n商品信息修改成功！\n");
    } else {
        printf("\n商品信息修改失败！\n");
    }
    pause_screen();
}

// 管理员补货
void admin_restock_product(void) {
    int id, quantity;
    clear_screen();
    printf("========================================\n");
    printf("           商品补货\n");
    printf("========================================\n");
    product_display_all();
    printf("\n请输入要补货的商品编号: ");
    scanf("%d", &id);
    
    Product *p = product_find_by_id(id);
    if (p == NULL) {
        printf("未找到该商品！\n");
        pause_screen();
        return;
    }
    
    printf("当前库存: %d\n", p->stock);
    printf("请输入补货数量: ");
    scanf("%d", &quantity);
    
    if (inventory_restock(id, quantity) == 0) {
        storage_save_products();
        printf("补货成功！当前库存: %d\n", p->stock);
    } else {
        printf("补货失败！\n");
    }
    pause_screen();
}

// 管理员查看交易记录
void admin_view_transactions(void) {
    transaction_display_all();
    pause_screen();
}

// 管理员查看统计信息
void admin_view_statistics(void) {
    clear_screen();
    printf("========================================\n");
    printf("           统计信息\n");
    printf("========================================\n");
    
    int product_count = 0;
    if (product_list != NULL) {
        struct llist_node *cur;
        for (cur = product_list->head.next; cur != &product_list->head; cur = cur->next) {
            product_count++;
        }
    }
    
    int transaction_count = 0;
    if (transaction_list != NULL) {
        struct llist_node *cur;
        for (cur = transaction_list->head.next; cur != &transaction_list->head; cur = cur->next) {
            transaction_count++;
        }
    }
    
    printf("商品总数: %d\n", product_count);
    printf("交易总数: %d\n", transaction_count);
    printf("总收入: %.2f 元\n", transaction_get_total_revenue());
    printf("总库存: %d\n", inventory_get_total_stock());
    
    printf("========================================\n");
    pause_screen();
}

// 管理员菜单
void admin_menu(void) {
    if (!admin_login()) {
        return;
    }
    
    int choice;
    while (1) {
        clear_screen();
        printf("========================================\n");
        printf("           管理员模式\n");
        printf("========================================\n");
        printf("1. 查看所有商品\n");
        printf("2. 添加商品\n");
        printf("3. 删除商品\n");
        printf("4. 修改商品信息\n");
        printf("5. 补货\n");
        printf("6. 查看交易记录\n");
        printf("7. 查看统计信息\n");
        printf("8. 返回主菜单\n");
        printf("========================================\n");
        printf("请选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                admin_display_products();
                break;
            case 2:
                admin_add_product();
                break;
            case 3:
                admin_remove_product();
                break;
            case 4:
                admin_update_product();
                break;
            case 5:
                admin_restock_product();
                break;
            case 6:
                admin_view_transactions();
                break;
            case 7:
                admin_view_statistics();
                break;
            case 8:
                return;
            default:
                printf("无效的选择，请重新输入！\n");
                pause_screen();
                break;
        }
    }
}
