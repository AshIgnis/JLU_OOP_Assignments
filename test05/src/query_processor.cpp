#include "query_processor.h"
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

QueryProcessor::QueryProcessor(Database& db) : database(db) {}

std::string QueryProcessor::processQuery(const std::string& query) {
    this->query = query;
    std::vector<std::string> tokens = tokenize(query);
    
    if (tokens.empty()) {
        return "空查询";
    }
    
    std::string command = tokens[0];
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);
    
    if (command == "CREATE" && tokens.size() > 1 && tokens[1] == "TABLE") {
        return createTable(tokens);
    } else if (command == "DROP" && tokens.size() > 1 && tokens[1] == "TABLE") {
        return dropTable(tokens);
    } else if (command == "INSERT" && tokens.size() > 1 && tokens[1] == "INTO") {
        return insertInto(tokens);
    } else if (command == "SELECT") {
        return selectFrom(tokens);
    } else if (command == "UPDATE") {
        return updateTable(tokens);
    } else if (command == "DELETE" && tokens.size() > 1 && tokens[1] == "FROM") {
        return deleteFrom(tokens);
    } else if (command == "SHOW" && tokens.size() > 1 && tokens[1] == "TABLES") {
        std::vector<std::string> tables = database.listTables();
        std::stringstream ss;
        ss << "表列表：" << std::endl;
        for (const auto& table : tables) {
            ss << " - " << table << std::endl;
        }
        return ss.str();
    }
    
    return "未知命令: " + command;
}

std::vector<std::string> QueryProcessor::tokenize(const std::string& query) {
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;
    char quoteChar = 0;
    
    for (char c : query) {
        if ((c == '\'' || c == '"') && (!inQuotes || quoteChar == c)) {
            inQuotes = !inQuotes;
            if (inQuotes) quoteChar = c;
            continue;
        }
        
        if (c == ' ' && !inQuotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }
    
    if (!token.empty()) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string QueryProcessor::createTable(const std::vector<std::string>& tokens) {
    if (tokens.size() < 4 || tokens[3][0] != '(') {
        return "语法错误: CREATE TABLE tableName (col1 type1, col2 type2, ...)";
    }
    
    std::string tableName = tokens[2];
    
    std::string schemaStr = query.substr(query.find('(') + 1);
    schemaStr = schemaStr.substr(0, schemaStr.find_last_of(')'));
    
    std::vector<std::pair<std::string, std::string>> schema;
    std::istringstream ss(schemaStr);
    std::string columnDef;
    
    while (std::getline(ss, columnDef, ',')) {
        columnDef.erase(0, columnDef.find_first_not_of(" \t"));
        columnDef.erase(columnDef.find_last_not_of(" \t") + 1);
        
        std::istringstream columnSS(columnDef);
        std::string columnName, columnType;
        columnSS >> columnName >> columnType;
        
        schema.emplace_back(columnName, columnType);
    }
    
    if (schema.empty()) {
        return "错误: 表定义中没有列";
    }
    
    if (database.createTable(tableName, schema)) {
        return "表 '" + tableName + "' 创建成功";
    } else {
        return "错误: 表 '" + tableName + "' 已存在";
    }
}

std::string QueryProcessor::dropTable(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        return "语法错误: DROP TABLE tableName";
    }
    
    std::string tableName = tokens[2];
    
    if (database.dropTable(tableName)) {
        return "表 '" + tableName + "' 删除成功";
    } else {
        return "错误: 表 '" + tableName + "' 不存在";
    }
}

std::string QueryProcessor::insertInto(const std::vector<std::string>& tokens) {
    if (tokens.size() < 5 || tokens[3] != "VALUES" || tokens[4][0] != '(') {
        return "语法错误: INSERT INTO tableName VALUES (val1, val2, ...)";
    }
    
    std::string tableName = tokens[2];
    auto table = database.getTable(tableName);
    
    if (!table) {
        return "错误: 表 '" + tableName + "' 不存在";
    }
    
    std::string valuesStr = query.substr(query.find('(') + 1);
    valuesStr = valuesStr.substr(0, valuesStr.find_last_of(')'));
    
    std::vector<std::string> values;
    std::istringstream ss(valuesStr);
    std::string valueStr;
    
    while (std::getline(ss, valueStr, ',')) {
        valueStr.erase(0, valueStr.find_first_not_of(" \t"));
        valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
        
        if ((valueStr[0] == '\'' && valueStr[valueStr.size() - 1] == '\'') ||
            (valueStr[0] == '"' && valueStr[valueStr.size() - 1] == '"')) {
            valueStr = valueStr.substr(1, valueStr.size() - 2);
        }
        
        values.push_back(valueStr);
    }
    
    if (table->insert(values)) {
        return "成功插入一条记录到表 '" + tableName + "'";
    } else {
        return "错误: 插入失败，列数不匹配";
    }
}

std::string QueryProcessor::selectFrom(const std::vector<std::string>& tokens) {
    if (tokens.size() < 4 || tokens[1] != "*" || tokens[2] != "FROM") {
        return "语法错误: SELECT * FROM tableName [WHERE condition]";
    }
    
    std::string tableName = tokens[3];
    auto table = database.getTable(tableName);
    
    if (!table) {
        return "错误: 表 '" + tableName + "' 不存在";
    }
    
    std::string condition;
    if (tokens.size() > 4 && tokens[4] == "WHERE") {
        for (size_t i = 5; i < tokens.size(); i++) {
            condition += tokens[i] + " ";
        }
        condition = condition.substr(0, condition.size() - 1);
    }
    
    std::vector<Record> results = table->select(condition);
    return formatResults(results);
}

std::string QueryProcessor::updateTable(const std::vector<std::string>& tokens) {
    if (tokens.size() < 4 || tokens[2] != "SET") {
        return "语法错误: UPDATE tableName SET col1=val1, col2=val2, ... [WHERE condition]";
    }
    
    std::string tableName = tokens[1];
    auto table = database.getTable(tableName);
    
    if (!table) {
        return "错误: 表 '" + tableName + "' 不存在";
    }
    
    size_t wherePos = std::find(tokens.begin(), tokens.end(), "WHERE") - tokens.begin();
    
    std::map<std::string, std::string> values;
    for (size_t i = 3; i < (wherePos < tokens.size() ? wherePos : tokens.size()); i++) {
        std::string assignment = tokens[i];
        if (assignment.back() == ',') assignment.pop_back();
        
        size_t eqPos = assignment.find('=');
        if (eqPos != std::string::npos) {
            std::string column = assignment.substr(0, eqPos);
            std::string value = assignment.substr(eqPos + 1);
            
            if ((value[0] == '\'' && value.back() == '\'') ||
                (value[0] == '"' && value.back() == '"')) {
                value = value.substr(1, value.size() - 2);
            }
            
            values[column] = value;
        }
    }
    
    std::string condition;
    if (wherePos < tokens.size()) {
        for (size_t i = wherePos + 1; i < tokens.size(); i++) {
            condition += tokens[i] + " ";
        }
        condition = condition.substr(0, condition.size() - 1); 
    }
    
    if (table->update(values, condition)) {
        return "成功更新表 '" + tableName + "'";
    } else {
        return "没有记录被更新";
    }
}

std::string QueryProcessor::deleteFrom(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        return "语法错误: DELETE FROM tableName [WHERE condition]";
    }
    
    std::string tableName = tokens[2];
    auto table = database.getTable(tableName);
    
    if (!table) {
        return "错误: 表 '" + tableName + "' 不存在";
    }
    
    std::string condition;
    if (tokens.size() > 3 && tokens[3] == "WHERE") {
        for (size_t i = 4; i < tokens.size(); i++) {
            condition += tokens[i] + " ";
        }
        condition = condition.substr(0, condition.size() - 1); 
    }
    
    if (table->deleteRecords(condition)) {
        return "成功从表 '" + tableName + "' 删除记录";
    } else {
        return "没有记录被删除";
    }
}

