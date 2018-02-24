#ifndef YHGE_TYPE_H
#define YHGE_TYPE_H
//#include <Geex/basics/linkage.h>

#include <string>
#include <vector>

#include <math.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace YHGE {

//____________________________________________________________________________

#ifndef nil
#define nil 0
#endif

    namespace Memory {
        typedef unsigned char  byte ;
        typedef unsigned char  word8 ;
        typedef unsigned short word16 ;
        typedef unsigned int   word32 ;
        typedef byte* pointer ;
        inline void clear(void* addr, size_t size) { ::memset(addr, 0, size) ; }
        template <class T> inline void clear(std::vector<T>& v) { ::memset(&v[0], 0, v.size() * sizeof(T)) ; }
        inline void copy(void* to, const void* from, size_t size) { ::memcpy(to, from, size) ; }
        long  used_memory() ;
    }

//_______________________________________________________________________

/**
 * A namespace gathering typedefs
 * corresponding to numbers. These types
 * names have the form (u)int<size> or float<size>,
 * where the (optional) u denotes an unsigned type,
 * and the size is in bits.
 */

    namespace Numeric {
        typedef char          int8 ;
        typedef short         int16 ;
        typedef int           int32 ;
#ifdef WIN32
        typedef __int64 int64 ;
#else
        typedef long long int int64 ;
#endif
        typedef unsigned char  uint8 ;
        typedef unsigned short uint16 ;
        typedef unsigned int   uint32 ;
#ifdef WIN32
        typedef unsigned __int64 uint64 ;
#else
        typedef unsigned long long int uint64 ;
#endif

        typedef float  float32 ;
        typedef double float64 ;

        extern  const float big_float ;
        extern  const float small_float ;
        extern  const double big_double ;
        extern  const double small_double ;

        int32    random_int32() ;
        float32  random_float32() ;
        float64  random_float64() ;
        bool  is_nan(float32 x) ;
        bool  is_nan(float64 x) ;
    }

    // These ones can be changed according to
    // precision and number of bits in target machine.
    // Note: if moving index_t, signed_index_t and size_t
    // to 64 bits, properties/record_id.h needs to be
    // changed accordingly (to enable 64bits properties
    // management).
    typedef Numeric::float64 real ;
    typedef Numeric::uint32 index_t ;
    typedef Numeric::int32 signed_index_t ;
    typedef Numeric::uint32 size_t ;

    enum { alignment_for_SSE2 = 16} ;

//_______________________________________________________________________

    namespace String {

        void  split_string(
            const std::string& in,
            char separator,
            std::vector<std::string>& out,
            bool skip_empty_fields = true
        ) ;

        void  join_strings(
            const std::vector<std::string>& in,
            char separator,
            std::string& out
        ) ;

        void  join_strings(
            const std::vector<std::string>& in,
            const std::string& separator,
            std::string& out
        ) ;


        std::string  join_strings(
            const std::vector<std::string>& in,
            char separator
        ) ;

        std::string  join_strings(
            const std::vector<std::string>& in,
            const std::string& separator
        ) ;


        void  to_lowercase(std::string& in) ;
        void  to_uppercase(std::string& in) ;

        inline std::string char_to_string(char c) {
            char s[2] ;
            s[0] = c ;
            s[1] = '\0' ;
            return std::string(s) ;
        }

        std::string  quote(const std::string& s, char quotes = '\"') ;

        bool  string_starts_with(const std::string& haystack, const std::string& needle) ;
        bool  string_ends_with(const std::string& haystack, const std::string& needle) ;
    }

//_______________________________________________________________________

    template <class T> inline T gx_max(T x1, T x2) {
        return x1 > x2 ? x1 : x2;
    }

    template <class T> inline T gx_min(T x1, T x2) {
        return x1 < x2 ? x1 : x2;
    }

    enum Sign { NEGATIVE=-1, ZERO=0, POSITIVE=1 } ;

    template <class T> inline Sign gx_sgn(T x) {
        return (x > 0) ? POSITIVE : (
            (x < 0) ? NEGATIVE : ZERO
        );
    }

    template <class T> inline T gx_abs(T x)  {
        return (x > 0) ? x : -x;
    }

    template <class T> inline T gx_sqr(T x)  {
        return x*x;
    }

    template <class T> inline void gx_clamp(T& x, T min, T max) {
        if(x < min) {
            x = min ;
        } else if(x > max) {
            x = max ;
        }
    }

    template <class T> inline void gx_swap(T& x, T& y) {
        T z = x ;
        x = y ;
        y = z ;
    }

}

#endif // TYPE_H
