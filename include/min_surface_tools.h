#ifndef MIN_SURFACE_TOOLS
#define MIN_SURFACE_TOOLS

#include <eigen3/Eigen/SparseCore>
#include "mesh.h"

void on_one_tri
(
    Eigen::Matrix<double, 3, 3> &r,
    const Eigen::Matrix<double, Eigen::Dynamic, 1> &u_0,
    Triangle t,
    Mesh &m
);

void prod
(
    Eigen::Matrix<double, Eigen::Dynamic, 1> &r,
    const Eigen::Matrix<double, Eigen::Dynamic, 1> &x,
    const Eigen::Matrix<double, Eigen::Dynamic, 1> &u_0,
    Mesh &m,
    const std::set<int> &on_boundary,
    bool complete
);

int mst_conjugated_gradient
(
    Eigen::Matrix<double, Eigen::Dynamic, 1> &u,
    const Eigen::Matrix<double, Eigen::Dynamic, 1> &u_0,
    int max_iter,
    double eps,
    Mesh &m,
    const std::set<int> &on_boundary
);

#endif // MIN_SURFACE_TOOLS

