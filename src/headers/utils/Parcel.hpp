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
    ((union {
        T a;
        char bytes[sizeof(T)];
    } *) var)->bytes[number] = byte;
}

template<class T>
char inline getByte(T var, int number) {
    return ((union {
        T a;
        char bytes[sizeof(T)];
    } *) var)->bytes[number];
}

/**
 * @class Parcel
 *
 * Позволяет переводить удобно данные в массив.
 */
class Parcel {
public:
    Parcel();

    Parcel(std::vector<char> vector) : data(vector) {}

    Parcel(Parcel &other) = delete;

    void putString(std::string var);

    template<class T>
    void put(T var) {
        unsigned char const *p = reinterpret_cast<unsigned char const *>(&var);
        for (int i = 0; i < sizeof(T); i++)
            data.push_back((char &&) p[i]);
    }

    int readInt();

    std::string readString();

    float readFloat();

    const std::vector<char> *getVector() const { return &data; }

private:
    int curPos;
    std::vector<char> data;
};


#endif //RECAST_SERIALIZABLE_H
