from fractal_app import FractalApp
from dialog_app import DialogApp
import json
from kivy.config import Config
from kivy.core.window import Window


Config.set('graphics', 'position', 'custom')


def window_f(size_x, size_y):
    Window.size = (size_x, size_y)
    Window.left = (1366 - size_x)/2
    Window.top = (768 - size_y)/2


def window_d(size_x, size_y):
    Window.size = (size_x, size_y)
    Window.left = 0
    Window.top = 0


def out():
    with open('fractal_config.json') as json_file:
        fractal = json.load(json_file)
    return fractal['fractal'] is not None


if __name__ == '__main__':
    window_d(300, 300)
    DialogApp().run()
    while out():
        window_f(1000, 600)
        FractalApp().run()
        window_d(300, 300)
        DialogApp().run()

