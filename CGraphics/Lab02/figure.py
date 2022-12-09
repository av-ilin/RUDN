import pygame as pg
import numpy as np
from numpy import sin, cos
from constants import *


class Figure3D:
    def __init__(self, path='config/config_pyramid'):
        self.edges = None
        self.vertices = None
        self.theta = 0
        self.fi = 0
        self.alpha = 0
        self.beta = 0
        self.gamma = 0
        self.zoom = 10
        self.ro = 10
        self.read_config(path)

    def read_config(self, file):
        with open(file, 'r') as file:
            n, k = map(int, file.readline().strip().split())
            self.vertices = np.zeros((n, 3))
            self.edges = np.zeros((k, 2)).astype(int)
            for i in range(n):
                x, y, z = map(float, file.readline().strip().split())
                self.vertices[i][0] = x
                self.vertices[i][1] = y
                self.vertices[i][2] = z
            file.readline()
            for i in range(k):
                e0, e1 = map(int, file.readline().strip().split())
                self.edges[i][0] = e0
                self.edges[i][1] = e1
            self.n = n
            self.k = k

    def update(self, scr, d_fi=0, d_theta=0,
                          d_alpha=0, d_beta=0, d_gamma=0, d_zoom=0):
        self.fi += d_fi
        self.theta += d_theta
        self.alpha += d_alpha
        self.beta += d_beta
        self.gamma += d_gamma
        self.zoom += d_zoom

        vertices = self.world()
        vertices = self.view_o(vertices)
        vertices = self.view_c(vertices)
        vertices = self.clip(vertices)
        self.draw(scr, vertices)

    def world(self):
        v = self.vertices.copy()
        for i in range(3):
            v[:, i] -= (max(v[:, i]) - min(v[:, i])) / 2
        return v

    def view_c(self, vertices):
        ro = self.ro
        fi = np.radians(self.fi)
        theta = np.radians(self.theta)
        v = np.c_[vertices, np.ones(self.n)]
        e = np.array([[-sin(theta), -cos(fi) * cos(theta), -sin(fi) * cos(theta), 0],
                      [ cos(theta), -cos(fi) * sin(theta), -sin(fi) * sin(theta), 0],
                      [          0,               sin(fi),              -cos(fi), 0],
                      [          0,                     0,                    ro, 1]])
        vertices = np.dot(v, e)
        return vertices[:, :3]

    def view_o(self, vertices):
        alpha = self.alpha
        beta = self.beta
        gamma = self.gamma
        oz = np.array([[cos(alpha), sin(alpha), 0],
                       [-sin(alpha), cos(alpha), 0],
                       [0, 0, 1]])
        oy = np.array([[ cos(beta), 0, sin(beta)],
                       [         0, 1,         0],
                       [-sin(beta), 0, cos(beta)]])
        ox = np.array([[1,           0,          0],
                       [0,  cos(gamma), sin(gamma)],
                       [0, -sin(gamma), cos(gamma)]])
        vertices = np.dot(vertices, ox)
        vertices = np.dot(vertices, oy)
        vertices = np.dot(vertices, oz)
        return vertices[:, :3]

    def clip(self, vertices):
        d = self.zoom
        v = vertices[:, :2]
        v[:, 0] *= d / vertices[:, 2]
        v[:, 1] *= d / vertices[:, 2]
        return v

    def draw(self, screen, vertices):
        screen.fill(BLACK)
        #pg.draw.circle(screen, BLUE, (CENTER_X, CENTER_Y), 10)
        for e in self.edges:
            x1 = vertices[e[0]][0] * SCALE + CENTER_X
            y1 = vertices[e[0]][1] * SCALE + CENTER_Y
            x2 = vertices[e[1]][0] * SCALE + CENTER_X
            y2 = vertices[e[1]][1] * SCALE + CENTER_Y
            pg.draw.line(screen, RED, (x1, y1), (x2, y2))
        for v in vertices:
            pg.draw.circle(screen, GREEN, (v[0] * SCALE + CENTER_X, v[1] * SCALE + CENTER_Y), 3)
        #pg.draw.rect(screen, WHITE, [50, 50, 50, 50])