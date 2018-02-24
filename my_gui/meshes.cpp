#include "meshes.h"
#include "line_stream.h"
#include <fstream>
#include <algorithm>
#include <queue>
#include <assert.h>

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
namespace YHGE
{
    TriMesh::TriMesh()
    {
        nb_vertices_ = 0;
        samplerate_ = 6;
    }
    TriMesh::~TriMesh()
    {
    }

    void TriMesh::load(const std::string& filename, Convex* planes)
    {
        std::cerr << "Loading " << filename << std::endl;
        clear();
        nb_vertices_ = 0;
        vertices_.clear();
        std::ifstream in(filename.c_str());
        if (!in)
        {
            std::cerr << "Could not open " << filename << std::endl;
            return;
        }
        load(in, planes);
    }

    void TriMesh::load(std::istream& input, Convex* planes)
    {
        if (planes != nil) { planes->clear(); }

        LineInputStream in(input);
        std::vector<vec3> vertices;

        while (!in.eof())
        {
            in.get_line();
            std::string keyword;
            in >> keyword;
            if (keyword == "v")
            {
                vec3 p;
                in >> p;
                vertices.push_back(p);
                vertices_.push_back(MeshVertex(p));
                nb_vertices_++;
            }
            else if (keyword == "f")
            {
                std::vector<int> cur_facet;
                while (!in.eol())
                {
                    std::string s;
                    in >> s;
                    if (s.length() > 0)
                    {
                        std::istringstream v_input(s);
                        int index;
                        v_input >> index;
                        if (index < 1 || index >(int)vertices_.size())
                        {
                            std::cerr << "Out of bounds vertex index" << std::endl;
                        }
                        else
                        {
                            cur_facet.push_back(index - 1);
                        }
                        char c;
                        v_input >> c;
                        if (c == '/')
                        {
                            v_input >> index;
                        }
                    }
                }
                if (cur_facet.size() < 3)
                {
                    std::cerr << "facet with less than 3 vertices, ignoring" << std::endl;
                }
                else
                {
                    for (unsigned int i = 1; i<cur_facet.size() - 1; i++)
                    {
                        int id0 = cur_facet[0];
                        int id1 = cur_facet[i];
                        int id2 = cur_facet[i + 1];
                        const vec3& p0 = vertices[id0];
                        const vec3& p1 = vertices[id1];
                        const vec3& p2 = vertices[id2];
                        bool e0 = true;
                        bool e1 = (i == cur_facet.size() - 2);
                        bool e2 = (i == 1);
                        push_back(aFacet(p0, p1, p2, e0, e1, e2, id0, id1, id2));
                        if (i == 1 && planes != nil)
                        {
                            planes->push_back(rbegin()->plane());
                        }
                        vertices_[id0].faces_.push_back((int)size() - 1);
                        vertices_[id1].faces_.push_back((int)size() - 1);
                        vertices_[id2].faces_.push_back((int)size() - 1);
                    }
                }
            }
        }
        std::cout << "nb_vertices: " << nb_vertices_ << "; nb_faces: " << size() << std::endl;

        total_area_ = 0;
        for (int i = 0; i < (*this).size(); ++i)
        {
            total_area_ = total_area_ + (*this)[i].face_area;
        }
    }

    bool TriMesh::contains(const vec3& p) const
    {
        return true;
    }

    void TriMesh::compute_bounding_box()
    {
        bbox_[0] = vec3(1e10, 1e10, 1e10);
        bbox_[1] = vec3(-1e10, -1e10, -1e10);
        for (unsigned int i = 0; i<size(); ++i)
            for (int j = 0; j < 3; ++j)
            {
            bbox_[0][0] = min(bbox_[0][0], (*this)[i].vertex[j][0]);
            bbox_[0][1] = min(bbox_[0][1], (*this)[i].vertex[j][1]);
            bbox_[0][2] = min(bbox_[0][2], (*this)[i].vertex[j][2]);
            bbox_[1][0] = max(bbox_[1][0], (*this)[i].vertex[j][0]);
            bbox_[1][1] = max(bbox_[1][1], (*this)[i].vertex[j][1]);
            bbox_[1][2] = max(bbox_[1][2], (*this)[i].vertex[j][2]);
            }
        bbox_[0] = bbox_[0] * 1.01;
        bbox_[1] = bbox_[1] * 1.01;
    }


    void load_tri(const std::string& filename)
    {

    }
}
