import numpy as np
from numpy.linalg import norm
from numpy import matmul as mul
from random import sample
from scipy.stats import norm as normal


def center(matrix):
    for j in range(matrix.shape[1]):
        mean = matrix[:,j].mean()
        for i in range(matrix.shape[0]):
            matrix[i,j] -= mean


def vifSelect(m, xs, ys):
    w = 0.5
    deltaw = .05

    vcxs = np.matrix(xs).T

    center(vcxs)
    ys = np.array(ys)
    mys = np.matrix(ys)
    subsample = sample(range(len(xs[0])), m)
    f = 0
    rmse = np.std(ys)
    residuals = np.matrix([y - ys.mean() for y in ys])
    model = np.matrix([1]*m).T

    results = np.matrix([1]*len(xs[0])).T

    whichVars = []

    for j in range(len(xs)):
        alpha = w / (1+j-f)
        gammahat = residuals.dot(vcxs[:,j])/norm(vcxs[:,j])
        xsub = []
        for i in subsample:
            xsub.append(vcxs[i, j])
        xsub = np.matrix(xsub).T

        matrixOfFun = mul(mul(mul(xsub.T, model), np.linalg.inv(mul(model.T, model))), mul(model.T, xsub))
        rsquared = matrixOfFun[0,0] / (norm(xsub)**2)
        t = gammahat / (rmse * np.sqrt(1-rsquared))

        cdfval = 2*normal.cdf(-abs(t))
        if cdfval < alpha:
            model = np.hstack((model, xsub))
            results = np.hstack((results, vcxs[:,j]))

            whichVars.append(j)

            residuals = mys - mul(mul(mul(results, np.linalg.inv(mul(results.T, results))), results.T), ys)
            rmse = norm(residuals) / np.sqrt(len(xs[0]) - 1 - model.shape[1])
            w = w + deltaw
            f = j
        else:
            w = (w - alpha) / (1-alpha)
    coeffs = mul(mul(np.linalg.inv(mul(results.T, results)), results.T),ys)
    return coeffs, whichVars