#ifndef SNAKEAFFICHAGE_H
#define SNAKEAFFICHAGE_H

void AfficheTimer(short int timer[], char tF);
/*
Cette fonction affiche le temps en bas � gauche de l'�cran la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void AfficheScore(short int score, char tF);
/*
Cette fonction affiche le Score en bas � droite de l'�cran la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void AfficheSnake(position pS[], int taille, short int posTete, char tF);
/*
Cette fonction affiche le serpent en entier sur la carte cette fonction est utilis�e pour l'initialisation ou la pause,
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void AfficheSnakeExtremite(position pS[], int taille, short int posTete, char cC[][CARTE_TAILLE_Y], char tF);
/*
Cette fonction affiche la tete et efface la queue du serpent,
la carte des collisions est modifi�es pour correspondre � ce qui est affich� � l'�cran,
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void GameOver(short int score, short int timer[], char tF);
/*
Quand le joueur perd on affiche l'�cran de GameOver qui contient son score et son temps avant de perdre,
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void AffichagePomme(position p[], char tF);
/*
Cette fonction affiche toutes les pommes du tableau de structure des pommes sur la carte,
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void AfficheTrouDeVer(position tDV[], char tF);
/*
Cette fonction affiche les deux portaille du tou de ver,
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void InitRDTrouDeVer(position tDV[], char cC[][CARTE_TAILLE_Y], char tF);
/*
Cette fonction change la position des trous de ver s'ils sont d�j� exist�s et en initialise deux � des nouveaux emplacements random,
apr�s un certain nombre d'essais(TROUDEVER_MAX_TESTSPAWN) non concluent car un element se trouve d�j� au m�me endroit,
la fonction va tester toutes les cases du tableau des collisions pour voir s'il trouve un emplacement vide pour chacun des deux elements,
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void InitFrame(char tF);
/*
Cette fonction affiche un damier sur lequel le serpent va ce deplace,
elle est utilise en debut de partie ou a la pause,
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void Pause(char tF);
/*
Cette fonction affiche un texte de pause pour avertir le joueur que son action(pause) a bien ete r�alis�.
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/

void Attendre(unsigned long wait);
/*
Attendre en microseconde
*/

void Intro(char tF);
/*
Affiche l'intro du snake,
la zone d'affichage se redimensionne en fonction de la taille de l'�cran.
*/


#endif 