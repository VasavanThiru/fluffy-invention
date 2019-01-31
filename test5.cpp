#include <iostream>
#include <cmath>
#include "min_surface_tools.h"
#include "mesh.h"

// Q5) cas particulier

double g(double x, double y)
{
    return std::cos(x) * std::cos(y);
}

int main(int argc, char *argv[])
{
    bool initial = false;
    if(argc > 1)
        initial = atoi(argv[1]) > 0;
    std::string filename("mesh.msh");
    Mesh m(filename);
    double eps = 1e-10; // precision of the solution
    int kiter = 1 << 10; // maximun number of iteration
    int k = 0;
    int num_ver = m.vertices_count();
    Eigen::Matrix<double, Eigen::Dynamic, 1> u, u_0;
    Eigen::Matrix<double, Eigen::Dynamic, 1> r;
    u = Eigen::Matrix<double, Eigen::Dynamic, 1>::Zero(num_ver);
    u_0 = u;
    r = u;
    std::set<int> on_boundary = m.boundary();
    std::set<int>::iterator it;

    // Set the value of u on the boundary
    for(it = on_boundary.begin(); it != on_boundary.end(); ++it) {
        Vertex c = m.vertex(*it);
        u(*it) = g(c[0], c[1]);
    }

    // Optimize if initial == false
    while(!initial && k < kiter && (u_0 - u).norm() >= eps) {
        u_0 = u;
        mst_conjugated_gradient(u, u_0, kiter, 1e-9, m, on_boundary); // u = A^(-1)g
        k++;
    }

    //* Print for gnuplot
    for(k = 0; k < num_ver; k++)
        std::cout << m.vertex(k) << " " << u(k) << std::endl;
    // */
    /* Print for the Python script
    std::cout << m.vertices_count() << " " << m.triangles_count() << std::endl;
    for(k = 0; k < m.vertices_count(); k++)
        std::cout << m.vertex(k) << " " << u(k) << std::endl;
    for(k = 0; k < m.triangles_count(); k++)
        std::cout << m.triangle(k) << std::endl;
    // */
    return 0;
}

