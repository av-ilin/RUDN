import numpy as np


class Location:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        
    def toNumpy(self):
        return np.array([self.y, self.x], dtype=int)

    def dist(self, other):
        return np.linalg.norm(self.toNumpy() - other.toNumpy(), ord=1)
    
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y
    
    def __lt__(self, other):
        return self.x < other.x and self.y < other.y
    
    def __repr__(self):
        return '(' + str(self.x) + ', ' + str(self.y) + ')'