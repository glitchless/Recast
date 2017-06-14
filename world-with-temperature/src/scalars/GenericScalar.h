//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_GENERICSCALAR_H
#define RECAST_GENERICSCALAR_H


template<typename T>
struct GenericScalar {
public:
    GenericScalar(T value) : _value(value) {
    }

    inline operator T() const {
        return _value;
    }

    inline operator T&() {
        return _value;
    }

private:
    T _value;
};


#endif //RECAST_GENERICSCALAR_H
