/**
 * @file InputThread.h
 * @brief Thread for command file
 * @author LionZXY
 * @project Recast-server
 * @date 12.06.17
 * @email nikita@kulikof.ru
 *
 * Execute console commands in background.
 * 
 **/
#ifndef RECAST_SERVER_INPUTTHREAD_H
#define RECAST_SERVER_INPUTTHREAD_H

#include "commands/CommandManager.hpp"

class Server;

class InputThread {
public:
    InputThread(InputThread &&thr1) { server = thr1.server; }

    InputThread(Server *srv);

    void init();

private:
    Server *server;
    CommandManager manager;
};


#endif //RECAST_SERVER_INPUTTHREAD_H
