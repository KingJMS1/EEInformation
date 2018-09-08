from sklearn.cluster import KMeans
from ast import literal_eval
from time import time
from pickle import dump

file = open("data.txt")
a = file.readline().rstrip("\n")

data = literal_eval(a)

file.close()

initime = time()
kmeans = KMeans(n_clusters=4).fit(data)
labellen = kmeans.labels_
finaltime = time()

points = open("pts.p", "wb")
dump(data, points)
points.close()
labels = open("lbs.p", "wb")
dump(labellen, labels)
labels.close()

presults = open("PackageResults.txt", 'w+')
presults.write(str(finaltime - initime))