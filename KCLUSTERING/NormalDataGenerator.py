from matplotlib import pyplot as plt
import numpy as np
from scipy import random as rnd
import KClustering
from time import time

def generate(meanx, meany, stddevx, stddevy, amount):
    alist = []
    for x in range(amount):
        alist.append(np.array([rnd.normal(meanx, stddevx), rnd.normal(meany, stddevy)]))
    return np.array(alist)
    

data = generate(-10, 5, 4, 4, 25000)
data2 = generate(21, 14, 5, 5, 25000)
data3 = generate(15, -19, 4, 4, 25000)
data4 = generate(-18, -21, 4, 4, 25000)
bigdata = data.tolist() + data2.tolist() + data3.tolist() + data4.tolist()

print(bigdata)

initime = time()
a = KClustering.cluster(bigdata, 4)
finaltime = time()

totaltime = finaltime - initime

file = open("time.txt", "w+")
file.write(str(totaltime))

dataa = np.array(a[0])
datab = np.array(a[1])
datac = np.array(a[2])
datad = np.array(a[3])

xa = dataa.T[0]
ya = dataa.T[1]
xb = datab.T[0]
yb = datab.T[1]
xc = datac.T[0]
yc = datac.T[1]
xd, yd = datad.T

x = data.T[0]
y = data.T[1]
x2 = data2.T[0]
y2 = data2.T[1]
x3 = data3.T[0]
y3 = data3.T[1]
x4, y4 = data4.T

plt.plot(x, y, 'bo')
plt.plot(x2, y2, 'ko')
plt.plot(x3, y3, 'ro')
plt.plot(x4, y4, 'go')
plt.show()

plt.plot(xa, ya, 'bo')
plt.plot(xb, yb, 'ko')
plt.plot(xc, yc, 'ro')
plt.plot(xd, yd, 'go')
plt.show()