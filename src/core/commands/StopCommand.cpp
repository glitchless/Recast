
#include "commands/ICommandSender.h"
#include "commands/StopCommand.h"
#include "Server.h"

using namespace std;

bool StopCommand::isValid(string &cmd, vector<string> args) {
    return cmd == "stop";
}

void StopCommand::onCommand(ICommandSender &sender, string &cmd, vector<string> args) {
    sender.getPlayer();
    if (!sender.isOP())
        sender.onMessage("Permission error");
    else if (sender.getServer() != NULL)
        sender.getServer()->isRunning = false;
    else
        sender.onMessage("Unavilable Server class. Contact to developers.");
}