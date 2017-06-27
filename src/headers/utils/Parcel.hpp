/**
 * @file Parcel.hpp
 * @brief Serialization Parcel class header file
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

template<class T>
void inline setByte(char byte, int number, T *var) {
    *(char *) (((void *) var) + number) = byte;
}

template<class T>
char inline getByte(T var, int number) {
    return (char) ((var >> ((sizeof(T) - number - 1) * 8)) & 255);
}

/**
 * @class Parcel
 *
 * Позволяет переводить удобно данные в массив.
 */
class Parcel {
public:
    Parcel(int code);

    Parcel(std::vector<char> *data);

    ~Parcel();

    Parcel(Parcel &other) = delete;

    int getCode();

    void putString(std::string var);

    template<class T>
    void put(T var) {
        unsigned char const * p = reinterpret_cast<unsigned char const *>(&var);
        for (int i = 0; i < sizeof(T); i++)
            data->push_back((char &&) p[i]);
    }

    int readInt();

    std::string readString();

    float readFloat();

private:
    int code;
    int curPos;
    std::vector<char> *data;
};


enum ParcelableIDs {
    USER_PARCE = 0,
    UNKNOWN = 0
};

#endif //RECAST_SERIALIZABLE_H
