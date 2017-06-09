#ifndef RECAST_SERVER_STOPCOMMAND_H
#define RECAST_SERVER_STOPCOMMAND_H


#include "ICommand.h"

/**
 * @brief StopCommand
 *
 * @example 'stop'
 */
class StopCommand: public ICommand {
public:
    StopCommand() { }
    bool isValid(std::string &cmd, std::vector<std::string> args);
    void onCommand(ICommandSender &sender, std::string &cmd, std::vector<std::string> args);
};


#endif //RECAST_SERVER_STOPCOMMAND_H
