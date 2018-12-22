#include "mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(const std::string &name)
{
    int i, tmp;
    int num_vertices = 0, num_triangles = 0;
    std::fstream file;
    file.open(name, std::fstream::in);
    if(!file.is_open()) {
        std::cerr << "Unable to open file " << name << std::endl;
        return;
    }
    file >> num_vertices >> num_triangles >> tmp;
    coordinates = Eigen::Array<double, Eigen::Dynamic, 2>(num_vertices, 2);
    triangles = Eigen::Array<int, Eigen::Dynamic, 3>(num_triangles, 3);
    for(i = 0; i < num_vertices; i++)
        file >> coordinates(i, 0) >> coordinates(i, 1) >> tmp;
    for(i = 0; i < num_triangles; i++)
        file >> triangles(i, 0) >> triangles(i, 1) >> triangles(i, 2)
            >> tmp;
    triangles -= 1;
}

Coordinate Mesh::coordinate(int i)
{
    return coordinates.block<1, 2>(i, 0);
}

Triangle Mesh::triangle(int i)
{
    return triangles.block<1, 3>(i, 0);
}

int Mesh::vertices_count() const
{
    return coordinates.rows();
}

int Mesh::triangles_count() const
{
    return triangles.rows();
}
