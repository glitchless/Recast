/**
 * @file
 * @brief CommandManager description
 * @author LionZXY
 * @project Recast-server
 * @date 08.06.17
 *
 * CommandManager description
 * 
 **/
#include <sstream>
#include <iterator>
#include <memory>
#include <vector>
#include "commands/CommandManager.h"
#include "commands/StopCommand.h"

using namespace std;
namespace {
    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::stringstream ss;
        ss.str(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }
}

/**
 * @brief Init CommandManager
 *
 * Adding all objects that extend ICommand to list (std::vector).
 *
 * @warning If you add ICommand, you should add line here
 *
 */
CommandManager::CommandManager() {
    commands.push_back(std::make_shared<StopCommand>());
}


/**
 * @brief call string command.
 *
 * Split string to arguments. Find command and run it.
 *
 * @param sender Link to any class who extend ICommandSender. Like Server, Player and other Context-like object.
 * @param cmd Command in string. @example stop now.
 */
void CommandManager::onCommand(ICommandSender *sender, std::string cmd) {
    std::vector<int> valid;
    vector <string> cmds = split(cmd, ' ');
    vector<string>::const_iterator first = cmds.begin() + 1;
    vector<string>::const_iterator last = cmds.end();
    vector <string> args(first, last);

    for (int i = 0; i < commands.size(); i++)
        if (commands[i]->isValid(cmds[0], args))
            valid.push_back(i);

    if (valid.size() == 0)
        sender->onMessage("Not found command");
    else {
        for (int i = 0; i < valid.size(); i++)
            commands[valid[i]]->onCommand(*sender, cmds[0], args);
    }
}

