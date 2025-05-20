#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <map>
#include "record.h"

class Table {
public:
    Table(const std::string& name, const std::vector<std::pair<std::string, std::string>>& schema);
    ~Table();

    bool insert(const std::vector<std::string>& values);
    std::vector<Record> select(const std::string& condition = "");
    bool update(const std::map<std::string, std::string>& values, const std::string& condition = "");
    bool deleteRecords(const std::string& condition = "");
    
    std::string getName() const;
    std::vector<std::pair<std::string, std::string>> getSchema() const;
    std::vector<Record> getRecords() const;
    
    bool save(std::ostream& out) const;
    bool load(std::istream& in);

private:
    std::string name;
    std::vector<std::pair<std::string, std::string>> schema;
    std::vector<Record> records;
    
    bool evaluateCondition(const Record& record, const std::string& condition) const;
};

#endif // TABLE_H