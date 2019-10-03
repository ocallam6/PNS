import pandas as pd 
import matplotlib.pyplot as plt 
from mpl_toolkits.mplot3d import Axes3D

df_1=pd.read_csv('q1.csv')
df_2=pd.read_csv('q2.csv')
df_3=pd.read_csv('q2q1.csv')
df_4=pd.read_csv('q2q2.csv')

plt.figure(1)
plt.plot(df_1.t,df_1.x)
plt.xlabel('t')
plt.ylabel('x')
plt.title('Q1 Part1: x(t)')
plt.show()

plt.figure(2)
plt.plot(df_2.t,df_2.x)
plt.xlabel('t')
plt.ylabel('x')
plt.title('Q1 Part2: x(t)')
plt.show()


fig = plt.figure(3)
ax = fig.add_subplot(111, projection='3d')
ax.plot(df_3.x0,df_3.x1,df_3.x2)
ax.set_xlabel('x0')
ax.set_ylabel('x1')
ax.set_zlabel('x2')
plt.title('Question 2: Part 1')
plt.show()

fig = plt.figure(4)
ax = fig.add_subplot(111, projection='3d')
ax.plot(df_4.x0,df_4.x1,df_4.x2)
ax.set_xlabel('x0')
ax.set_ylabel('x1')
ax.set_zlabel('x2')
plt.title('Question 2: Part 2')
plt.show()