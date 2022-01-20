# -*- coding: utf-8 -*-
# ***Vous trouverez dans ce notebook les différents résultats obtenus lors de la résolution des équations de la chaleur instationnaire***

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


# # Euler Explicite

with open("Resultats_Explicite.txt", "r") as f:
    lines = f.readlines()
X = float(lines[0])
DeltaX = float(lines[1])
DeltaT = float(lines[2])
lines = lines[3:]  #On charge le fichier texte contenant les résultats et on le lit ligne à ligne, 
#les trois premières lignes contenant les valeurs de X, DeltaX et DeltaT

plt.close()
fig=plt.figure(figsize=(20,10))
x = np.arange(0,X+DeltaX,DeltaX)
for i in range(0,len(lines),300):
    t = i * DeltaT
    plt.plot(x, [float(s) for s in lines[i].split("; ")[:-1]], label="t = " + str(t)[:4] + " s") 
plt.legend()
plt.title("Evolution de la température dans le milieu en fonction du temps_Euler Explicite")
plt.xlim(0, X)
plt.ylim(-1, 2)
plt.xlabel("Abscisse")
plt.ylabel("Température")
plt.show()

# +
plt.close()
fig=plt.figure(figsize=(20,10))
line, = plt.plot(x, [float(s) for s in lines[0].split("; ")[:-1]], label="t = " + str(0.0)[:4] + " s")
plt.title("Evolution de la température dans le milieu en fonction du temps (version animée)")
plt.xlabel("Abscisse")
plt.ylabel("Température")

def animate(i): 
    t = (i%len(lines)) * DeltaT
    y = [float(s) for s in lines[i%len(lines)].split("; ")[:-1]]
    line.set_data(x, y)
    line.set_label("t = " + str(t)[:4] + " s")
    return line,

ani = animation.FuncAnimation(fig, animate, frames=len(lines), blit=True, interval=200, repeat=True)
plt.show()
# -

# # Euler Implicite

with open("Resultats_Implicite.txt", "r") as f:
    linesI = f.readlines()
X = float(linesI[0])
DeltaX = float(linesI[1])
DeltaT = float(linesI[2])
linesI = linesI[3:]

plt.close()
fig=plt.figure(figsize=(20,10))
x = np.arange(0,X+DeltaX,DeltaX)
for i in range(0,len(linesI),300):
    t = i * DeltaT
    plt.plot(x, [float(s) for s in linesI[i].split("; ")[:-1]], label="t = " + str(t)[:4] + " s") 
plt.legend()
plt.title("Evolution de la température dans le milieu en fonction du temps_Euler Implicite")
plt.xlim(0, X)
plt.ylim(-1, 2)
plt.xlabel("Abscisse")
plt.ylabel("Température")
plt.show()

plt.close()
fig=plt.figure(figsize=(20,10))
line, = plt.plot(x, [float(s) for s in linesI[0].split("; ")[:-1]], label="t = " + str(0.0)[:4] + " s")
plt.title("Evolution de la température dans le milieu en fonction du temps (version animée)")
plt.xlabel("Abscisse")
plt.ylabel("Température")
ani2 = animation.FuncAnimation(fig, animate, frames=len(linesI), blit=True, interval=200, repeat=True)
plt.show()

# # Comparaison des deux méthodes

# On trace ici l'écart entre les deux méthodes de résolution

plt.close()
fig=plt.figure(figsize=(20,10))
x = np.arange(0,X+DeltaX,DeltaX)
for i in range(0,len(linesI),300):
    t = i * DeltaT
    DonneE = lines[i].split("; ")[:-1]
    DonneI = linesI[i].split("; ")[:-1]
    plt.plot(x, [abs(float(DonneE[s])-float(DonneI[s])) for s in range(len(DonneE))], label="t = " + str(t)[:4] + " s") 
plt.legend()
plt.title("Ecart absolu entre les deux méthodes")
plt.xlim(0, X)
plt.xlabel("Abscisse")
plt.ylabel("Différence Température")
plt.show()

# On remarque que la différence entre les deux méthodes est la plus importante au niveau des extremas de température (la différence se creusant dans les zones de fort gradiant)
