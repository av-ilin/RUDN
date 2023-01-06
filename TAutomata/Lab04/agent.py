from loc import Location
import numpy as np


class Agent:
    def __init__(self, x=0, y=0):
        self.backup = (x, y)
        self.location = Location(x, y)
        self.purpose = 0
        self.attack = 0.1
    
    def reset(self):
        self.location = Location(self.backup[0], self.backup[1])
        self.purpose = 0
        self.attack = 0.1

    def get_state(self):
        state = self.location.toNumpy()
        state = np.append(state, [self.purpose]).astype(int)
        return state
    
    
class TableAgent(Agent):
    def __init__(self, size=10, alpha=0.1, gamma=0.6, x=0, y=0):
        super().__init__(x, y)
        self.q_table = np.zeros((size, size, 2, size, size, 5))
        self.alpha = alpha
        self.gamma = gamma

    def get_action(self, state, epsilon=-1):
        if np.random.uniform(0, 1) < epsilon:
            return np.random.randint(5)
        return np.argmax(self.q_table[state[0], state[1], state[2], 
                                      state[3], state[4]])

    def update(self, state, action, reward, next_state):
        old_value = self.q_table[state[0], state[1], state[2], state[3], state[4], action]
        next_max = np.max(self.q_table[next_state[0], next_state[1], next_state[2], next_state[3], next_state[4]])
        new_value = (1 - self.alpha) * old_value + self.alpha * (reward + self.gamma * next_max)
        self.q_table[state[0], state[1], state[2], state[3], state[4], action] = new_value