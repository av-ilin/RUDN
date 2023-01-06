import gym
from gym import spaces
import pandas as pd
from IPython.display import display
from IPython.display import clear_output
import numpy as np
from loc import Location


class HunterWorldEnv(gym.Env):
    
    def __init__(self, agent, target, size=10, n_border=20, agent_locs=[]):
        self.size = size
        self.agent = agent
        self.target = target
        self.observation_space = spaces.Dict(
            {
                "agent": spaces.Box(0, np.array([size - 1, size - 1, 1]), dtype=int),
                "target": spaces.Box(0, size - 1, shape=(2,), dtype=int),
            }
        ) 
        self.action_space = spaces.Discrete(5)
        self._action_to_direction = {
            0: np.array([1, 0]),
            1: np.array([0, 1]),
            2: np.array([-1, 0]),
            3: np.array([0, -1]),
        }
        self.borders = self.create_borders(n_border, size, agent_locs)
    
                
    def create_borders(self, n, size, agent_locs):
        borders = []
        for i in range(n):
            loc = Location(np.random.randint(size), np.random.randint(size))
            while loc == self.agent.location or loc == self.target.location or loc in self.target.route or loc in agent_locs:
                loc = Location(np.random.randint(size), np.random.randint(size))
            borders.append(loc)
        return borders
        
        
    def _get_obs(self):
        agent = self.agent.get_state()
        target = self.target.get_state()
        desk = np.zeros((1, self.size + 2, self.size + 2))
        desk[0] = np.pad(self.render(), 1, constant_values=-1)
        obs = desk[:, self.agent.location.y:self.agent.location.y + 3, 
                      self.agent.location.x:self.agent.location.x + 3]
        return {"agent": agent,
                "target": target,
                "state_bse": np.concatenate([agent, target]),
                "state_net": obs}

    
    def _get_info(self):
        return {"distance": self.agent.location.dist(self.target.location)}

    
    def reset(self):
        self.agent.reset()
        self.target.reset()
        observation = self._get_obs()
        info = self._get_info()
        return observation, info

    
    def step(self, action):
        if action == 4:
            if self.agent.location == self.target.location and self.agent.purpose == 0:
                if self.agent.attack > self.target.escape:
                    self.agent.purpose = 1
                    self.target.update()
                    return self._get_obs(), 1000, False, self._get_info()
                self.agent.attack += 0.1
                self.target.run()
                return self._get_obs(), 1000, False, self._get_info()
            return self._get_obs(), -500, False, self._get_info()
                  
        direction = self._action_to_direction[action]
        new_loc = np.clip(self.agent.location.toNumpy() + direction, 0, self.size - 1)
        new_loc = Location(new_loc[1], new_loc[0])
        if new_loc not in self.borders:
            self.agent.location = new_loc
        
        observation = self._get_obs()
        info = self._get_info()
        reward = -info['distance']

        if self.agent.location == self.target.location and self.agent.purpose == 1:
            return observation, 1000, True, info

        return observation, reward, False, info


    def print(self):
        clear_output(wait=True)
        
        def cell_color(val):
            color = 'white'
            if val == 'A':
                color = 'blue'
            if val == 'T':
                color = 'green'
            if val == 'X':
                color = 'red'
            if val == 'O':
                color = 'yellow'
            if val == 'B':
                color = 'black'
            return 'color: %s' % color
        
        n = self.size
        desk = np.full((n, n), '.').astype(str)
        desk[self.agent.location.y, self.agent.location.x] = 'A'
        desk[self.target.location.y, self.target.location.x] = 'T' if self.agent.purpose == 0 else 'O'
        if self.agent.location == self.target.location and self.agent.purpose == 0:
            desk[self.agent.location.y, self.agent.location.x] = 'X'
        for border in self.borders:
            desk[border.y, border.x] = 'B'
        display(pd.DataFrame(desk).style.applymap(cell_color))

        
    def render(self):        
        n = self.size
        desk = np.full((n, n), 0).astype(int)
        desk[self.agent.location.y, self.agent.location.x] = 1
        desk[self.target.location.y, self.target.location.x] = 2 if self.agent.purpose == 0 else 3
        if self.agent.location == self.target.location and self.agent.purpose == 0:
            desk[self.agent.location.y, self.agent.location.x] = 4
        for border in self.borders:
            desk[border.y, border.x] = 5
        return desk