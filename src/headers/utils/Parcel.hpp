/**
 * @file Serializable.cpp
 * @brief Serialization
 * @author LionZXY
 * @project Recast
 * @email nikita@kulikof.ru
 * @date 08.06.17
 *
 * Serialization
 *
 **/

#ifndef RECAST_SERIALIZABLE_H
#define RECAST_SERIALIZABLE_H


#include <vector>
#include <string>

/**
 * @class Parcel
 *
 * Позволяет переводить удобно данные в массив.
 */
class Parcel {
public:
    Parcel(int code);
    Parcel(std::vector<unsigned char> * data);
    ~Parcel();
    Parcel(Parcel &other) = delete;

    int getCode();
    void putString(std::string var);
    template <class T> void put(T var);

    int readInt();
    std::string readString();
    float readFloat();
private:
    int code;
    int curPos;
    std::vector<unsigned char> * data;
};


enum ParcelableIDs{
    USER_PARCE = 0,
    UNKNOWN = 0
};

class ISerializable {
public:
    void write(Parcel in);
    void read(Parcel out);
};

#endif //RECAST_SERIALIZABLE_H