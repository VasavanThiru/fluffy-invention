#include "mesh.h"

Mesh::Mesh()
{
}

// Load a mesh
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
    vertices = Eigen::Array<double, Eigen::Dynamic, 2>(num_vertices, 2);
    triangles = Eigen::Array<int, Eigen::Dynamic, 3>(num_triangles, 3);
    for(i = 0; i < num_vertices; i++)
        file >> vertices(i, 0) >> vertices(i, 1) >> tmp;
    for(i = 0; i < num_triangles; i++)
        file >> triangles(i, 0) >> triangles(i, 1) >> triangles(i, 2)
            >> tmp;
    triangles -= 1;
}

Vertex Mesh::vertex(int i)
{
    return vertices.block<1, 2>(i, 0);
}

Triangle Mesh::triangle(int i)
{
    return triangles.block<1, 3>(i, 0);
}

int Mesh::vertices_count() const
{
    return vertices.rows();
}

int Mesh::triangles_count() const
{
    return triangles.rows();
}

std::set<int> Mesh::boundary() const
{
    int i, j;
    std::set<std::set<int> > edge;
    std::set<std::set<int> >::iterator it;
    std::set<int> edge_vertices;
    std::set<int>::iterator vt;
    int num_tri = triangles.rows();

    // find all the edges
    for(i = 0; i < num_tri; i++) {
        std::set<int> s[3];
        s[0].insert(triangles(i, 0));
        s[0].insert(triangles(i, 1));
        s[1].insert(triangles(i, 0));
        s[1].insert(triangles(i, 2));
        s[2].insert(triangles(i, 1));
        s[2].insert(triangles(i, 2));
        for(j = 0; j < 3; j++) {
            it = edge.find(s[j]);
            if(it == edge.end())
                edge.insert(s[j]);
            else
                edge.erase(it);
        }
    }

    for(it = edge.begin(); it != edge.end(); ++it) {
        for(vt = it->begin(); vt != it->end(); ++vt)
            edge_vertices.insert(*vt);
    }
    return edge_vertices;
}

