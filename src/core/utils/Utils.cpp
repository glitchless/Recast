/**
 * @file Utils.cpp
 * @brief Utils file
 * @author LionZXY
 * @project Recast-server
 * @date 16.06.17
 * @email nikita@kulikof.ru
 *
 * Misc methods
 * 
 **/
#include "utils/Utils.h"

using namespace std;

static const char ALPHANUM[] =
        "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

string genRandomString(const size_t len) {
    std::string randStr;
    randStr.reserve(len);

    for (int i = 0; i < len; ++i) {
        randStr[i] = ALPHANUM[rand() % (sizeof(ALPHANUM) - 1)];
    }

    return randStr;
}