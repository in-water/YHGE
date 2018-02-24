#ifndef TET_STRUCT_H
#define TET_STRUCT_H
#include "meshes.h"
#include <string>
namespace YHGE
{
    class MyTetStruct
    {
    public:
//----------------------------------functions----------------------------------------//
        void load(std::string filename) { boundary_.load(filename); }
        void init_boundary_points(int nb);



//----------------------------------return data--------------------------------------//
        TriMesh					 boundary(){ return boundary_; }
        std::vector<vec3>		 boundary_point(){ return boundary_points_; }
    private:
        TriMesh					 boundary_;
        std::vector<vec3>		 boundary_points_;
    };
}
#endif // TET_STRUCT_H
