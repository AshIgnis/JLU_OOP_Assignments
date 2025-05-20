#include "user_manager.h"
#include <direct.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <functional>

UserManager::UserManager() {
    loadUsers();
}

UserManager::~UserManager() {
    saveUsers();
}

bool UserManager::registerUser(const std::string& email, const std::string& password) {
    if (!isEmailValid(email)) {
        std::cout << "邮箱格式不正确!" << std::endl;
        return false;
    }
    
    if (!isPasswordValid(password)) {
        std::cout << "密码不符合要求! 密码长度必须至少为6位" << std::endl;
        return false;
    }
    
    if (users.find(email) != users.end()) {
        std::cout << "该邮箱已注册!" << std::endl;
        return false;
    }
    
    User newUser;
    newUser.email = email;
    newUser.passwordHash = hashPassword(password);
    users[email] = newUser;
    

    std::string userDir = "data/" + email;
    #ifdef _WIN32
        _mkdir(userDir.c_str());
    #else
        mkdir(userDir.c_str(), 0777);
    #endif
    
    saveUsers();
    return true;
}

bool UserManager::loginUser(const std::string& email, const std::string& password) {
    auto it = users.find(email);
    if (it == users.end()) {
        std::cout << "邮箱不存在!" << std::endl;
        return false;
    }
    
    if (it->second.passwordHash != hashPassword(password)) {
        std::cout << "密码错误!" << std::endl;
        return false;
    }
    
    currentUser = email;
    std::cout << "登录成功! 欢迎 " << email << std::endl;
    return true;
}

bool UserManager::isEmailValid(const std::string& email) {
    std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailRegex);
}

bool UserManager::isPasswordValid(const std::string& password) {
    return password.length() >= 6;
}

std::string UserManager::getCurrentUser() const {
    return currentUser;
}

bool UserManager::loadUsers() {
    std::ifstream file(getUsersFilePath());
    if (!file) {
        return false;
    }
    
    users.clear();
    
    int userCount;
    file >> userCount;
    file.ignore();
    
    for (int i = 0; i < userCount; i++) {
        std::string email;
        std::string passwordHash;
        std::getline(file, email);
        std::getline(file, passwordHash);
        
        User user;
        user.email = email;
        user.passwordHash = passwordHash;
        users[email] = user;
    }
    
    return true;
}

bool UserManager::saveUsers() {
    #ifdef _WIN32
        _mkdir("data");
    #else
        mkdir("data", 0777);
    #endif
    
    std::ofstream file(getUsersFilePath());
    if (!file) {
        std::cerr << "无法保存用户数据!" << std::endl;
        return false;
    }
    
    file << users.size() << std::endl;
    
    for (const auto& pair : users) {
        file << pair.second.email << std::endl;
        file << pair.second.passwordHash << std::endl;
    }
    
    return true;
}

std::string UserManager::hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

std::string UserManager::getUsersFilePath() const {
    return "data/users.dat";
}