#ifndef YHGEGL_H
#define YHGEGL_H
#include "glsl_linear.h"
#include <GL/gl.h>
namespace YHGE
{
    inline void glVertex(const vec2& p) {
        ::glVertex2f( GLfloat(p.x), GLfloat(p.y) ) ;
    }

    inline void glVertex(const vec3& p) {
        ::glVertex3f( GLfloat(p.x), GLfloat(p.y), GLfloat(p.z) ) ;
    }

    inline void glVertex(const vec4& p) {
        ::glVertex4f( GLfloat(p.x), GLfloat(p.y), GLfloat(p.z), GLfloat(p.w) ) ;
    }

    inline void glTexCoord(real s) {
        ::glTexCoord1f( GLfloat(s) ) ;
    }

    inline void glTexCoord(const vec2& p) {
        ::glTexCoord2f( GLfloat(p.x), GLfloat(p.y) ) ;
    }

    inline void glTexCoord(const vec3& p) {
        ::glTexCoord3f( GLfloat(p.x), GLfloat(p.y), GLfloat(p.z) ) ;
    }

    inline void glTexCoord(const vec4& p) {
        ::glTexCoord4f( GLfloat(p.x), GLfloat(p.y), GLfloat(p.z), GLfloat(p.w) ) ;
    }

    inline void glNormal(const vec3& v) {
        ::glNormal3f( GLfloat(v.x), GLfloat(v.y), GLfloat(v.z) ) ;
    }

    inline void glColor(const vec3& c) {
        ::glColor3f( GLfloat(c.x), GLfloat(c.y), GLfloat(c.z) ) ;
    }

    inline void glColor(const vec4& c) {
        ::glColor4f( GLfloat(c.x), GLfloat(c.y), GLfloat(c.z), GLfloat(c.w) ) ;
    }

    inline void glMultiTexCoord(unsigned int unit, real s) {
        glMultiTexCoord1f(GL_TEXTURE0 + unit, (GLfloat)s) ;
    }

    inline void glMultiTexCoord(unsigned int unit, const vec2& v) {
        glMultiTexCoord2f(
            GL_TEXTURE0 + unit,
            GLfloat(v.x),
            GLfloat(v.y)
        ) ;
    }

    inline void glMultiTexCoord(unsigned int unit, const vec3& v) {
        glMultiTexCoord3f(
            GL_TEXTURE0 + unit,
            GLfloat(v.x),
            GLfloat(v.y),
            GLfloat(v.z)
        ) ;
    }

    inline void glMultiTexCoord(unsigned int unit, const vec4& v) {
        glMultiTexCoord4f(
            GL_TEXTURE0 + unit,
            GLfloat(v.x),
            GLfloat(v.y),
            GLfloat(v.z),
            GLfloat(v.w)
        ) ;
    }

}
#endif // YHGEGL_H
