from kivy.uix.widget import Widget
from kivy.graphics import *
import numpy as np


class MandelbrotSet(Widget):
    def __init__(self, **kwargs):
        super(MandelbrotSet, self).__init__(**kwargs)

    def start(self):
        self.mset()

    def draw(self, image, size_x, size_y):
        pos_x = (1000 - size_x)/2
        pos_y = (600 - size_y)/2
        with self.canvas:
            Color(1., 0, 0)
            Rectangle(pos=(pos_x, pos_y), size=(size_x, size_y))

        for i in range(image.shape[0]):
            for j in range(image.shape[1]):
                if image[i][j] < 1:
                    with self.canvas:
                        Color(0, 0, 0)
                        Rectangle(pos=(i + pos_x, j + pos_y), size=(1, 1))

    def mset(self):
        count_p, count_q = 500, 500
        count_iter = 100
        val_R = 1e+16

        image = np.zeros((count_p, count_q))
        p_list = np.linspace(-2.5, 1.5, count_p)
        q_list = np.linspace(-2, 2, count_q)

        for i, p in enumerate(p_list):
            for j, q in enumerate(q_list):
                c = p + q * 1j
                z = 0
                for k in range(count_iter):
                    z = z ** 2 + c
                    if abs(z) > val_R:
                        image[i, j] = 1
                        break

        self.draw(image, count_p, count_q)
