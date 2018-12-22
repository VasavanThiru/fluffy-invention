#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <fstream>
#include <eigen3/Eigen/Dense>

typedef Eigen::Array<double, Eigen::Dynamic, 2> Coordinates;
typedef Eigen::Array<int, Eigen::Dynamic, 3> Triangles;
typedef Eigen::DenseBase<Eigen::Array<double, Eigen::Dynamic, 2> >::FixedBlockXpr<1, 2>::Type Coordinate;
typedef Eigen::DenseBase<Triangles>::FixedBlockXpr<1, 3>::Type Triangle;

class Mesh
{
    public:
    Mesh();
    Mesh(const std::string &name);
    Coordinate coordinate(int i);
    Triangle triangle(int i);
    int vertices_count() const;
    int triangles_count() const;
    private:
    Coordinates coordinates;
    Triangles triangles;
};

#endif // MESH_H
