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
    bool isValid(string &cmd, vector<string> args);
    void onCommand(ICommandSender &sender, string &cmd, vector<string> args);
};


#endif //RECAST_SERVER_STOPCOMMAND_H
