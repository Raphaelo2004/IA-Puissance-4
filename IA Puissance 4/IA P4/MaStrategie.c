#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define LIGNE 6
#define COLONNE 7

typedef int t_grille[LIGNE][COLONNE];

int main(int argc, char** argv);
void chargerGrille(char** argv, t_grille grille);
void copieGrille(t_grille laGrille, t_grille grilleTest);
int coupGagnant(t_grille grilleTest);
int bloquerAdversaire(t_grille grilleTest);
bool prochainCoupPerdant(t_grille grilleTest);
bool deuxPuissance4(t_grille grilleTest, int *i);
int meilleurColonne(t_grille grilleTest);
int choisirColonneOrdi(t_grille laGrille);
int milieu(int j1, int j2);
bool estVainqueur(t_grille laGrille, int lig, int col);
int chercherLigne(t_grille laGrille, int col);
int alignementMax(t_grille laGrille, int lig, int col);


const int VIDE = 0;
const int JOUEUR = 1;
const int ADVERSAIRE = 2;

/*
* VOTRE STRATEGIE
*/
int maStrategie(t_grille grille)
{
    // TODO: Votre strategie de victoire. La seule fonction que vous aurez à modifier.
    // libre à vous d'en créer d'autres pour aérer votre code. 
    // La variable grille est un tableau à deux dimensions d'entiers, c'est la grille du tour. 
    // Un VIDE représente une case vide, 1 représente vos jetons et 2 représente les jetons adverses.
    // A vous de choisir le meilleur prochain coup !

    int meilleureClonne;
    
    meilleureClonne = choisirColonneOrdi(grille);

    // Retourne la meilleure colonne à jouer
    return meilleureClonne;
}

// La fonction principale reçoit la grille du tour et retourne le coup choisi
// Vous n'avez pas à modifier cette fonction
int main(int argc, char** argv) 
{
    t_grille grille;

    chargerGrille(argv, grille);

    return maStrategie(grille);
}

// Charge la grille du tour actuel
// Vous n'avez pas à modifier cette fonction
void chargerGrille(char** argv, t_grille grille) 
{
    for(int i = 0; i < LIGNE; i++)
        for(int j = 0; j < COLONNE; j++)
            grille[i][j] = atoi(argv[i * COLONNE + j + 1]);
}



void copieGrille(t_grille laGrille, t_grille grilleTest){
    int i, j;
    for (i=0; i<LIGNE; i++)
    {
        for (j=0; j<COLONNE; j++)
        {
            grilleTest[i][j] = laGrille[i][j];
        }
    }
}

int chercherLigne(t_grille laGrille, int col){
    int ligne = -1;
    while (ligne<LIGNE-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}

int alignementMax(t_grille laGrille, int lig, int col){
    // consiste Ã  regarder si une ligne de 4 pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt,i,j, max;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<LIGNE && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    max = cpt;
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<COLONNE && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt > max)
    {
        max = cpt;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<LIGNE && j<COLONNE && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt > max)
    {
        max = cpt;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<COLONNE && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<LIGNE && j>=0 && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt > max)
    {
        max = cpt;
    }
    return max;
}

int coupGagnant(t_grille grilleTest){
    int col, j, i;
    col = -1;
    j = 0;
    while (j<COLONNE && col == -1)
    {   
        i = chercherLigne(grilleTest, j);
        if (i != -1)
        {
            
            grilleTest[i][j] = JOUEUR;
            if (estVainqueur(grilleTest, i, j))
            {
                col = j;
            }
            grilleTest[i][j] = VIDE;
        }
        j = j+1;
    }
    return col;
}

int bloquerAdversaire(t_grille grilleTest){
    int col, j, i;
    col = -1;
    j = 0;
    while (j<COLONNE && col == -1)
    {   
        i = chercherLigne(grilleTest, j);
        if (i != -1)
        {
            
            grilleTest[i][j] = ADVERSAIRE;
            if (estVainqueur(grilleTest, i, j))
            {
                col = j;
            }
            grilleTest[i][j] = VIDE;
        }
        j = j+1;
    }
    return col;
}

