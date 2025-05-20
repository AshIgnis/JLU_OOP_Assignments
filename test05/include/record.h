#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>
#include <map>

class Record {
public:
    Record(const std::vector<std::pair<std::string, std::string>>& schema);
    
    void setValue(const std::string& field, const std::string& value);
    std::string getValue(const std::string& field) const;
    std::map<std::string, std::string> getAllValues() const;
    
    bool save(std::ostream& out) const;
    bool load(std::istream& in, const std::vector<std::pair<std::string, std::string>>& schema);

private:
    std::map<std::string, std::string> values;
    std::vector<std::pair<std::string, std::string>> schema;
};

#endif // RECORD_H