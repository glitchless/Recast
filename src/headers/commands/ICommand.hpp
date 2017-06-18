/**
 * @file
 * @brief Command file
 * @author LionZXY
 * @project Recast-server
 * @date 08.06.17
 *
 * Describe ICommandFile
 * 
 **/
#ifndef RECAST_SERVER_ICOMMAND_H
#define RECAST_SERVER_ICOMMAND_H

#include <string>
#include <vector>
#include "ICommandSender.hpp"

/**
 * @brief Superclass for Command object
 *
 * If you want to create new command you should extend ICommand class and register that in CommandManager constructor
 *
 * @warning Don't forget to register your Command in CommandManager!!!
 *
 */
class ICommand {
public:
    ICommand() {}

    ICommand(const ICommand &other) {}

    virtual bool isValid(const std::string &cmd, const std::vector<std::string> &args) const = 0; //// You should return @var True if this command line satisfied with you.

    /**
     * Run command.
     * @example On command 'stop now 1 2' from Server console this method receives (Server, 'stop'. {'now','1', '2'})
     *
     * @warning ICommandSender is NOT thread-safe. It means @param sender is sent from background thread. If your ICommand needs main thread execution, create an issue. I will create a flag for that command.
     *
     * @param sender context object
     * @param cmd first word in command
     * @param args second and next words in command (Always not null)
     */
    virtual void onCommand(ICommandSender &sender, const std::string &cmd, const std::vector<std::string> &args) = 0;
};


#endif //RECAST_SERVER_ICOMMAND_H
