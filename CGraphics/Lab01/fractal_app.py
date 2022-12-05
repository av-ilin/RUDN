from koch_widget import KochWidget, KochWidgetR, KochWidgetF
from tree_widget import PythagoreanTree
from mandelbrot_widget import MandelbrotSet
from kivy.app import App
import json


class FractalApp(App):
    def __init__(self):
        super().__init__()
        with open('fractal_config.json') as json_file:
            config = json.load(json_file)
        fractal_idx = config['fractal']
        deep = config['deep']
        alpha = config['alpha'] if config['alpha'] is not None else 45
        fractals = [KochWidgetR(deep), KochWidgetF(deep), PythagoreanTree(deep, alpha), MandelbrotSet()]
        self.fractal = fractals[fractal_idx]

    def build(self):
        return self.fractal

    def on_start(self):
        self.fractal.start()
