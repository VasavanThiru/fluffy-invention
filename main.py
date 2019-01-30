#!/usr/bin/env python

# -*- coding: utf8 -*-

import sys
import math
import numpy as np
import numpy.linalg as LA
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_mesh(filename):
    f = open(filename)
    data = f.read()
    data = data.split('\n')
    del data[-1]
    tmp = data[0].split(' ')
    num_cor = int(tmp[0])
    num_tri = int(tmp[1])
    array = [np.empty([int(num_cor), 3], dtype=np.float32),
             np.empty([int(num_tri), 3], dtype=np.int)]
    for i in range(num_cor):
        a = data[i + 1].split(' ')
        for j in range(3):
            array[0][i][j] = float(a[j])
    for i in range(num_tri):
        a = data[i + num_cor + 1].split(' ')
        for j in range(3):
            array[1][i][j] = int(a[j])
    #array[1] -= 1
    return array

def mesh(x, y, tri):
    fig = plt.figure()
    p = fig.gca().set_aspect('equal')
    plt.triplot(x, y, tri)
    plt.title('Plotting mesh')
    plt.show()

def surface(x, y, z, tri):
    fig = plt.figure()
    #fig.gca().set_aspect('equal')
    #plt.tripcolor(x, y, tri, z, shading="flat")
    #plt.colorbar()
    ax = fig.gca(projection='3d')
    for a in z:
        ax.plot_trisurf(x, y, tri, a)
    plt.title('Plotting a function')
    plt.show()

def area(x, y, z, tri):
    s = 0.
    for i in range(len(tri)):
        t = tri[i]
        u = np.array([x[t[1]] - x[t[0]], y[t[1]] - y[t[0]], z[t[1]] - z[t[0]]])
        v = np.array([x[t[2]] - x[t[0]], y[t[2]] - y[t[0]], z[t[2]] - z[t[0]]])
        s += LA.norm(np.cross(u, v), 2)
    return s / 2

if __name__ == '__main__':
    if len(sys.argv) > 1:
        array = read_mesh(sys.argv[1])
    else:
        array = read_mesh('catenoide.msh')
    #mesh(array[0][:,0], array[0][:,1], array[1])
    z = np.sqrt(array[0][:,0] * array[0][:,0] + array[0][:,1] * array[0][:,1])
    z[z < 1.] = 1.
    for i in range(len(z)):
        z[i] = math.acosh(z[i])
    print('max z', np.max(z))
    #z /= np.max(z)
    a0 = area(array[0][:,0], array[0][:,1], z, array[1])
    a1 = area(array[0][:,0], array[0][:,1], array[0][:,2], array[1])
    print('area z', a0)
    print('area', a1)
    print('diff', a1 - a0)
    print(np.sqrt(np.sum((z - array[0][:,2])**2)))
    surface(array[0][:,0], array[0][:,1], [z], array[1])
    #surface(array[0][:,0], array[0][:,1], [array[0][:,2]], array[1])
    #surface(array[0][:,0], array[0][:,1], [z - array[0][:,2]], array[1])
