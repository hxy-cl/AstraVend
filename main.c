/*
 * main.c - 主程序和菜单系统
 * 功能：程序入口、主菜单、系统初始化
 */

#include "vending_machine.h"

// 清屏函数
void clear_screen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// 暂停屏幕
void pause_screen(void) {
    printf("\n按回车键继续...");
    getchar();
    getchar();
}

// 显示主菜单
void display_menu(void) {
    clear_screen();
    printf("========================================\n");
    printf("     自助售货机管理系统\n");
    printf("========================================\n");
    printf("1. 顾客模式\n");
    printf("2. 管理员模式\n");
    printf("3. 退出系统\n");
    printf("========================================\n");
    printf("请选择: ");
}

// 主函数
int main(void) {
    int choice;
    
    // 初始化链表
    product_list = NULL;
    transaction_list = NULL;
    total_revenue = 0.0;
    
    // 加载已保存的数据
    storage_load_all();
    
    // 如果没有加载到数据，则初始化默认数据
    if (product_list == NULL || product_list->head.next == &product_list->head) {
        product_init();
    }
    
    while (1) {
        display_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                customer_menu();
                break;
            case 2:
                admin_menu();
                break;
            case 3:
                printf("\n正在保存数据...\n");
                storage_save_all();
                printf("数据已保存！\n");
                
                // 清理链表
                if (product_list != NULL) {
                    llist_destroy(product_list);
                }
                if (transaction_list != NULL) {
                    llist_destroy(transaction_list);
                }
                
                printf("感谢使用，再见！\n");
                return 0;
            default:
                printf("无效的选择，请重新输入！\n");
                pause_screen();
                break;
        }
    }
    
    return 0;
}
