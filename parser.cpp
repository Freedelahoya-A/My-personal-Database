#include "parser.hpp"
#include <sstream>
#include <algorithm>

static void trim(std::string &s) {
    s.erase(remove_if(s.begin(), s.end(), isspace), s.end());
}

Command parseSQL(const std::string& sql_raw) {
    std::string sql = sql_raw;
    std::transform(sql.begin(), sql.end(), sql.begin(), ::toupper);

    Command cmd;
    if (sql.find("CREATE TABLE") == 0) {
        cmd.type = CommandType::CREATE;
        auto name_start = sql.find("TABLE") + 6;
        auto paren_start = sql.find("(", name_start);
        cmd.table = sql.substr(name_start, paren_start - name_start);

        auto cols = sql.substr(paren_start + 1, sql.find(")") - paren_start - 1);
        std::istringstream ss(cols);
        std::string col;
        while (getline(ss, col, ',')) {
            trim(col);
            cmd.columns.push_back(col);
        }

    } else if (sql.find("INSERT INTO") == 0) {
        cmd.type = CommandType::INSERT;
        auto name_start = sql.find("INTO") + 5;
        auto values_start = sql.find("VALUES");
        cmd.table = sql.substr(name_start, values_start - name_start);

        auto vals = sql.substr(sql.find("(", values_start) + 1);
        vals = vals.substr(0, vals.find(")"));
        std::istringstream ss(vals);
        std::string val;
        while (getline(ss, val, ',')) {
            trim(val);
            cmd.values.push_back(val);
        }

    } else if (sql.find("SELECT") == 0) {
        cmd.type = CommandType::SELECT;
        auto from_pos = sql.find("FROM");
        cmd.table = sql.substr(from_pos + 5);
    } else {
        cmd.type = CommandType::UNKNOWN;
    }

    trim(cmd.table);
    return cmd;
}
