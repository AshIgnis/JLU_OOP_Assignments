#include "record.h"
#include <stdexcept>
#include <iostream>

Record::Record(const std::vector<std::pair<std::string, std::string>>& schema) : schema(schema) {
    for (const auto& column : schema) {
        values[column.first] = "";
    }
}

void Record::setValue(const std::string& field, const std::string& value) {
    if (values.find(field) == values.end()) {
        throw std::runtime_error("字段 '" + field + "' 不存在");
    }
    
    values[field] = value;
}

std::string Record::getValue(const std::string& field) const {
    auto it = values.find(field);
    if (it == values.end()) {
        throw std::runtime_error("字段 '" + field + "' 不存在");
    }
    
    return it->second;
}

std::map<std::string, std::string> Record::getAllValues() const {
    return values;
}

bool Record::save(std::ostream& out) const {
    for (const auto& column : schema) {
        out << values.at(column.first) << std::endl;
    }
    
    return true;
}

bool Record::load(std::istream& in, const std::vector<std::pair<std::string, std::string>>& schema) {
    for (const auto& column : schema) {
        std::string value;
        std::getline(in, value);
        values[column.first] = value;
    }
    
    return true;
}