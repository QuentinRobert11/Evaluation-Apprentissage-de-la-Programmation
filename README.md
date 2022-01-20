## Apprentissage de la programmation : Evaluation
# Equation de la chaleur instationnaire

Quentin ROBERT
20 janvier 2022

# Structure du projet :

Vous trouverez dans ce repository différents dossiers contenant divers fichiers.
Tandis que le dossier src regroupe les différents fichiers .cpp, le fichier headers regroupe les différents fichiers .h. On a pris soint de créer un makefile et un dossier build contenant des fichiers .o. L'exécutable final est lui aussi présent dans ce repository et porte le nom de *project*. 
On notera enfin la présence de deux fichiers .txt contenant les résultats obtenus lors des résolutions explicites et implicites de l'équation ainsi qu'un fichier .py (jupyter notebook) permettant de les visualiser.

**Review des différents fichiers : **

Dans ce projet sont définis différents objets :

- Les fichiers *matrix.h* et *matrix.cpp* servent à créer une classe Matrix qui nous sera utile par la suite. On y définit les opérations élémentaires du calcul matriciel ainsi que les notions de norme, trace, transposées... Une fonction *tests_Matrices()* permet de faire dans l'éxécutable final un certain nombre de tests de ces opérations. Notons qu'on a pris soin d'utiliser des templates, permettant dedéfnir des objets Matrix<int> comme des objets Matrix<double> (qui nous serons plus utiles ici.
- Les fichiers *linear_syst.h* et *linear_syst.cpp* nous permettent de définir deux méthodes de résolution des systèmes linéaires : la méthode du gradiant conjugué et la méthode du pivot (utile pour la première question bonus que je n'ai malheureusement pas eu le temps de terminer)
- Les fichiers *temperature_map.h* et *temperature_map.cpp* nous permettent de définir des objets de type TempMap représentant une carte de la tempéraure pour Nx point de l'espace alignés. Cest objets présentent les méthodes *iterer_EExplicite()* et *iterer_EImplicite()* qui permettent de faire une itération de la résolution par la méthode d'Euler selon un pas DeltaT. la méthode *Resoudre()* permet alors de faire un nombre Nt d'itérations et de ranger les résultats dans un fichier .txt.
- Le fichier *main.cpp* est lui une interface console permettant de présenter les différents tests du calcul matriciel, mais aussi de la résolution des systèmes linéaires. Il permet aussi à l'utilisateur de lancer une nouvelle résolution de l'équation de la chaleur avec des pas spatial et temporels choisis.
 
Le notebook *graphiques.py* permet d'observer les différents résultats obtenus.
