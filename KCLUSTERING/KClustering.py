from random import sample
import math
from copy import deepcopy
from matplotlib import pyplot as plt
import numpy as np

def importDataset():
    pass


def initassign(dataset, mapping):
    newmap = {x:None for x in mapping.keys()}
    for e in dataset:
        closemean = ()
        means = tuple(mapping.keys())
        dist = math.inf
        for mean in means:
            ndist = sum([(mean[x] - e[x])**2 for x in range(len(e))])
            if ndist < dist:
                closemean = mean
                dist = ndist
        if newmap[closemean] is not None:
            newmap[closemean] = newmap[closemean] + (e,)
        else:
            newmap[closemean] = (e,)
    return newmap


def update(mapping):
    newmap = {}
    for cluster in mapping.values():
        a = [0]*len(cluster[0])
        for x in range(len(cluster[0])):
            a[x] = sum([b[x] for b in cluster])
            a[x] /= len(cluster)
        newmap[tuple(a)] = None
    return newmap



def display(map):
    a = list(map.values())
    dataa = np.array(a[0])
    datab = np.array(a[1])
    datac = np.array(a[2])
    xa = dataa.T[0]
    ya = dataa.T[1]
    xb = datab.T[0]
    yb = datab.T[1]
    xc = datac.T[0]
    yc = datac.T[1]
    plt.plot(xa, ya, 'bo')
    plt.plot(xb, yb, 'ko')
    plt.plot(xc, yc, 'ro')
    plt.show()


def cluster(dlist, k):
    dataset = dlist

    initmeans = sample(dataset, k)

    mapping = {tuple(x): None for x in initmeans}

    mapping = initassign(dataset, mapping)
    oldmap = deepcopy(mapping)
    mapping = update(mapping)

    x = True
    n = 0
    while x:
        #print(n)
        mapping = initassign(dataset, mapping)
        x = oldmap != mapping
        oldmap = deepcopy(mapping)
        #print(x)
        if x:
            mapping = update(mapping)
        n += 1
    #print("Done")
    return oldmap

# dataset = importDataset()
#
# k = 4
#
# initmeans = sample(dataset, k)
#
# mapping = {x:None for x in initmeans}
#
#
# initassign(dataset, mapping)
# update(mapping)
#
# x = True
#
# while x:
#     x = assign(dataset, mapping)
#     mapping = update(mapping)
#
# print("Done!")