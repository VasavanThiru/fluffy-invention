#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <eigen3/Eigen/Dense>

typedef Eigen::Array<double, Eigen::Dynamic, 2> Vertices;
typedef Eigen::Array<int, Eigen::Dynamic, 3> Triangles;
typedef Eigen::DenseBase<Vertices>::FixedBlockXpr<1, 2>::Type Vertex;
typedef Eigen::DenseBase<Triangles>::FixedBlockXpr<1, 3>::Type Triangle;

class Mesh
{
    public:
    Mesh();
    Mesh(const std::string &name);
    Vertex vertex(int i);
    Triangle triangle(int i);
    int vertices_count() const;
    int triangles_count() const;
    std::set<int> boundary() const;
    private:
    Vertices vertices;
    Triangles triangles;
};

#endif // MESH_H
