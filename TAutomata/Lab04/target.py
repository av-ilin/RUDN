from loc import Location
import numpy as np


class Target:
    def __init__(self, size, x=None, y=None, n_routes=20, escape=np.random.random()):
        self.area_size = size
        self.backup = {'location': None, 'route': None}
        self.location = self.create_location(x, y, size)
        self.route = self.create_escape_route(n_routes)
        self.escape = escape
    
    
    def create_location(self, x, y, size):
        x = x if x is not None else np.random.randint(size)
        y = y if y is not None else np.random.randint(size)
        while x == 0 and y == 0:
            x = np.random.randint(size)
            y = np.random.randint(size)
        self.backup['location'] = Location(x, y)
        return Location(x, y)
    
    
    def create_escape_route(self, n):
        area = self.area_size
        loc = self.location
        x, y = loc.x, loc.y
        route = []
        for i in range(n):   
            dx = np.random.randint(-5, 5)
            dy = 5 - abs(dx) if np.random.uniform(0, 1) < 0.5 else abs(dx) - 5
            new_x = x + dx
            new_y = y + dy
            while not (0 <= new_x < area and 0 <= new_y < area):
                dx = np.random.randint(-5, 5)
                dy = 5 - abs(dx) if np.random.uniform(0, 1) < 0.5 else abs(dx) - 5
                new_x = x + dx
                new_y = y + dy
            route.append(Location(new_x, new_y))
            x = new_x
            y = new_y
        self.backup['route'] = list(route)
        return route


    def run(self):
        self.location = self.route.pop(0)

    def reset(self):
        self.location = Location(self.backup['location'].x, self.backup['location'].y)
        self.route = list(self.backup['route'])

    def get_state(self):
        return self.location.toNumpy()

    def update(self):
        self.location = Location(0, 0)