std::string QueryProcessor::formatResults(const std::vector<Record>& records) {
    if (records.empty()) {
        return "查询结果为空";
    }
    
    std::stringstream ss;

    auto columns = records[0].getAllValues();
    std::vector<std::string> columnNames;
    for (const auto& column : columns) {
        columnNames.push_back(column.first);
    }
    
    std::map<std::string, size_t> columnWidths;
    for (const auto& name : columnNames) {
        columnWidths[name] = name.length();
    }
    
    for (const auto& record : records) {
        auto values = record.getAllValues();
        for (const auto& column : columnNames) {
            columnWidths[column] = std::max(columnWidths[column], values[column].length());
        }
    }

    ss << "+";
    for (const auto& column : columnNames) {
        ss << std::string(columnWidths[column] + 2, '-') << "+";
    }
    ss << std::endl;
    
    ss << "|";
    for (const auto& column : columnNames) {
        ss << " " << std::setw(columnWidths[column]) << column << " |";
    }
    ss << std::endl;
    
    ss << "+";
    for (const auto& column : columnNames) {
        ss << std::string(columnWidths[column] + 2, '-') << "+";
    }
    ss << std::endl;
    
    for (const auto& record : records) {
        ss << "|";
        auto values = record.getAllValues();
        for (const auto& column : columnNames) {
            ss << " " << std::setw(columnWidths[column]) << values[column] << " |";
        }
        ss << std::endl;
    }
    
    ss << "+";
    for (const auto& column : columnNames) {
        ss << std::string(columnWidths[column] + 2, '-') << "+";
    }
    ss << std::endl;
    
    ss << records.size() << " 条记录";
    
    return ss.str();
}