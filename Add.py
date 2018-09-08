from time import time
b = 5
c = 3
d = 2
initime = time()
for x in range(100000):
	b = (c + d)%100
	c= (b + d)%1000
	d= (c + b + d)%500
	b= (d - c)%150
fintime = time()

print("TIME: " + str(fintime - initime))