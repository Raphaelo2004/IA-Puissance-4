**Puissance 4 (Connect Four)**

**Description**

Puissance 4 (Connect Four) est un jeu de plateau classique pour deux joueurs. Le but du jeu est d'aligner quatre de ses jetons dans une rangée verticale, horizontale ou diagonale avant l'adversaire. Ce projet implémente une version numérique du jeu en Python (ou autre langage utilisé), où un joueur humain peut affronter une intelligence artificielle (IA).

**Fonctionnalités**

Interface utilisateur en ligne de commande 

Joueur humain contre IA

IA utilisant des algorithmes de recherche de minimax avec élagage alpha-bêta

Gestion des entrées des joueurs

Vérification automatique des conditions de victoire

Gestion des exceptions pour les entrées incorrectes

Possibilité de rejouer une partie

**Prérequis**

Assurez-vous d'avoir les éléments suivants installés sur votre machine :

Python

Git (pour cloner le dépôt)

**Installation**

Clonez le répertoire depuis GitHub :

git clone https://github.com/Raphaelo2004/IA-Puissance-4

Naviguez dans le répertoire du projet :

se mettre dans le bon dossier

Exécutez le script principal pour lancer le jeu :

compilez:

cc MaStrategie.c -o maStrat

lancez :

./maStrat

**Règles du Jeu**

Le jeu se joue sur une grille de 7 colonnes et 6 lignes.

Chaque joueur à son tour dépose un jeton dans l'une des colonnes.

Le premier joueur à aligner quatre de ses jetons verticalement, horizontalement ou diagonalement remporte la partie.

Si la grille est pleine et qu'aucun joueur n'a aligné quatre jetons, la partie est considérée comme un match nul.

**IA**

L'intelligence artificielle utilise l'algorithme de minimax avec élagage alpha-bêta pour prendre des décisions optimales. Cet algorithme évalue les différents coups possibles et choisit celui qui maximise ses chances de victoire tout en minimisant celles de l'adversaire.
