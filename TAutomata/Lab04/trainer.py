from IPython.display import display
from IPython.display import clear_output
import pandas as pd
from loc import Location
from time import sleep


class AgentTrainer:
    def __init__(self, agents, target, env):
        self.agents = agents
        self.target = target
        self.env = env
        self.statistic = None
    
    def start(self, locations=[Location(0, 0)]):
        stats = {'Agent-%d' % i: {'Episod': None, 
                                  'Alpha': None, 
                                  'Gamma': None, 
                                  'Done': None} for i in range(len(self.agents))}

        for i, agent in enumerate(self.agents):
            eps_all = 0
            success_all = True
            step_count_all = 0
            for j, loc in enumerate(locations):
                self.agents[i].location = loc
                self.agents[i].backup = (loc.x, loc.y)
                eps, (success, step_count) = self.train(i, idx_loc=j, loc_count=len(locations))
                eps_all += eps
                success_all &= success
                step_count_all += step_count
            stats['Agent-%d' % i] = {'Alpha': agent.alpha, 
                                     'Gamma': agent.gamma, 
                                     'Done': success,
                                     'Episod': eps_all/len(locations),
                                     'Step':  step_count_all/len(locations)}
            
        self.statistic = pd.DataFrame(stats).T
        display(pd.DataFrame(self.statistic.sort_values(by=['Episod', 'Step']).head(10)))
    
    
    def progress(self, i, n_episod, agent_idx=0, idx_loc=0, loc_count=0):
        clear_output(wait=True)
        print('Agent: %d/%d\tLocation: %d/%d\tEpisod: %d/%d' % (agent_idx+1, len(self.agents), 
                                                                idx_loc + 1, loc_count,
                                                                i+1, n_episod), end='')
        
    
    def train(self, agent_idx=0, n_episod = 100, max_iter=10000, idx_loc=0, loc_count=0):
        agent = self.agents[agent_idx]
        target = self.target
        env = self.env
        env.agent = agent
        episod_counter = 0
        
        for i in range(0, n_episod):
            episod_counter += 1
            self.progress(i, n_episod, agent_idx, idx_loc, loc_count)
            obs, _ = env.reset()
            state = obs['state_bse']
            done = False
            eps = 1 - (i + 1) / n_episod
            for j in range(max_iter):
                action = agent.get_action(state, eps)
                obs, reward, done, info = env.step(action)
                next_state = obs['state_bse']
                agent.update(state, action, reward, next_state)
                state = next_state
                if done:
                    break
            if self.check(agent_idx):
                break
                
        return episod_counter, self.check(agent_idx, counter=True)
    
    
    def check(self, agent_idx, max_iter=100, view=False, counter=False):
        agent = self.agents[agent_idx]
        env = self.env
        env.agent = agent
        
        obs, _ = env.reset()
        if view:
            env.print()
            sleep(0.3)
        state = obs['state_bse']
        done = False
        step_count = 0
        for _ in range(max_iter):
            step_count += 1
            action = agent.get_action(state)
            obs, reward, done, info = env.step(action)
            state = obs['state_bse']
            if view:
                env.print()
                sleep(0.3)
            if done:
                break
        
        if counter:
            return done, step_count
        return done