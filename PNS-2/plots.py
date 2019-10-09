import pandas as pd 
import matplotlib.pyplot as plt 
from mpl_toolkits.mplot3d import Axes3D

df_1=pd.read_csv('ass2.csv')


plt.figure(1)
plt.plot(df_1.t,df_1.x0)
plt.xlabel('t')
plt.ylabel('x')
plt.title('Q1: x(t)')
plt.show()

plt.figure(2)
plt.plot(df_1.t,df_1.x1)
plt.xlabel('t')
plt.ylabel('x')
plt.title('Q1: d/dt x(t)')
plt.show()

plt.figure(3)
plt.plot(df_1.x0,df_1.x1)
plt.xlabel('x')
plt.ylabel('dx/dt ')
plt.title('Q1: Phase')
plt.show()

