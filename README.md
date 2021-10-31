# ROB306
Projet ROB306

## Pour faire fonctionner le code ##
Lancer `g++ FLAG .\Dijkstra_main.cpp -o .\result; ./result.exe DIMENSION` avec la dimension souhaitée et le flag d'optimisation choisi (par défaut, ne rien mettre).
Lancer `g++ .\Dijkstra_parallel.cpp -o .\result -fopenmp; ./result.exe DIMENSION` avec la dimension choisie pour exécuter le code avec OpenMP

## Pour faire fonctionner le code (OLD VERSION) ##
Penser à changer le chemin de lecture du fichier matrice.txt dans le fichier Dijkstra.cpp

generate.cpp c'est pour créer une matrice de dimension à spécifier, il faut changer la dimension choisie directement dans le fichier Dijkstra.cpp