bool prochainCoupPerdant(t_grille grilleTest){
    int j, i;
    bool perdant;
    perdant = false;
    j = 0;
    i = chercherLigne(grilleTest, j);
    if (i != -1)
    {
        grilleTest[i][j] = JOUEUR;
        grilleTest[i-1][j] = ADVERSAIRE;
        if (estVainqueur(grilleTest, i-1, j))
        {
            perdant = true;
        }
    }
    return perdant;
}

bool deuxPuissance4(t_grille grilleTest, int *i){
    int j, x, y, nbPuissance4, Puissane3Perdant;
    bool perdant;
    perdant = false;
    j = 0;
    nbPuissance4 = 0;
    Puissane3Perdant = 0;
    while (j<COLONNE && nbPuissance4 < 2 && Puissane3Perdant < 2)
    {
        *i = chercherLigne(grilleTest, j);
        if (*i != -1)
        {
            grilleTest[*i][j] = ADVERSAIRE;
            if (alignementMax(grilleTest, *i, j) == 3)
            {
                y = 0;
                while (y<COLONNE && Puissane3Perdant < 2)
                {
                    x = chercherLigne(grilleTest, y);
                    if (x != -1)
                    {
                        grilleTest[x][y] = ADVERSAIRE;
                        if (estVainqueur(grilleTest, *i, j))
                        {
                            Puissane3Perdant += 1;
                        }
                        grilleTest[x][y] = VIDE;
                    }
                    y += 1;
                }
            }
            if (estVainqueur(grilleTest, *i, j))
            {
                nbPuissance4 += 1;
            }
            grilleTest[*i][j] = VIDE;
        }
        j = j+1;
    }
    if (!(nbPuissance4 < 2 && Puissane3Perdant < 2))
    {
        perdant = true;
    }
    return perdant;
}


int meilleurColonne(t_grille grilleTest){
    int col, j, i, max, maxTest, jMax, jPerdant;
    max = -1;
    maxTest = -1;
    col = -1;
    j = 0;
    i = 0;
    while (j<COLONNE)
    {
        if (!(prochainCoupPerdant(grilleTest)))
        {   
            if ((!deuxPuissance4(grilleTest, &i)))
            {
                maxTest = (alignementMax(grilleTest, i, j));
                if (maxTest > max)
                {
                    max = maxTest;
                    jMax = j;
                }
                else if (maxTest == max)
                {
                    jMax = milieu(j, jMax);
                }
            }
        }
        else
        {
            jPerdant = j;
        }
        grilleTest[i-1][j] = VIDE;
        grilleTest[i][j] = VIDE;
    }
    j = j+1;
    
    if (jMax != -1)
    {
        col = jMax;
    }
    else
    {
        col = jPerdant;
    }
    return col;
}


int choisirColonneOrdi(t_grille laGrille){
    int col;
    col = -1;
    t_grille grilleTest;
    copieGrille(laGrille, grilleTest);
    col = coupGagnant(grilleTest);
    if (col == -1)
    {
        col = bloquerAdversaire(grilleTest);
        if (col == -1)
        {
            col = meilleurColonne(grilleTest);
        }
    }
    return col;
}

int milieu(int j1, int j2){
    int res;
    if (j1 == 3 || j2 == 3)
    {
        res = 3;
    }
    else if (j1 == 2 || j2 == 2)
    {
        res = 2;
    }
    else if (j1 == 4 || j2 == 4)
    {
        res = 4;
    }
    else if (j1 == 1 || j2 == 1)
    {
        res = 1;
    }
    else if (j1 == 5 || j2 == 5)
    {
        res = 5;
    }
    else if (j1 == 0 || j2 == 0)
    {
        res = 0;
    }
    else
    {
        res = 6;
    }
    return res;
}

bool estVainqueur(t_grille laGrille, int lig, int col){
    // consiste Ã  regarder si une ligne de 4 pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt,i,j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<LIGNE && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<COLONNE && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<LIGNE && j<COLONNE && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<COLONNE && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<LIGNE && j>=0 && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=4 ){
        return true;
    }
    return false;
}