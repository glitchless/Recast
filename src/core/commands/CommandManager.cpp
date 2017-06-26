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
#include "commands/CommandManager.hpp"
#include "commands/StopCommand.hpp"

using namespace std;

namespace {
    template<typename Out>
    void split(const string &s, char delim, Out result) {
        stringstream ss;
        ss.str(s);
        string item;
        while (getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    vector<string> split(const string &s, char delim) {
        vector<string> elems;
        split(s, delim, back_inserter(elems));
        return elems;
    }
}

/**
 * @brief Init CommandManager
 *
 * Adding all objects that extend ICommand to list (std::vector).
 *
 * @warning If you add an ICommand, you should add line here
 *
 */
CommandManager::CommandManager() {
    commands.push_back(make_shared<StopCommand>());
}


/**
 * @brief call string command.
 *
 * Split string to arguments. Find command and run it.
 *
 * @param sender Link to any class that extends ICommandSender. Like Server, Player and other Context-like object.
 * @param cmd Command in string. @example stop now.
 */
void CommandManager::onCommand(ICommandSender *sender, const std::string &cmd) {
    vector<int> valid;
    vector<string> cmds = split(cmd, ' ');
    auto first = cmds.begin() + 1;
    auto last = cmds.end();
    vector<string> args(first, last);

    for (int i = 0; i < commands.size(); i++) {
        if (commands[i]->isValid(cmds[0], args)) {
            if (commands[i]->isOnlyUICommand())
                delayedCommand.push(new DelayCommand(sender, commands[i], cmds[0], args));
            else
                valid.push_back(i);
        }
    }

    if (valid.size() == 0) {
        sender->onMessage("Not found command");
    } else {
        for (int i = 0; i < valid.size(); i++) {
            commands[valid[i]]->onCommand(*sender, cmds[0], args);
        }
    }
}

using namespace std;

void CommandManager::executeDelayedCommandInUI() {
    DelayCommand *delayCommand;
    while (!delayedCommand.empty() && delayedCommand.pop(delayCommand)) {
        delayCommand->execute();
        delete delayCommand;
    }
}

