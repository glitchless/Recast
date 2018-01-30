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

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/lockfree/queue.hpp>
#include <queue>
#include "utils/DelayCommand.h"

class ICommandSender;

class ICommand;

/**
 * @brief Send string-command through CommandManager
 *
 * This is a very important class. Through this you can execute console-like text commands.
 */
class CommandManager {
public:
    CommandManager();

    CommandManager(const CommandManager &other) = delete;

    void onCommand(ICommandSender *sender, const std::string &cmd);

    void executeDelayedCommandInUI();

private:
    std::vector<std::shared_ptr<ICommand>> commands;
    boost::lockfree::queue<DelayCommand *, boost::lockfree::capacity<10>> delayedCommand;
};


#endif //RECAST_SERVER_COMMANDMANAGER_H
