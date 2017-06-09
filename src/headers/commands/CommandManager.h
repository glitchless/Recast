/**
 * @file
 * @brief CommandManager file
 * @author LionZXY
 * @project Recast-server
 * @date 08.06.17
 *
 * Command manager file
 * 
 **/
#ifndef RECAST_SERVER_COMMANDMANAGER_H
#define RECAST_SERVER_COMMANDMANAGER_H


#include "ICommandSender.h"
#include "ICommand.h"

/**
 * @brief Send string-command through CommandManager
 *
 * This is very important class. Through this you can execute console-like text command.
 */
class CommandManager {
public:
    CommandManager();

    CommandManager(CommandManager &other) = delete;

    void onCommand(ICommandSender *sender, const std::string &cmd);

private:
    std::vector<std::shared_ptr<ICommand>> commands;
};


#endif //RECAST_SERVER_COMMANDMANAGER_H
