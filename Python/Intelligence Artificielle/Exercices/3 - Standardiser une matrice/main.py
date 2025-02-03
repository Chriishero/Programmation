import numpy as np

np.random.seed(0)
A = np.random.randint(0, 100, [10, 5])
print(A)

std = A.std(axis=0)
mean = A.mean(axis=0)

A = (A-mean)/std
print(A)
