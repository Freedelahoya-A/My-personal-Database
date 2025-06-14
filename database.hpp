#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "parser.hpp"

class Database {
public:
    void execute(const Command& cmd);

private:
    struct Table {
        std::vector<std::string> columns;
        std::vector<std::vector<std::string>> rows;
    };

    std::unordered_map<std::string, Table> tables;

    void createTable(const Command& cmd);
    void insertInto(const Command& cmd);
    void selectFrom(const Command& cmd);
};
