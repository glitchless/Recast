/**
 * @file NetworkUtils.hpp
 * @brief Basic networking utils header file
 * @author StealthTech
 * @project Recast-server
 * @date 17.06.17
 * @email st3althtech@mail.ru
 *
 **/

#ifndef RECAST_NETWORK_UTILS_HPP
#define RECAST_NETWORK_UTILS_HPP

#include <string>
#include <unistd.h>
#include <memory>
#include <iostream>
#include <sys/socket.h> // socket(), AF_INET/PF_INET
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h>  // inet_aton()
#include <netdb.h>      // gethostbyname
#include <fcntl.h>
#include <boost/log/trivial.hpp>

using namespace std;

const int DEFAULT_PORT_TCP = 1337;
const int DEFAULT_PORT_UDP = 1338;

string int2ipv4(uint32_t ip);
struct sockaddr_in resolve(const char* host, int port);

#endif //RECAST_NETWORK_UTILS_HPP
