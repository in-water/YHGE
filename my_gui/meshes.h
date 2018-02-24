#ifndef MESHES_H
#define MESHES_H
#include <set>
#include "glsl_linear.h"
#include "geometry.h"

namespace YHGE
{
    class Convex :public std::vector < Plane<real> >
    {
    public:
        inline bool contain(const vec3& p)
        {
            for (unsigned int i = 0; i < size(); i++)
            {
                if ((*this)[i].side(p) < 0) { return false; }
            }
            return true;
        }
    };

    class MeshVertex
    {
    public:
        MeshVertex(const vec3& p)
        {
            pos_ = p;
            tex_coord_ = 0.;
        }

        MeshVertex()
        {
            pos_ = vec3(0, 0, 0);
            tex_coord_ = 0;
        }

        vec3& point()    { return pos_; }

    public:
        vec3             pos_;
        std::vector<int> faces_;
        real             tex_coord_;
    };

    class aFacet
    {
    public:
        aFacet(
            const vec3& p1, const vec3& p2, const vec3& p3,
            int e1, int e2, int e3,
            int i1, int i2, int i3
            ){
            vertex[0] = p1;
            vertex[1] = p2;
            vertex[2] = p3;
            edge_flag[0] = e1;
            edge_flag[1] = e2;
            edge_flag[2] = e3;
            vertex_index[0] = i1;
            vertex_index[1] = i2;
            vertex_index[2] = i3;
            face_area = cross(p3 - p1, p2 - p1).length() / 2.0;
        }

        aFacet(
            const vec3& p1, const vec3& p2, const vec3& p3,
            int e1, int e2, int e3
            ){
            vertex[0] = p1;
            vertex[1] = p2;
            vertex[2] = p3;
            edge_flag[0] = e1;
            edge_flag[1] = e2;
            edge_flag[2] = e3;
            face_area = cross(p3 - p1, p2 - p1).length() / 2.0;
        }

        aFacet(
            const vec3& p1, const vec3& p2, const vec3& p3
            ){
            vertex[0] = p1;
            vertex[1] = p2;
            vertex[2] = p3;
            face_area = cross(p3 - p1, p2 - p1).length() / 2.0;
        }

        aFacet()
        {
            face_area = 0;
        }

        vec3 normal() const
        {
            return normalize(cross(vertex[2] - vertex[0], vertex[1] - vertex[0]));
        }

        vec3 xdir() const
        {
            return normalize(vertex[1] - vertex[0]);
        }

        vec3 ydir() const
        {
            return cross(xdir(), normal());
        }

        vec3 org() const
        {
            return vertex[0];
        }

        vec3 center() const
        {
            return 1.0 / 3.0*(vertex[0] + vertex[1] + vertex[2]);
        }

        bool has_vertex(int vidx) { return vertex_index[0] == vidx || vertex_index[1] == vidx || vertex_index[2] == vidx; }
        //bool has_vertex(int vidx) { return vertex_index[0] == vidx || vertex_index[1] == vidx || vertex_index[2] == vidx; }

        int find_edge(int v0, int v1)
        {
            for (int i = 0; i < 3; ++i)
            {
                if ((vertex_index[i] == v0 && vertex_index[(i + 1) % 3] == v1) || (vertex_index[i] == v1 && vertex_index[(i + 1) % 3] == v0))
                    return(i + 2) % 3;
            }
            return -1;
        }

        Plane<real> plane() const { return Plane<real>(vertex[0], normal()); }

        aFacet& operator=(const aFacet& rhs)
        {
            for (int i = 0; i < 3; ++i)
            {
                vertex_index[i] = rhs.vertex_index[i];
                vertex[i] = rhs.vertex[i];
                edge_flag[i] = rhs.edge_flag[i];
            }
            return *this;
        }

        real face_area;
        int vertex_index[3];
        vec3 vertex[3];
        int edge_flag[3];


    };

    class TriMesh :public std::vector < aFacet >
    {
    public:
        TriMesh();
        ~TriMesh();

        void load(const std::string& filename, Convex* planes = nil);
        void load(std::istream& in, Convex* planes = nil);
        void get_bounding_box(vec3& minb, vec3& maxb)
        {
            minb = bbox_[0];
            maxb = bbox_[1];
        }
        void compute_bounding_box();
        bool contains(const vec3& p) const;

        void normalize(vec3& g, double& R, bool disable_normalize_ = false);

        int nb_vertices() const{ return nb_vertices_; }
        MeshVertex& vertex(int idx){ return vertices_[idx]; }
        void add_ver_tex(vec3 p){ vertices_.push_back(MeshVertex(p)); }
        void clear_all()
        {
            clear();
            vertices_.clear();
            nb_vertices_ = 0;
        }

        real total_area() const{ return total_area_; }

        void print_box(){ std::cout << "box is " << bbox_[0] << std::endl << bbox_[1] << std::endl; }

        void load_tri(const std::string& filename);

    protected:
        int                      nb_vertices_;
        std::vector<MeshVertex>  vertices_;
        vec3                     bbox_[2];
        real                     total_area_;

    public:
        int                      samplerate_;
    };
}

#endif // MESHES_H
