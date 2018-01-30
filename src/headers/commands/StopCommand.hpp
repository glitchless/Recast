#ifndef RECAST_SERVER_STOPCOMMAND_H
#define RECAST_SERVER_STOPCOMMAND_H


#include "ICommand.hpp"

/**
 * @brief StopCommand
 *
 * @example 'stop'
 */
class StopCommand: public ICommand {
public:
    bool isValid(const std::string &cmd, const std::vector<std::string> &args) const;
    void onCommand(ICommandSender &sender, const std::string &cmd, const std::vector<std::string> &args);

};


#endif //RECAST_SERVER_STOPCOMMAND_H
