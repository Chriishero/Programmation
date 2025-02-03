from scipy import misc
import matplotlib.pyplot as plt

face = misc.face(gray=True) # charge une photo de base de la bibliothèqe 'scipy' en noir et blanc
x, y = face.shape
print(x, y)
zoom = face[int(x/4):int(x-x/4), int(y/4):int(y-y/4)] # zoom de 1/4 sur l'image
zoom[zoom > 200] = 255 # pour tous les pixels avec une luminosité élevé (>200), la mettre au maximum
zoom[zoom < 100] = 0 # pour tous les pixels avec une luminosité basse (<100), la mettre au minimum

plt.imshow(zoom, cmap=plt.cm.gray) # l'affiche en noir et blanc
plt.show()

