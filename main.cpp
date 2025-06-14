#include <iostream>
#include <string>
#include "parser.hpp"
#include "database.hpp"
using namespace std;
int main() {
    Database db;
    string input;

    cout << "Welcome to MiniDB by kaal bhairav" << std::endl;

    while (true) {
        cout << "KB> ";
        getline(std::cin, input);

        if (input == "bye" || input == "BYE" || input == "exit") break;

        auto command = parseSQL(input);
        db.execute(command);
    }

    return 0;
}
