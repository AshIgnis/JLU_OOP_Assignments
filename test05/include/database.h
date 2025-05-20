#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include <memory>
#include "table.h"

class Database {
public:
    Database(const std::string& name, const std::string& userEmail = "");
    ~Database();

    bool createTable(const std::string& tableName, const std::vector<std::pair<std::string, std::string>>& schema);
    bool dropTable(const std::string& tableName);
    std::shared_ptr<Table> getTable(const std::string& tableName);
    std::vector<std::string> listTables() const;
    
    std::string getName() const;
    bool save() const;
    bool load();

private:
    std::string name;
    std::string userEmail; 
    std::map<std::string, std::shared_ptr<Table>> tables;
    std::string getFilePath() const;
};

#endif // DATABASE_H