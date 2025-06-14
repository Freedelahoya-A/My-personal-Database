#include "database.hpp"
#include <iostream>

void Database::execute(const Command& cmd) {
    switch (cmd.type) {
        case CommandType::CREATE:
            createTable(cmd);
            break;
        case CommandType::INSERT:
            insertInto(cmd);
            break;
        case CommandType::SELECT:
            selectFrom(cmd);
            break;
        default:
            std::cerr << "Unknown or unsupported command.\n";
            break;
    }
}

void Database::createTable(const Command& cmd) {
    if (tables.find(cmd.table) != tables.end()) {
        std::cerr << "Table already exists.\n";
        return;
    }

    Table t;
    t.columns = cmd.columns;
    tables[cmd.table] = t;
    std::cout << "Table '" << cmd.table << "' created.\n";
}

void Database::insertInto(const Command& cmd) {
    if (tables.find(cmd.table) == tables.end()) {
        std::cerr << "Table not found.\n";
        return;
    }

    if (cmd.values.size() != tables[cmd.table].columns.size()) {
        std::cerr << "Column/value count mismatch.\n";
        return;
    }

    tables[cmd.table].rows.push_back(cmd.values);
    std::cout << "Row inserted.\n";
}

void Database::selectFrom(const Command& cmd) {
    if (tables.find(cmd.table) == tables.end()) {
        std::cerr << "Table not found.\n";
        return;
    }

    auto& table = tables[cmd.table];
    for (auto& col : table.columns) std::cout << col << "\t";
    std::cout << "\n";

    for (auto& row : table.rows) {
        for (auto& val : row) std::cout << val << "\t";
        std::cout << "\n";
    }
}
