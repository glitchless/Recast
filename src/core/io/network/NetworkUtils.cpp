/**
 * @file NetworkUtils.cpp
 * @brief Basic networking utils source file
 * @author StealthTech
 * @project Recast-server
 * @date 17.06.17
 * @email st3althtech@mail.ru
 *
 **/

#include <cstring>
#include "io/network/NetworkUtils.hpp"

using namespace std;
string int2ipv4(uint32_t ip) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "%u.%u.%u.%u", ip&0xFF, (ip&0xFF00) >> 8, (ip&0xFF0000) >> 16, (ip&0xFF000000) >> 24);
    return buffer;
}

struct sockaddr_in resolve(const char* host, int port) {
    struct hostent* hp = gethostbyname(host);
    if (NULL == hp) {
        throw runtime_error("An exception occurred (resolve error): " + string(strerror(errno)));
    }

    char** pAddress = hp->h_addr_list;
    while(*pAddress) {
        unsigned char *ipf = reinterpret_cast<unsigned char*>(*pAddress);
        uint32_t cur_interface_ip = 0;
        uint8_t *rimap_local_ip_ptr = reinterpret_cast<uint8_t*>(&cur_interface_ip);
        rimap_local_ip_ptr[0] = ipf[0];
        rimap_local_ip_ptr[1] = ipf[1];
        rimap_local_ip_ptr[2] = ipf[2];
        rimap_local_ip_ptr[3] = ipf[3];
        cerr << "Resolved successfully: " << int2ipv4(cur_interface_ip) << endl;
        ++pAddress;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    memcpy(&address.sin_addr, hp->h_addr, hp->h_length);

    return address;
}
