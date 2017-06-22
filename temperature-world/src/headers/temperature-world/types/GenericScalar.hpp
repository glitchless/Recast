//
// Created by Oleg Morozenkov on 14.06.17.
//

#ifndef RECAST_GENERICSCALAR_H
#define RECAST_GENERICSCALAR_H


/**
 * Template for structs that wrap fundamental types. You can consider it as medium-strong typedef.
 *
 * @tparam T Underlying type.
 */
template<typename T>
struct GenericScalar {
public:
    GenericScalar(T value) : _value(value) {
    }

    inline operator T() const noexcept {
        return _value;
    }

    inline operator T&() noexcept {
        return _value;
    }

protected:
    T _value;
};


#endif //RECAST_GENERICSCALAR_H
