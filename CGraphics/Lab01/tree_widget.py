from kivy.uix.widget import Widget
from kivy.graphics import *
import numpy as np


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return '(' + str(self.x) + ', ' + str(self.y) + ')'


class PythagoreanTree(Widget):
    def __init__(self, k=12, alpha=45, **kwargs):
        super(PythagoreanTree, self).__init__(**kwargs)
        self.length = 100
        self.a = Point((1000 - self.length) * (1 - alpha/90), (600 - self.length) / 5)
        self.alpha = np.radians(alpha)
        self.fi = np.radians(0)
        self.n = k

    def start(self):
        self.tree(self.a, self.length, self.alpha, self.fi, self.n)

    def tree(self, a, length, alpha, fi, n):
        if n == 0:
            return

        b = Point(a.x + length * np.cos(fi),
                  a.y + length * np.sin(fi))

        c = Point(b.x + length * np.cos(fi + np.pi / 2),
                  b.y + length * np.sin(fi + np.pi / 2))

        d = Point(a.x + length * np.cos(fi + np.pi / 2),
                  a.y + length * np.sin(fi + np.pi / 2))

        length_a = length * np.cos(self.alpha)
        length_b = length * np.cos(np.pi/2 - self.alpha)

        e = Point(d.x + length_a * np.cos(alpha),
                  d.y + length_a * np.sin(alpha))

        with self.canvas:
            Color(1., 0, 0)
            Line(points=[a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y, a.x, a.y])

        with self.canvas:
            Color(1., 0, 0)
            Line(points=[d.x, d.y, e.x, e.y, c.x, c.y])

        self.tree(e, length_b, alpha - np.pi/2 + self.alpha, alpha - np.pi / 2, n - 1)
        self.tree(d, length_a, alpha + self.alpha, alpha, n - 1)