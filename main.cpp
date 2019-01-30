#include <iostream>
#include <cmath>
#include "min_surface_tools.h"
#include "mesh.h"

double g(double x, double y)
{
    /*
    if(std::abs(x + M_PI) < 0.01 && std::abs(y + M_PI) < 0.01)
        return 1.;
    else
        return 0.;
    // */
    /*
    //double r = std::sqrt(M_PI * M_PI - x * x);
    double r = M_PI * std::sqrt(1. - std::pow(x / M_PI, 2));
    if(r != r)
        r = 0.;
    return r;
    // */
    //return std::cos(x) * std::cos(y);
    //return M_PI * std::sin(1. * x) + M_PI * std::sin(1. * y);
    //return 1.;
    //*
    if(x * x + y * y < 1.5 * 1.5)
        return 0.;
    else
        return 1.3169578969248166;
    // */
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
    int k = 0, l;
    int num_cor = m.vertices_count();
    Eigen::Matrix<double, Eigen::Dynamic, 1> u, u_0;
    Eigen::Matrix<double, Eigen::Dynamic, 1> r;
    u = Eigen::Matrix<double, Eigen::Dynamic, 1>::Zero(num_cor);
    u_0 = u;
    r = u;
    std::set<int> on_boundary = m.boundary();
    std::set<int>::iterator it;

    // Set the value of u on the boundary
    for(it = on_boundary.begin(); it != on_boundary.end(); ++it) {
        Coordinate c = m.coordinate(*it);
        u(*it) = g(c[0], c[1]);
    }

    // Optimize if initial == false
    while(!initial && k < kiter && (u_0 - u).norm() >= eps) {
        u_0 = u;
        l = mst_conjugated_gradient(u, u_0, kiter, 1e-9, m, on_boundary); // u = A^(-1)g
        prod(r, u, u_0, m, on_boundary, true); // r = A*u-b
        //std::cout << "k " << k << " " << l << " " << r.norm() << " "
        //    << (u_0 - u).norm() << std::endl;
        k++;
    }

    /* Print for gnuplot
    for(k = 0; k < num_cor; k++)
        std::cout << m.coordinate(k) << " " << u(k) << std::endl;
    // */
    //* Print for the Python script
    std::cout << m.vertices_count() << " " << m.triangles_count() << std::endl;
    for(k = 0; k < m.vertices_count(); k++)
        std::cout << m.coordinate(k) << " " << u(k) << std::endl;
    for(k = 0; k < m.triangles_count(); k++)
        std::cout << m.triangle(k) << std::endl;
    // */
    return 0;
}

