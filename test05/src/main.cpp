#include "command_interface.h"
#include "database.h"
#include "user_manager.h"
#include <iostream>
#include <string>

enum class AuthAction {
    LOGIN,
    REGISTER,
    EXIT
};

AuthAction showAuthMenu() {
    std::cout << "\n===== DBMS认证系统 =====\n";
    std::cout << "1. 登录\n";
    std::cout << "2. 注册\n";
    std::cout << "3. 退出\n";
    std::cout << "请选择操作 (1-3): ";
    
    int choice;
    std::cin >> choice;
    std::cin.ignore(); 
    
    switch (choice) {
        case 1: return AuthAction::LOGIN;
        case 2: return AuthAction::REGISTER;
        case 3: return AuthAction::EXIT;
        default: 
            std::cout << "无效选择，请重试\n";
            return showAuthMenu();
    }
}

int main() {
    std::cout << "DBMS启动中...\n";
    
    UserManager userManager;
    std::string email, password;
    bool authenticated = false;
    
    while (!authenticated) {
        AuthAction action = showAuthMenu();
        
        switch (action) {
            case AuthAction::LOGIN:
                std::cout << "请输入邮箱: ";
                std::getline(std::cin, email);
                std::cout << "请输入密码: ";
                std::getline(std::cin, password);
                authenticated = userManager.loginUser(email, password);
                break;
                
            case AuthAction::REGISTER:
                std::cout << "请输入邮箱: ";
                std::getline(std::cin, email);
                std::cout << "请输入密码: ";
                std::getline(std::cin, password);
                if (userManager.registerUser(email, password)) {
                    std::cout << "注册成功! 现在可以登录\n";
                }
                system("pause");
                system("cls");
                break;
                
            case AuthAction::EXIT:
                std::cout << "感谢使用，再见!\n";
                return 0;
        }
    }
    
    // 用户已验证，现在请求数据库名称
    std::string dbName;
    std::cout << "请输入数据库名称: ";
    std::getline(std::cin, dbName);
    
    // 使用当前用户的邮箱创建数据库实例
    Database db(dbName, userManager.getCurrentUser());
    CommandInterface interface(db);
    
    interface.run();
    
    return 0;
}