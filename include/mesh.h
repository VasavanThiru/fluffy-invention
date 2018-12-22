#ifndef MESH_H
#define MESH_H

#include <eigen3/Eigen/Dense>
#include <string>
#include <fstream>

class Mesh
{
    public:
    Mesh();
    Mesh(std::string &name);
    private:
    Eigen::Matrix<double, Eigen::Dynamic, 2> coordinates;
    Eigen::Matrix<int, Eigen::Dynamic, 3> triangles;
};

#endif // MESH_H
