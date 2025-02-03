"""
Morphology : technique mathématique qui permet de transformer des matrices.
On définit une structure, qui va se déplacer de pixel en pixel sur l'image, en rencontrant un pixel blanc, elle va soit imprimer des pixels (dilation) ou en effacer (érosion)

ndimage.binary_opening(matrice) : permet l'érosion et la dilation
"""

import numpy as np 
import matplotlib.pyplot as plt
from scipy import ndimage

image = plt.imread('bacteria.png')
image = image[:,:,0] # efface la 3ème dimension

plt.figure(figsize=(12,8))
plt.subplot(2,3,1)
plt.imshow(image, cmap='gray')

image_2 = np.copy(image)
plt.subplot(2,3,2)
plt.hist(image_2.ravel(), bins=255) # fais un histogramme avec l'image applatit et 255 catégories pour chaque valeurs que peut prendre un pixel

image = image < 0.6 # crée un masque de boolean indexing et renvoie une image binaire
plt.subplot(2,3,3)
plt.imshow(image)

open_x = ndimage.binary_opening(image) # retire les artefacts
plt.subplot(2,3,4)
plt.imshow(image)

label_image, n_labels = ndimage.label(open_x) # renvoie des étiquettes pour chaque bactéries, et le nombre d'étiquette
plt.subplot(2,3,5)
plt.imshow(label_image)

sizes = ndimage.sum(open_x, label_image, range(n_labels)) # compte tous les pixels qu'il y a dans les différents groupes de bactéries
# open_x : image original
# label_image : image qui contient les étiquettes
# range(n_labels) : nombre d'étiquette qu'on veut examiner
plt.subplot(2,3,6)
plt.scatter(range(n_labels), sizes, c='orange')

plt.show()