#include "min_surface_tools.h"

// Computation on one triangle
void on_one_tri
(
    Eigen::Matrix<double, 3, 3> &r,
    const Eigen::Matrix<double, Eigen::Dynamic, 1> &u_0,
    Triangle t,
    Mesh &m
)
{
    int i, j;
    Eigen::Matrix<double, 2, 1> u, v, n[3];
    Eigen::Matrix<double, 2, 1> c_0;
    Eigen::Matrix<double, 2, 1> c_1;

    //std::cout << t << std::endl;
    //for(int k = 0; k < 3; k++)
    //    std::cout << m.coordinate(t[k]) << std::endl;

    c_0 = Eigen::Matrix<double, 2, 1>(m.coordinate(t[2]));
    c_1 = Eigen::Matrix<double, 2, 1>(m.coordinate(t[1]));
    n[0] = c_0 - c_1;

    c_0 = Eigen::Matrix<double, 2, 1>(m.coordinate(t[0]));
    c_1 = Eigen::Matrix<double, 2, 1>(m.coordinate(t[2]));
    n[1] = c_0 - c_1;

    c_0 = Eigen::Matrix<double, 2, 1>(m.coordinate(t[1]));
    c_1 = Eigen::Matrix<double, 2, 1>(m.coordinate(t[0]));
    n[2] = c_0 - c_1;

    //for(int k = 0; k < 3; k++)
    //    std::cout << "n_" << k << ": \n" << n[k] << std::endl;

    u = (m.coordinate(t[1]) - m.coordinate(t[0])).matrix();
    v = (m.coordinate(t[2]) - m.coordinate(t[0])).matrix();

    double area = std::abs(u(0) * v(1) - u(1) * v(0));

    for(j = 0; j < 3; j++)
        for(i = 0; i < 3; i++)
            r(i, j) = n[j].dot(n[i]);
    double s = 0.;
    for(j = 0; j < 3; j++) {
        s += u_0(t[j]) * u_0(t[j]) * r(j, j);
        for(i = j + 1; i < 3; i++)
            s += 2. * u_0(t[j]) * u_0(t[i]) * r(j, i);
    }
    s = std::sqrt(1. + s);
    r /= s;
    r /= (4. * area);
}

// Product of the matrix and x, the result is stored in r
void prod
(
    Eigen::Matrix<double, Eigen::Dynamic, 1> &r,
    const Eigen::Matrix<double, Eigen::Dynamic, 1> &x,
    const Eigen::Matrix<double, Eigen::Dynamic, 1> &u_0,
    Mesh &m,
    const std::set<int> &on_boundary,
    bool complete
)
{
    int i, j, k;
    int num_tri = m.triangles_count();
    Eigen::Matrix<double, 3, 3> a;
    r = Eigen::Matrix<double, Eigen::Dynamic, 1>::Zero(r.rows());
    for(k = 0; k < num_tri; k++) {
        Triangle t = m.triangle(k);
        on_one_tri(a, u_0, t, m);
        for(i = 0; i < 3; i++) {
            if(on_boundary.find(t[i]) != on_boundary.end()) {
                r(t[i]) = 0.;
                continue;
            }
            for(j = 0; j < 3; j++) {
                if(!complete && on_boundary.find(t[j]) != on_boundary.end())
                    continue;
                r(t[i]) += x(t[j]) * a(j, i);
            }
        }
    }
}

int mst_conjugated_gradient
(
    Eigen::Matrix<double, Eigen::Dynamic, 1> &u,
    const Eigen::Matrix<double, Eigen::Dynamic, 1> &u_0,
    int max_iter,
    double eps,
    Mesh &m,
    const std::set<int> &on_boundary
)
{
    int k = 0;
    double alpha, beta;
    Eigen::Matrix<double, Eigen::Dynamic, 1> r, p, t;
    r = Eigen::Matrix<double, Eigen::Dynamic, 1>::Zero(u.rows());
    t = r;
    prod(r, u, u_0, m, on_boundary, true); // r = A*u-b
    p = r;
    while(r.norm() >= eps && k < max_iter) {
        /*
        std::cout << "u" << std::endl;
        std::cout << u << std::endl;
        std::cout << "r" << std::endl;
        std::cout << r << " " << r.norm() << std::endl;
        std::cout << "p" << std::endl;
        std::cout << p << " " << p.norm() << std::endl;
        // */
        prod(t, p, u_0, m, on_boundary, false); // t = A*p
        beta = r.squaredNorm();
        alpha = beta / p.dot(t);
        u -= alpha * p;
        r -= alpha * t;
        beta = r.squaredNorm() / beta;
        p = r + beta * p;
        //std::cout << "alpha " << alpha << " beta " << beta << std::endl;
        k++;
    }
    return k;
}
