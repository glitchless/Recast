/**
 * @file Parcel.cpp
 * @brief Serialization Parcel class source file
 * @author LionZXY
 * @project Recast
 * @email nikita@kulikof.ru
 * @date 08.06.17
 *
 * Serialization
 *
 **/

#include "utils/Parcel.hpp"

template<class T>
char inline getByte(T var, int number);

template<class T>
void inline setByte(char byte, int number, T *var);

Parcel::Parcel() {
    curPos = sizeof(int);
}

int Parcel::readInt() {
    int var = 0;
    for (int i = 0; i < sizeof(int); i++, curPos++) {
        setByte(data[curPos], i, &var);
    }
    return var;
}

std::string Parcel::readString() {
    std::string str;
    char tmp;
    while ((tmp = data[curPos++]) != '\0') {
        str.push_back(tmp);
    }
    return str;
}

float Parcel::readFloat() {
    float var = 0;
    for (int i = 0; i < sizeof(float); i++, curPos++) {
        setByte(data[curPos], i, &var);
    }
    return var;
}

void Parcel::putString(std::string var) {
    for (size_t i = 0; i < var.length(); i++)
        data.push_back((char) var.at(i));
    data.push_back('\0');
}

