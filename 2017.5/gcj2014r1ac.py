import numpy as np
import random

def generatorBad():
    res = range(0, 1000)
    for i in xrange(0, 1000):
        j = random.randint(0, 999)
        res[i], res[j] = res[j], res[i]
    return res


def getMat():
    tol = 1
    mat = [[0] * 1000] * 1000
    for i in xrange(0, tol):
        res = generatorBad()
        for j in xrange(0, 1000):
            mat[j][res[j]] += 1
    print mat
    for i in xrange(0, 1000):
        for j in xrange(0, 1000):
            mat[i][j] = mat[i][j] * 1.0 / tol
    return mat

a = getMat()
np.savetxt("../Data/gcj2014r1ac/mat.csv", a)
b = np.loadtxt("../Data/gcj2014r1ac/mat.csv")
print b
