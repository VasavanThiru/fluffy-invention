#include "mesh.h"
#include <iostream>

Mesh::Mesh()
{
}

Mesh::Mesh(std::string &name)
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
    std::cout << "Number of vertices: " << num_vertices << std::endl;
    std::cout << "Number of triangles: " << num_triangles << std::endl;
    coordinates = Eigen::Matrix<double, Eigen::Dynamic, 2>(num_vertices, 2);
    triangles = Eigen::Matrix<int, Eigen::Dynamic, 3>(num_triangles, 3);
    for(i = 0; i < num_vertices; i++)
        file >> coordinates(i, 0) >> coordinates(i, 1) >> tmp;
    for(i = 0; i < num_triangles; i++)
        file >> triangles(i, 0) >> triangles(i, 1) >> triangles(i, 2)
            >> tmp;
    triangles -= 1;
    std::cout << "Vertices" << std::endl << coordinates << std::endl;
    std::cout << "Triangles" << std::endl << triangles << std::endl;
}
