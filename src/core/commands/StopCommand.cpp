
#include "commands/ICommandSender.hpp"
#include "commands/StopCommand.hpp"
#include "Server.hpp"

using namespace std;

bool StopCommand::isValid(const string &cmd, const vector<string> &args) const {
    return cmd == "stop";
}

void StopCommand::onCommand(ICommandSender &sender, const string &cmd, const vector<string> &args) {
    if (!sender.isOP()) {
        sender.onMessage("Permission error");
    } else if (sender.getServer() != NULL) {
        sender.getServer()->shutdown();
        sender.onMessage("Server stopping...");
    } else {
        sender.onMessage("Unavilable Server class. Contact to developers.");
    }
}