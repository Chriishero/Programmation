"""
signal.detrend(y) : élimine les tendances linéaires du signal 'y'

Transformation de fourier : technique mathématique qui permet d'extraire et d'analyser les fréquences présentes dans un signal périodique.
En résultat, on récupère un spectre avec les fréquences en abscisse et l'amplitude en ordonnée
"""

import numpy as np 
import matplotlib.pyplot as plt
from scipy import signal, fftpack

x = np.linspace(0, 20, 100)
y = x + 4*np.sin(x) + np.random.randn(x.shape[0])
new_signal = signal.detrend(y)

plt.plot(x,y)
plt.plot(x,new_signal)
plt.show()

x = np.linspace(0, 30, 1000)
y = 3 * np.sin(x) + 2 * np.sin(5*x) + np.sin(10*x) + np.random.random(x.shape[0]) * 10 # signal avec du bruit

fourier = fftpack.fft(y)
power = np.abs(fourier)
frequences = fftpack.fftfreq(y.size)

fourier[power<400] = 0 # filtre les fréquences dont l'amplitude est < 400

filtered_signal = fftpack.ifft(fourier) # transformation fourier inverse sur le spectre obtenu 

plt.figure(figsize=(12, 8))
plt.plot(x, y) # affiche le signal contenue du bruit
plt.plot(x, filtered_signal, lw=3) # affiche le signal filtré
plt.show()