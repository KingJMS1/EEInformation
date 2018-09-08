from sklearn import linear_model
from pickle import load
from time import time



xfile = open("xs.p", 'rb')
yfile = open("ys.p", 'rb')

xs = load(xfile)
ys = load(yfile)
reg = linear_model.ElasticNet()
initime = time()
reg.fit(xs, ys)
finaltime = time()
print(reg.sparse_coef_)
file = open("netsults.txt", 'w+')
file.write("Time: " + str(finaltime - initime) + "\n")
file.write("SPARSE_COEFFS: " + str(reg.sparse_coef_) + "\n" + "IDKMAYBEDENSECOEFFS: " + str(reg.coef_))
file.close()
xfile.close()
yfile.close()
