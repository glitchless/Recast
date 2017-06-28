/**
 * @file CreateEntityCommand.h
 * @author LionZXY
 * @project Recast-server
 * @date 27.06.17
 * @email nikita@kulikof.ru
 **/
#ifndef RECAST_SERVER_CREATEENTITYCOMMAND_H
#define RECAST_SERVER_CREATEENTITYCOMMAND_H

#include "commands/ICommand.hpp"

class CreateEntityCommand : public ICommand {
public:
    bool isOnlyUICommand() { return true; }

    bool isValid(const std::string &cmd, const std::vector<std::string> &args) const;

    void onCommand(ICommandSender &sender, const std::string &cmd, const std::vector<std::string> &args);


};


#endif //RECAST_SERVER_CREATEENTITYCOMMAND_H
