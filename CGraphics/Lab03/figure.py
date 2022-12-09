import pygame as pg
import numpy as np
from numpy import sin, cos
from constants import *
from dash_line import dashed_line


class Figure3D:
    def __init__(self, path='config/config_pyramid'):
        self.view_hide = True
        self.algorithm = True
        self.n_faces = None
        self.n_edges = None
        self.n_vertices = None
        self.edges = None
        self.vertices = None
        self.faces = None
        self.theta = 0
        self.fi = 0
        self.alpha = 0
        self.beta = 0
        self.gamma = 0
        self.zoom = 10
        self.ro = 10
        self.read_config(path)
        self.camera_center, self.barycenter = None, None

    def read_config(self, file):
        with open(file, 'r') as file:
            k, n, m = map(int, file.readline().strip().split())
            self.n_vertices = k
            self.n_edges = n
            self.n_faces = m
            self.vertices = np.zeros((k, 3))
            self.edges = np.zeros((n, 2)).astype(int)
            self.faces = [[] for _ in range(m)]
            for i in range(k):
                x, y, z = map(float, file.readline().strip().split())
                self.vertices[i][0] = x
                self.vertices[i][1] = y
                self.vertices[i][2] = z
            file.readline()
            for i in range(n):
                e0, e1 = map(int, file.readline().strip().split())
                self.edges[i][0] = e0
                self.edges[i][1] = e1
            file.readline()
            for i in range(m):
                self.faces[i] = [int(p) for p in file.readline().strip().split()]

    def update(self, scr, d_fi=0, d_theta=0,
               d_alpha=0, d_beta=0, d_gamma=0, d_zoom=0):
        self.fi += d_fi
        self.theta += d_theta
        self.alpha += d_alpha
        self.beta += d_beta
        self.gamma += d_gamma
        self.zoom += d_zoom

        vertices = self.world()
        vertices = self.view_axis(vertices)
        vertices = self.view_camera(vertices)
        if self.algorithm:
            visible = self.visible_alg1(vertices)
        else:
            visible = self.visible_alg2()
        vertices = self.clip(vertices)
        self.draw(scr, vertices, visible)

    def world(self):
        v = self.vertices.copy()
        for i in range(3):
            v[:, i] -= (max(v[:, i]) - min(v[:, i])) / 2
        return v

    def view_camera(self, vertices):
        ro = self.ro
        fi = np.radians(self.fi)
        theta = np.radians(self.theta)
        v = np.c_[vertices, np.ones(self.n_vertices)]
        e = np.array([[-sin(theta), -cos(fi) * cos(theta), -sin(fi) * cos(theta), 0],
                      [cos(theta), -cos(fi) * sin(theta), -sin(fi) * sin(theta), 0],
                      [0, sin(fi), -cos(fi), 0],
                      [0, 0, ro, 1]])
        vertices = np.dot(v, e)
        self.camera_center = np.array([ro * sin(fi) * cos(theta),
                                       ro * sin(fi) * sin(theta),
                                       ro * cos(fi)])
        return vertices[:, :3]

    def view_axis(self, vertices):
        alpha = self.alpha
        beta = self.beta
        gamma = self.gamma
        oz = np.array([[cos(alpha), sin(alpha), 0],
                       [-sin(alpha), cos(alpha), 0],
                       [0, 0, 1]])
        oy = np.array([[cos(beta), 0, sin(beta)],
                       [0, 1, 0],
                       [-sin(beta), 0, cos(beta)]])
        ox = np.array([[1, 0, 0],
                       [0, cos(gamma), sin(gamma)],
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

    def visible_alg1(self, vertices):
        visible = np.full(self.n_faces, False)
        for i, face in enumerate(self.faces):
            x, y, z = vertices[face[:3]]
            h = x[0] * y[2] * z[1] + x[1] * y[0] * z[2] + x[2] * y[1] * z[0] - \
                x[0] * y[1] * z[2] - x[1] * y[2] * z[0] - x[2] * y[0] * z[1]
            visible[i] = h < 0
        return visible

    def visible_alg2(self):
        barycenter = self.vertices.sum(axis=0) / self.vertices.shape[0]
        camera_center = self.camera_center
        visible = np.full(self.n_faces, False)
        for i, face in enumerate(self.faces):
            face_center = self.vertices[face[:3]].sum(axis=0) / 3
            x, y, z = self.vertices[face[:3]]
            A, B, C = np.cross((x - y), (x - z))
            D = x[0] * y[2] * z[1] + x[1] * y[0] * z[2] + x[2] * y[1] * z[0] - \
                x[0] * y[1] * z[2] - x[1] * y[2] * z[0] - x[2] * y[0] * z[1]
            e = np.array([A, B, C])
            e *= np.sign((e * barycenter).sum() + D)
            d = face_center - camera_center
            gamma = np.dot(d, e) / np.linalg.norm(d) / np.linalg.norm(e)
            visible[i] = 0 < gamma < 1
        return visible

    def draw(self, screen, vertices, visible):
        screen.fill(BLACK)

        visible_edges = set()
        for i, vis in enumerate(visible):
            if vis:
                visible_edges |= {(self.faces[i][j - 1], self.faces[i][j]) for j in range(len(self.faces[i]))}

        for e in self.edges:
            x1 = vertices[e[0], 0] * SCALE + CENTER_X
            y1 = vertices[e[0], 1] * SCALE + CENTER_Y
            x2 = vertices[e[1], 0] * SCALE + CENTER_X
            y2 = vertices[e[1], 1] * SCALE + CENTER_Y
            if ((e[0], e[1]) in visible_edges) or ((e[1], e[0]) in visible_edges):
                pg.draw.line(screen, RED, (x1, y1), (x2, y2))
            elif self.view_hide:
                dashed_line(screen, RED, (x1, y1), (x2, y2), dash_length=7)

        if self.view_hide:
            for v in vertices:
                pg.draw.circle(screen, BLUE, (v[0] * SCALE + CENTER_X, v[1] * SCALE + CENTER_Y), 3)

    def change_view_mode(self):
        self.view_hide = not self.view_hide

    def change_algorithm(self):
        self.algorithm = not self.algorithm
