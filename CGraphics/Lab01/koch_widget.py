from kivy.uix.widget import Widget
from kivy.graphics import *
from kivy.clock import Clock
import numpy as np


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class KochWidget(Widget):
    def __init__(self, k, **kwargs):
        super(KochWidget, self).__init__(**kwargs)
        self.points = np.array([0, 0, 0.5, 0.5 * 3 ** 0.5, 1, 0, 0, 0])
        self.points *= 300
        self.points[::2] += 350
        self.points[1::2] += 200
        self.k = 0

    def start(self):
        self.draw()
        Clock.schedule_interval(self.play, 2)

    def draw(self):
        self.canvas.clear()
        with self.canvas:
            Color(1., 0, 0)
            Line(points=list(self.points), width=1)

    def play(self, _):
        if self.k < 6:
            self.koch()
            self.draw()
            self.k += 1

    def koch(self):
        points = [(self.points[i], self.points[i + 1]) for i in range(0, len(self.points) - 1, 2)]
        segments = [(points[i], points[i + 1]) for i in range(len(points) - 1)]
        points = []
        for segment in segments:
            x1, y1 = segment[0]
            x2, y2 = segment[1]
            dx = (x2 - x1) / 3
            dy = (y2 - y1) / 3
            points += [x1, y1]
            points += [x1 + dx, y1 + dy]
            points += [(x2 + x1) / 2 + (y1 - y2) / (2 * 3 ** 0.5), (y2 + y1) / 2 + (x2 - x1) / (2 * 3 ** 0.5)]
            points += [x1 + 2 * dx, y1 + 2 * dy]
            points += [x2, y2]

        self.points = np.array(points)


class KochWidgetR(Widget):
    def __init__(self, k=8, **kwargs):
        super(KochWidgetR, self).__init__(**kwargs)
        self.a = Point(0, 10)
        self.b = Point(1000, 10)
        self.fi = 0
        self.n = k

    def start(self):
        self.koch(self.a, self.b, self.fi, self.n)

    def koch(self, a, b, fi, n):
        if n <= 0:
            with self.canvas:
                Color(1., 0, 0)
                Line(points=[a.x, a.y, b.x, b.y], width=1)
            return

        length = ((a.x - b.x) ** 2 + (a.y - b.y) ** 2) ** 0.5
        dl = length / 3

        a1 = Point(a.x + dl * np.cos(fi),
                   a.y + dl * np.sin(fi))

        b1 = Point(a1.x + dl * np.cos(fi),
                   a1.y + dl * np.sin(fi))

        c = Point(a1.x + dl * np.cos(fi + np.pi / 3),
                  a1.y + dl * np.sin(fi + np.pi / 3))

        self.koch(a1, c, fi + np.pi / 3, n - 1)
        self.koch(c, b1, fi - np.pi / 3, n - 1)
        self.koch(a, a1, fi, n - 2)
        self.koch(b1, b, fi, n - 2)


class KochWidgetF(Widget):
    def __init__(self, k=8, **kwargs):
        super(KochWidgetF, self).__init__(**kwargs)
        points = np.array([0, 0, 0.5, 0.5 * 3 ** 0.5, 1, 0])
        points *= 300
        points[::2] += 350
        points[1::2] += 200

        self.a = Point(points[0], points[1])
        self.b = Point(points[2], points[3])
        self.c = Point(points[4], points[5])
        self.fi1 = np.radians(60)
        self.fi2 = np.radians(-60)
        self.fi3 = np.radians(180)
        self.n = k

    def start(self):
        self.koch(self.a, self.b, self.fi1, self.n)
        self.koch(self.b, self.c, self.fi2, self.n)
        self.koch(self.c, self.a, self.fi3, self.n)

    def koch(self, a, b, fi, n):
        if n <= 0:
            with self.canvas:
                Color(1., 0, 0)
                Line(points=[a.x, a.y, b.x, b.y], width=1)
            return

        length = ((a.x - b.x) ** 2 + (a.y - b.y) ** 2) ** 0.5
        dl = length / 3

        a1 = Point(a.x + dl * np.cos(fi),
                   a.y + dl * np.sin(fi))

        b1 = Point(a1.x + dl * np.cos(fi),
                   a1.y + dl * np.sin(fi))

        c = Point(a1.x + dl * np.cos(fi + np.pi / 3),
                  a1.y + dl * np.sin(fi + np.pi / 3))

        self.koch(a1, c, fi + np.pi / 3, n - 1)
        self.koch(c, b1, fi - np.pi / 3, n - 1)
        self.koch(a, a1, fi, n - 2)
        self.koch(b1, b, fi, n - 2)
