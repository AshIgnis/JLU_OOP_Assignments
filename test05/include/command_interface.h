#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <string>
#include <iostream>
#include "database.h"

class CommandInterface {
public:
    CommandInterface(Database& db);
    void run();

private:
    Database& database;

    void processCommand(const std::string& command);
    void displayHelp();
};

#endif // COMMAND_INTERFACE_H