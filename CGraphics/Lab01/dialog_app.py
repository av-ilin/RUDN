from kivy.config import Config
from kivy.app import App
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.button import Button
from kivy.uix.textinput import TextInput
import json


red = (255 / 255, 67 / 255, 67 / 255)
green = (0 / 255, 158 / 255, 60 / 255)
Config.set('graphics', 'width', '300')
Config.set('graphics', 'height', '300')


class DialogApp(App):
    def __init__(self, **kwargs):
        super().__init__()
        self.deep = None
        self.alpha = None

    def build(self):
        main_layout = FloatLayout()

        self.deep = TextInput(hint_text='Input deep:',
                              size_hint=(.5, .2),
                              pos_hint={'center_x': .25, 'center_y': .9},
                              multiline=False)
        self.alpha = TextInput(hint_text='Input alpha:',
                               size_hint=(.5, .2),
                               pos_hint={'center_x': .75, 'center_y': .9},
                               multiline=False)

        but01 = Button(text='Direct Koch',
                       size_hint=(1, .2),
                       pos_hint={'center_x': .5, 'center_y': 0.7},
                       color=red)
        but02 = Button(text='Koch\'s Snowflake',
                       size_hint=(1, .2),
                       pos_hint={'center_x': .5, 'center_y': 0.5},
                       color=red)
        but03 = Button(text='The Pythagorean Tree',
                       size_hint=(1, .2),
                       pos_hint={'center_x': .5, 'center_y': .3},
                       color=red)
        but04 = Button(text='The Mandelbrot Set',
                       size_hint=(1, .2),
                       pos_hint={'center_x': .5, 'center_y': .1},
                       color=red)

        but01.bind(on_press=self.on_but01)
        but02.bind(on_press=self.on_but02)
        but03.bind(on_press=self.on_but03)
        but04.bind(on_press=self.on_but04)

        main_layout.add_widget(but01)
        main_layout.add_widget(but02)
        main_layout.add_widget(but03)
        main_layout.add_widget(but04)
        main_layout.add_widget(self.alpha)
        main_layout.add_widget(self.deep)
        return main_layout

    def on_start(self):
        with open('fractal_config.json') as json_file:
            config = json.load(json_file)
        self.deep.text = str(config['deep']) if config['deep'] is not None else ''
        self.alpha.text = str(config['alpha']) if config['alpha'] is not None else ''

        config = {'fractal': None,
                  'deep': None,
                  'alpha': None}
        with open('fractal_config.json', 'w') as outfile:
            json.dump(config, outfile)

    def write_config(self, config):
        print(config)
        with open('fractal_config.json', 'w') as outfile:
            json.dump(config, outfile)
        self.stop()

    def on_but01(self, *args):
        deep = 8 if self.deep.text == '' else int(self.deep.text)
        deep = 10 if deep > 10 else deep
        config = {'fractal': 0,
                  'deep': deep,
                  'alpha': None}
        self.write_config(config)

    def on_but02(self, *args):
        deep = 8 if self.deep.text == '' else int(self.deep.text)
        deep = 8 if deep > 8 else deep
        config = {'fractal': 1,
                  'deep': deep,
                  'alpha': None}
        self.write_config(config)

    def on_but03(self, *args):
        deep = 8 if self.deep.text == '' else int(self.deep.text)
        deep = 13 if deep > 13 else deep
        alpha = 45 if self.alpha.text == '' else int(self.alpha.text)
        config = {'fractal': 2,
                  'deep': deep,
                  'alpha': alpha}
        self.write_config(config)

    def on_but04(self, *args):
        config = {'fractal': 3,
                  'deep': None,
                  'alpha': None}
        self.write_config(config)

