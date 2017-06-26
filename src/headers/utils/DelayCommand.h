/**
 * @file DelayCommand.h
 * @author LionZXY
 * @project Recast-server
 * @date 26.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_DELAYCOMMAND_H
#define RECAST_SERVER_DELAYCOMMAND_H

#include <string>
#include <commands/ICommand.hpp>

class ICommandSender;

class DelayCommand {
public:
    DelayCommand() {}

    DelayCommand(ICommandSender *sender, std::shared_ptr<ICommand> command, std::string cmd,
                 std::vector<std::string> args) : sender(
            sender), command(command), cmd(cmd), args(args) {}

    void execute() {
        command->onCommand(*sender, cmd, args);
    }

private:
    ICommandSender *sender;
    std::shared_ptr<ICommand> command;
    std::string cmd;
    std::vector<std::string> args;
};


#endif //RECAST_SERVER_DELAYCOMMAND_H
