import VifRegression
from pickle import load
from time import time
import numpy as np

m = 300

xfile = open("xs.p", 'rb')
yfile = open("ys.p", 'rb')

xs = load(xfile)
ys = load(yfile)

axs = np.matrix(xs).T
bxs = axs.tolist()

tinit = time()
coefficients, whichVars = VifRegression.vifSelect(m, bxs, ys)
tfinal = time()
results = open("resultspure.txt", "w+")
results.write("Regression Coeffs: " + str(coefficients))
results.write("Variable numbers selected: " + str(whichVars))
results.write("m = 300")
results.write("Time: " + str(tfinal - tinit))
