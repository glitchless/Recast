/**
 * @file InputThread.cpp
 * @brief Input thread for execute terminal command
 * @author LionZXY
 * @project Recast-server
 * @date 12.06.17
 * @email nikita@kulikof.ru
 *
 * Execute background command
 * 
 **/

#include <string>
#include <iostream>
#include <boost/log/trivial.hpp>
#include "threads/InputThread.h"
#include "Server.h"

using namespace std;

InputThread::InputThread(Server *srv) {
    server = srv;
    BOOST_LOG_TRIVIAL(info) << "Input thread is running...";
}

void InputThread::init() {
    while (server->isRunning()) {
        string cmd = "";
        cin >> cmd;
        manager.onCommand(server, cmd);
    }
}
