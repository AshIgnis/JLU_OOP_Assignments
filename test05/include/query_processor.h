#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include <string>
#include <iostream>
#include <vector>
#include "database.h"

class QueryProcessor {
public:
    QueryProcessor(Database& db);
    
    std::string processQuery(const std::string& query);

private:
    Database& database;
    std::string query;
    
    std::string createTable(const std::vector<std::string>& tokens);
    std::string dropTable(const std::vector<std::string>& tokens);
    std::string insertInto(const std::vector<std::string>& tokens);
    std::string selectFrom(const std::vector<std::string>& tokens);
    std::string updateTable(const std::vector<std::string>& tokens);
    std::string deleteFrom(const std::vector<std::string>& tokens);
    
    std::vector<std::string> tokenize(const std::string& query);
    std::string formatResults(const std::vector<Record>& records);
};

#endif // QUERY_PROCESSOR_H