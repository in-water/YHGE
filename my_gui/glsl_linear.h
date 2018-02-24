#ifndef GLSL_LINEAR_H
#define GLSL_LINEAR_H
#include "yhge_type.h"
#include "vecg.h"
#include "matrix.h"

namespace YHGE {

    typedef vec2g<real> vec2;
    typedef vec3g<real> vec3;
    typedef vec4g<real> vec4;

    typedef Matrix<real, 3> mat3;
    typedef Matrix<real, 4> mat4;


    namespace Numeric {

//        inline bool has_nan(const vec2& v) {
//            return is_nan(v.x) || is_nan(v.y);
//        }

//        inline bool has_nan(const vec3& v) {
//            return is_nan(v.x) || is_nan(v.y) || is_nan(v.z);
//        }

//        inline bool has_nan(const vec4& v) {
//            return is_nan(v.x) || is_nan(v.y) || is_nan(v.z) || is_nan(v.w);
//        }

    }

}
#endif // GLSL_LINEAR_H
