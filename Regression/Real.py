import VifRegression
from random import Random
from pickle import dump
from time import time

m = 300

xs = []
ys = []

rand = Random()
rand.seed(57424)

somecols = rand.sample(range(150), 15)
loosecols = somecols[0:7]
medcols = somecols[7:12]
tightcols = somecols[12:15]

for i in range(1000):
    row = []
    y = rand.uniform(0, 400)
    for j in range(150):
        if j in loosecols:
            x = y + rand.uniform(-360, 360)
        elif j in medcols:
            x = y + rand.uniform(-120, 120)
        elif j in tightcols:
            x = y + rand.uniform(-40, 40)
        else:
            x = rand.uniform(0, 400)
        row.append(x)
    xs.append(row)
    ys.append(y)

xsfile = open("xs.p", "wb+")
ysfile = open("ys.p", "wb+")

dump(xs, xsfile)
dump(ys, ysfile)
tinit = time()
coefficients, whichVars = VifRegression.regress(m, xs, ys)
tfinal = time()
results = open("results.txt", "w+")
results.write("Regression Coeffs: " + str(coefficients))
results.write("Variables with relation: " + str(somecols))
results.write("Variable numbers selected: " + str(whichVars))
results.write("m = 300")
results.write("Time: " + str(tfinal - tinit))
print(coefficients)
print("\n")
print(somecols)
print("\n")
print(whichVars)
