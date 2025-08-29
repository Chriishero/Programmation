import numpy as np

class GDA:
    def __init__(self):
        self.phi, self.mu, self.sigma = None, None, None

    def _prior_probability(self, y):
        m = len(y)
        return 1/m * np.sum(y)
    
    def _means_function(self, X, y):
        m, n = X.shape
        return np.array([