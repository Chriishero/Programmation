import numpy as np
import matplotlib.pyplot as plt

dataset = {f"exeperience{i}": np.random.randn(100) for i in range(4)}

def graphique(data):
    n = len(data)
    plt.figure(figsize=(10 ,8))
    for k, i in zip(data.keys(), range(1, n+1)):
        plt.subplot(n, 1, i)
        plt.plot(data[k])
        plt.title(k)
    plt.show()

graphique(dataset)