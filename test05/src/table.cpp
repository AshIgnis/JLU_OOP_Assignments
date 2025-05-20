#include "table.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

Table::Table(const std::string& name, const std::vector<std::pair<std::string, std::string>>& schema)
    : name(name), schema(schema) {}

Table::~Table() {}

bool Table::insert(const std::vector<std::string>& values) {
    if (values.size() != schema.size()) {
        return false; 
    }
    
    Record record(schema);
    for (size_t i = 0; i < values.size(); i++) {
        record.setValue(schema[i].first, values[i]);
    }
    
    records.push_back(record);
    return true;
}

std::vector<Record> Table::select(const std::string& condition) {
    std::vector<Record> result;
    
    for (const auto& record : records) {
        if (condition.empty() || evaluateCondition(record, condition)) {
            result.push_back(record);
        }
    }
    
    return result;
}

bool Table::update(const std::map<std::string, std::string>& values, const std::string& condition) {
    bool updated = false;
    
    for (auto& record : records) {
        if (condition.empty() || evaluateCondition(record, condition)) {
            for (const auto& pair : values) {
                record.setValue(pair.first, pair.second);
            }
            updated = true;
        }
    }
    
    return updated;
}

bool Table::deleteRecords(const std::string& condition) {
    if (condition.empty()) {
        records.clear();
        return true;
    }
    
    size_t initialSize = records.size();
    
    records.erase(
        std::remove_if(records.begin(), records.end(),
            [this, &condition](const Record& record) {
                return evaluateCondition(record, condition);
            }
        ),
        records.end()
    );
    
    return records.size() < initialSize;
}

std::string Table::getName() const {
    return name;
}

std::vector<std::pair<std::string, std::string>> Table::getSchema() const {
    return schema;
}

std::vector<Record> Table::getRecords() const {
    return records;
}

bool Table::save(std::ostream& out) const {
    out << schema.size() << std::endl;
    
    for (const auto& column : schema) {
        out << column.first << " " << column.second << std::endl;
    }
    
    out << records.size() << std::endl;
    
    for (const auto& record : records) {
        record.save(out);
    }
    
    return true;
}

bool Table::load(std::istream& in) {
    records.clear();
    
    int recordCount = 0;
    in >> recordCount;
    in.ignore(); 
    
    for (int i = 0; i < recordCount; i++) {
        Record record(schema);
        record.load(in, schema);
        records.push_back(record);
    }
    
    return true;
}

bool Table::evaluateCondition(const Record& record, const std::string& condition) const {
    size_t pos = condition.find('=');
    if (pos != std::string::npos) {
        std::string column = condition.substr(0, pos);
        std::string value = condition.substr(pos + 1);
        
        column.erase(0, column.find_first_not_of(" \t"));
        column.erase(column.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t'\""));
        value.erase(value.find_last_not_of(" \t'\"") + 1);
        
        return record.getValue(column) == value;
    }
    
    return false;
}