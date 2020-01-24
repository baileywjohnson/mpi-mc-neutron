import pandas as pd
from pandas import DataFrame

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

df = pd.read_csv('data_file.csv')
threedee = plt.figure().gca(projection='3d')
threedee.scatter(df['A'], df['H'], df['r/n'], color='red')
threedee.scatter(df['A'], df['H'], df['b/n'], color='green')
threedee.scatter(df['A'], df['H'], df['t/n'], color='blue')
threedee.set_xlabel('A')
threedee.set_ylabel('H')
threedee.set_zlabel('r/n, b/n, t/n')

plt.show()