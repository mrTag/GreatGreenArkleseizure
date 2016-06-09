#ifndef vector2_h__
#define vector2_h__

#include "libfixmath/fix16.hpp"

namespace gga {
    struct Vector2 {
        Fix16 X;
        Fix16 Y;

		Vector2() : X(0), Y(0) {}
    };
}

#endif // vector2_h__