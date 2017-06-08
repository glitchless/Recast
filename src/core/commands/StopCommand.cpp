
#include <commands/ICommandSender.h>
#include <commands/StopCommand.h>

using namespace std;

bool StopCommand::isValid(std::string cmd, vector<string> args) {
    return cmd == "stop";
}

void StopCommand::onCommand(ICommandSender &sender, string cmd, vector<string> args) {
    if (!sender.isOP())
        sender.onMessage("У вас нет прав");
    else if (sender.getServer() != NULL)
        sender.getServer()->isRunning = false;
    else
        sender.onMessage("Невозможно получить класс сервера. Обратитесь к разработчикам");
}