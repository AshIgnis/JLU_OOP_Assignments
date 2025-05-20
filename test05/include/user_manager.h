#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <fstream>

struct User {
    std::string email;
    std::string passwordHash;
};

class UserManager {
public:
    UserManager();
    ~UserManager();
    
    bool registerUser(const std::string& email, const std::string& password);
    bool loginUser(const std::string& email, const std::string& password);
    bool isEmailValid(const std::string& email);
    bool isPasswordValid(const std::string& password);
    std::string getCurrentUser() const;
    
private:
    std::map<std::string, User> users;
    std::string currentUser;
    
    bool loadUsers();
    bool saveUsers();
    std::string hashPassword(const std::string& password);
    std::string getUsersFilePath() const;
};

#endif // USER_MANAGER_H