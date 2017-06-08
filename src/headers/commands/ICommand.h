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
#include "ICommandSender.h"

using namespace std;

/**
 * @brief Superclass for Command object
 *
 * If you want create new command you should extend ICommand class and register this in CommandManager constructor
 *
 * @warning Don't forget register your Command in CommandManager!!!
 *
 */
class ICommand {
public:
    ICommand() {}

    ICommand(ICommand &other) {}

    virtual bool isValid(string cmd, vector<string> args) = 0; //// You should return @var True if this command line satisfied with you.

    /**
     * Run command.
     * @example On command 'stop now 1 2' from Server console this method recieve (Server, 'stop'. {'now','1', '2'})
     *
     * @param sender context object
     * @param cmd first word in command
     * @param args second and next word in command (Always not null)
     */
    virtual void onCommand(ICommandSender &sender, string cmd, vector<string> args) = 0;
};


#endif //RECAST_SERVER_ICOMMAND_H
