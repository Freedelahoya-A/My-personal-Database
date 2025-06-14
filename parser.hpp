#pragma once
#include <string>
#include <vector>

enum class CommandType { CREATE, INSERT, SELECT, UNKNOWN };

struct Command {
    CommandType type;
    std::string table;
    std::vector<std::string> columns;
    std::vector<std::string> values;
};

Command parseSQL(const std::string& sql);
