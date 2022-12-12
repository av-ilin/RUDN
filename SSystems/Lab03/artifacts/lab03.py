import pandas as pd
import numpy as np
import json
import pickle
from catboost import CatBoostRegressor
from catboost import CatBoostClassifier
from sklearn.cluster import KMeans


data_anime = pd.read_csv('anime_cl.csv')
data_top = json.load(open('anime_top_for_cluster.json'))
clf_model = CatBoostClassifier().load_model('cat_cls.model')
reg_model = CatBoostRegressor().load_model('cat_reg.model')
kmn_model = pickle.load(open('kmeans.model', 'rb'))


def recomend(usr):
    X = np.array([usr[key] for key in sorted(usr)])
    y = kmn_model.predict([X]).reshape(-1)[0]
    anime_for_usr = np.array(data_top[str(y)])
    anime_f = []
    for anime in anime_for_usr:
        X1 = np.array(data_anime[data_anime['anime_id'] == anime].drop(columns=['anime_id'])).reshape(-1)
        X2 = np.array(pd.DataFrame(usr, index=[0])).reshape(-1)
        X3 = np.array(y).reshape(-1)
        X_f = np.concatenate((X3, X2, X1))
        rate1 = clf_model.predict(X_f).reshape(-1)
        rate2 = reg_model.predict(X_f).reshape(-1)
        if (rate1 + rate2)/2 >= 5:
            anime_f.append(anime)
        if len(anime_f) == 10:
            break
    return anime_f