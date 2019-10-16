import pandas as pd 
import matplotlib.pyplot as plt 

planets=pd.read_csv("planets.csv")
#-------Position with time-------#
plt.figure(1)
plt.plot(planets.x00,planets.x10,color='green')
plt.plot(planets.x01,planets.x11,color='blue')
plt.plot(planets.x02,planets.x12,color='red')
plt.plot(planets.x03,planets.x13,color='black')
plt.xlabel("x")
plt.ylabel("y")
plt.title("Planet 0")
plt.show()