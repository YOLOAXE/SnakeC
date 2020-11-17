#ifndef SNAKEINIT_H
#define SNAKEINIT_H

void SnakeInitPos(position p[], char cC[][CARTE_TAILLE_Y]);
/*
Initialise la position des éléments du serpent avec ces collisions au milieu de l'écran
*/

void PommeInitPosElement(position p[], short int pos, char cC[][CARTE_TAILLE_Y], char tF);
/*
Initialise la position d'un élément du tableau de structure pommes avec ces collisions au hasard, 
après un certain nombre d'essais(POMME_MAX_TESTSPAWN) non concluent car un element se trouve déjà au même endroit, 
la fonction va tester toutes les cases du tableau des collisions pour voir s'il trouve un emplacement vide
*/

void PommeInitPos(position p[], char cC[][CARTE_TAILLE_Y]);
/*
Initialise la position des éléments des pommes avec ces collisions au hasard
*/

void InitCarteCollision(char cC[][CARTE_TAILLE_Y]);
/*
Initialise le tableau à zéro pour l'effacer de toute collision
*/

void ResetGame(char cC[][CARTE_TAILLE_Y],position pS[],position pP[],position tDV[],short int* taille, short int* posTete,short int timer[],short int* score,char tF);
/*
Reinitialise les paramètres du jeu pour redémarrer une partie.
*/

char RealocTailleFenetre(char taille);

#endif 