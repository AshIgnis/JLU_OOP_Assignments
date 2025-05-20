#include "database.h"
#include <fstream>
#include <direct.h>
#include <stdexcept>
#include <sstream>
#include <iostream>

Database::Database(const std::string& name, const std::string& userEmail) : name(name), userEmail(userEmail) {
    load();
}

Database::~Database() {
    save();
}

bool Database::createTable(const std::string& tableName, const std::vector<std::pair<std::string, std::string>>& schema) {
    if (tables.find(tableName) != tables.end()) {
        return false; 
    }
    
    tables[tableName] = std::make_shared<Table>(tableName, schema);
    return true;
}

bool Database::dropTable(const std::string& tableName) {
    if (tables.find(tableName) == tables.end()) {
        return false; 
    }
    
    tables.erase(tableName);
    return true;
}

std::shared_ptr<Table> Database::getTable(const std::string& tableName) {
    if (tables.find(tableName) == tables.end()) {
        return nullptr; 
    }
    
    return tables[tableName];
}

std::vector<std::string> Database::listTables() const {
    std::vector<std::string> tableNames;
    for (const auto& pair : tables) {
        tableNames.push_back(pair.first);
    }
    return tableNames;
}

std::string Database::getName() const {
    return name;
}

std::string Database::getFilePath() const {
    char currentDir[FILENAME_MAX];
    _getcwd(currentDir, sizeof(currentDir));
    
    std::string path(currentDir);
    
    size_t pos = path.find("test05");
    if (pos != std::string::npos) {
        path = path.substr(0, pos + 6);
    }
    
    if (path.back() != '\\' && path.back() != '/') {
        path += '\\';
    }
    
    if (!userEmail.empty()) {
        path += "data\\" + userEmail + "\\" + name + ".txt";
    } else {
        path += "data\\" + name + ".txt";
    }
    
    return path;
}

bool Database::save() const {
    std::string path = getFilePath();
    
    std::string directory;
    size_t lastSlash = path.find_last_of("\\/");
    if (lastSlash != std::string::npos) {
        directory = path.substr(0, lastSlash);
    }
    
    #ifdef _WIN32
        _mkdir(directory.c_str());  
    #else
        mkdir(directory.c_str(), 0777);
    #endif

    std::ofstream file(path);
    if (!file) {
        std::cerr << "无法打开文件进行写入：" << path << std::endl;
        return false;
    }
    
    file << tables.size() << std::endl;
    
    for (const auto& pair : tables) {
        file << pair.first << std::endl;
        pair.second->save(file);
    }
    
    file.flush();
    
    if (!file) {
        std::cerr << "写入文件时发生错误：" << path << std::endl;
        return false;
    }
    
    std::cout << "数据已成功保存到：" << path << std::endl;
    return true;
}

bool Database::load() {
    std::ifstream file(getFilePath());
    if (!file) {
        return false; 
    }
    
    tables.clear();
    
    int tableCount = 0;
    file >> tableCount;
    file.ignore(); 
    
    for (int i = 0; i < tableCount; i++) {
        std::string tableName;
        std::getline(file, tableName);
        
        int schemaSize = 0;
        file >> schemaSize;
        file.ignore(); 
        
        std::vector<std::pair<std::string, std::string>> schema;
        for (int j = 0; j < schemaSize; j++) {
            std::string line;
            std::getline(file, line);
            std::istringstream iss(line);
            std::string columnName, columnType;
            iss >> columnName >> columnType;
            schema.emplace_back(columnName, columnType);
        }
        
        auto table = std::make_shared<Table>(tableName, schema);
        table->load(file);
        tables[tableName] = table;
    }
    
    return true;
}