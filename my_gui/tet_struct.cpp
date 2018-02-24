#include "tet_struct.h"
#include "geometry.h"

namespace YHGE
{
    void MyTetStruct::init_boundary_points(int nb)
    {
        boundary_points_.clear();
        real totalw = 0.;
        real res = 0.;
        int check = 0;
        for (unsigned int i = 0; i < boundary_.size(); ++i)
        {
            totalw = totalw + boundary_[i].face_area;
        }
        for (unsigned int i = 0; i < boundary_.size(); ++i)
        {
            real nf = nb*boundary_[i].face_area / totalw;
            int n = int(nf + res + 0.0000001);
            res = nf + res - n;
            if (n >= 1)
            {
                check += n;
                vec3 v0 = boundary_[i].vertex[0];
                vec3 v1 = boundary_[i].vertex[1];
                vec3 v2 = boundary_[i].vertex[2];
                for (int j = 0; j < n; ++j)
                {
                    vec3 p=sample_tri(v0, v1, v2);
                    boundary_points_.push_back(p);
                }
            }
        }
        std::cout<<"Initial "<<nb<<" points"<<std::endl;
    }

}
