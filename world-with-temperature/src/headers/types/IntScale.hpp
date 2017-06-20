//
// Created by Oleg Morozenkov on 18.06.17.
//

#ifndef RECAST_INTSCALE_H
#define RECAST_INTSCALE_H


/**
 * Type.
 * Represents scale. It can be either upscale or downscale.
 */
struct IntScale {
public:
    enum Mode {
        Upscale, Downscale
    };

    IntScale(int scale, Mode mode) : _scale(scale), _mode(mode) {
    }

    inline int scale() const noexcept {
        return _scale;
    }

    inline Mode mode() const noexcept {
        return _mode;
    }

    inline bool isUpscale() const noexcept {
        return _mode == Upscale;
    }

    inline bool isDownscale() const noexcept {
        return _mode == Downscale;
    }

    template<typename T>
    inline T apply(T value) const noexcept {
        return _mode == Upscale ? value * _scale : value / _scale;
    }

    template<typename T>
    inline T invertApply(T value) const noexcept {
        return _mode == Upscale ? value / _scale : value * _scale;
    }

    inline bool operator==(const IntScale& other) const noexcept {
        return _scale == other._scale && _mode == other._mode;
    }

    inline bool operator!=(const IntScale& other) const noexcept {
        return !(*this == other);
    }

protected:
    int _scale;
    Mode _mode;
};


#endif //RECAST_INTSCALE_H
