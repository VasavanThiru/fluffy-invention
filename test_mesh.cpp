#include <iostream>
#include "mesh.h"

int main()
{
    int i;
    std::string file("mesh.msh");
    Mesh m(file);
    std::cout << "Number of vertices: " << m.vertices_count() << std::endl;
    std::cout << "Number of triangles: " << m.triangles_count() << std::endl;
    for(i = 0; i < m.vertices_count(); i++)
        std::cout << m.coordinate(i) << std::endl;
    for(i = 0; i < m.triangles_count(); i++)
        std::cout << m.triangle(i) << std::endl;
    return 0;
}

