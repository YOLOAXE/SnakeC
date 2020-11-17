#ifndef SNAKECONTROLLEUR_H
#define SNAKECONTROLLEUR_H

#define TFL 325							/*Largeur de base de la fenetre en pixel.(325)*/ 
#define TFH 250							/*Hauteur de base de la fenetre en pixel.(250)*/
#define TT 2							/*Taille du texte.*/
#define CARTE_TAILLE_Y 40				/*Dimension max de la carte en Hauteur.*/
#define CARTE_TAILLE_X 60				/*Dimension max de la carte en largeur.*/
#define TAILLE_BASE_SNAKE 10			/*Taille du serpent de base.*/
#define TAILLE_MAX_SNAKE 2400			/*Taille max du snake CARTE_TAILLE_Y * CARTE_TAILLE_X.*/
#define SPEED_BASE_SNAKE 100000L		/*Temps en microseconde avant d'effectuer un cycle du serpent ici 0.1s.*/
#define SPEED_BASE_TIMER 1000000L 		/*Temps en microseconde avant d'effectuer un cycle du Timer ici 1s.*/
#define TEMPS_INTRO 1000000L
#define NOMBRE_MAX_POMME 5				/*Nombre maximal de pommes pr?ent sur le terrain*/
#define POMME_MAX_TESTSPAWN 5			/*Nombre maximal de tests random position sur la carte des collisions avant de faire appara?re en brute force.*/
#define TROUDEVER_MAX_TESTSPAWN 5		/*Idem.*/
#define MULTIPLICATEUR_MAX_FENETRE 15	/*La taille maximale pour redimensionner la fen?re.*/
#define COULEUR_TEXTE 0xdedede			/*Couleur en hexad?imal appliquer ?ChoisirCouleurDessin elle remplace la fonction CouleurParComposante.*/
#define COULEUR_TEXTE2 0xde0000			/*Idem.*/
#define COULEUR_POMME 0xff0000			/*Idem.*/
#define COULEUR_POMME2 0xffffff			/*Idem.*/
#define COULEUR_GROUND 0x00912c			/*Idem.*/
#define COULEUR_GROUND2 0x00c73c		/*Idem.*/
#define COULEUR_CADRE 0x004491			/*Idem.*/
#define COULEUR_SNAKE 0xfcba03			/*Idem.*/
#define COULEUR_TROUDEVER 0x0000ff		/*Idem.*/
#define COULEUR_TROUDEVER2 0x0050dd		/*Idem.*/
#define COULEUR_BACKGROUND 0x000000		/*Idem.*/
#define COULEUR_INTRO 0xffffff			/*Idem.*/
#define NAME "Dark Snake"				/*Le nom du jeux (Reference a dark soul).*/

typedef struct
{
	signed char pX;						/*La position x.*/
	signed char pY;						/*La position y.*/
}position;								/*La structure utilise par tous les objets du jeu pour les places sur la carte des collisions.*/

void AddTimer(short int tabTime[], short int taille);
/*
Incr?ente 1 a un tableau dont on a d?ini ? taille arriver ?60 la fonction incr?ente 1 dans la prochaine valeur du tableau.
*/

short int ModuloDeuxDirection(short int pos);
/*
Fait le modulo de TAILLE_MAX_SNAKE si la valeur est n?ative alors on repars de la fin de TAILLE_MAX_SNAKE et on d?r?ente la valeur.
La fonction sert ?lire le tableau de structure du snake car il se d?lace dans ce tableau.
*/

void OnColliderEnter(position pS[], short int posTete, short int* taille, char* mode, position pP[], short int* score, char cC[][CARTE_TAILLE_Y], position tDV[], short int timer[], char tF);
/*
Detecte les collisions entre les differents elements de la carte et g?e les ??ements li? ?c'est collision (Game Over?,Taille Snake++, teleportation) 
|| ps = position du snake || posTete = la position de la tete dans le tableaux || taille = taille du snake || mode = mode de jeux || pP = la position des pommes || 
score = le score du joueur || cC = carte des collisions || tDV = la position des trou de ver || timer = le tableaux qui contient les infos du chronometre || tF = la taille de la fenetre ||.
*/

void DeplacementSnake(position dS, position pS[], short int* posTete);
/*
Prends le vecteur de direction ds et il l'applique au prochain element de pS(la position du serpent) grace a posTete(la position de la tete) que l'on incr?ente de 1.
*/

signed char Input(signed char mode, position* dS,char * taille,char * wM);
/*
Cette fonction renvoie ce qu'on lui a envoye si aucune touche valide na ??appuye,
elle sert ?la fois ?contr?er le serpent grace ?ds(vecteur direction) et ?modifier le mode du jeu(Pause = 1, Quitter = -1 ,en jeu = 0).
*/

#endif 