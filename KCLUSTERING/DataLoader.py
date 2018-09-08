from matplotlib import pyplot as plt
import numpy as np
import KClustering
from time import time
from ast import literal_eval

file = open("data.txt")
a = file.readline().rstrip("\n")

data = literal_eval(a)

inittime = time()
b = KClustering.cluster(data, 4)
finaltime = time()

totaltime = finaltime - inittime
file = open("timepure.txt", "w+")
file.write(str(totaltime))

nb = list(b.values())

dataa = np.array(nb[0])
datab = np.array(nb[1])
datac = np.array(nb[2])
datad = np.array(nb[3])

xa = dataa.T[0]
ya = dataa.T[1]
xb = datab.T[0]
yb = datab.T[1]
xc = datac.T[0]
yc = datac.T[1]
xd, yd = datad.T

plt.plot(xa, ya, 'bo')
plt.plot(xb, yb, 'ko')
plt.plot(xc, yc, 'ro')
plt.plot(xd, yd, 'go')
plt.show()