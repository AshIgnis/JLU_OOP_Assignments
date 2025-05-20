#include "command_interface.h"
#include "query_processor.h"
#include <iostream>
#include <string>

CommandInterface::CommandInterface(Database& db) : database(db) {}

void CommandInterface::run() {
    std::cout << "WELCOME TO DBMS" << std::endl;
    std::cout << "数据库: " << database.getName() << " 已加载" << std::endl;
    displayHelp();
    
    std::string command;
    QueryProcessor processor(database);
    
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, command);
        
        if (command == "exit" || command == "quit") {
            std::cout << "保存数据库并退出..." << std::endl;
            if (database.save()) {
            std::cout << "数据保存成功！" << std::endl;
            } else {
            std::cout << "警告: 数据保存失败！" << std::endl;
            }
            break;
        }else if (command == "help") {
            displayHelp();
        } else {
            try {
                std::string result = processor.processQuery(command);
                std::cout << result << std::endl;
            } catch (const std::exception& e) {
                std::cout << "错误: " << e.what() << std::endl;
            }
        }
    }
}

void CommandInterface::displayHelp() {
    std::cout << "\n可用命令(基于SQL语言):" << std::endl;
    std::cout << "  CREATE TABLE 表名 (列名1 类型1, 列名2 类型2, ...)" << std::endl;
    std::cout << "  DROP TABLE 表名" << std::endl;
    std::cout << "  INSERT INTO 表名 VALUES (值1, 值2, ...)" << std::endl;
    std::cout << "  SELECT * FROM 表名 [WHERE 条件]" << std::endl;
    std::cout << "  UPDATE 表名 SET 列名1=值1, 列名2=值2, ... [WHERE 条件]" << std::endl;
    std::cout << "  DELETE FROM 表名 [WHERE 条件]" << std::endl;
    std::cout << "  SHOW TABLES" << std::endl;
    std::cout << "  help - 显示帮助信息" << std::endl;
    std::cout << "  exit/quit - 保存并退出" << std::endl;
}