#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>
#include "SnakeControlleur.h"
#include "SnakeInit.h"
#include "SnakeAffichage.h"

int main(int argc, char* argv[])
{
	unsigned long tempsSnake = Microsecondes();						/*C'est la variable du temps du serpent qui correspond ?la diff?ence entre le temps qui s'est pass?et Microsecondes().*/
	unsigned long tempsTimer = Microsecondes();						/*C'est la variable du temps du chronom?re qui correspond ?la diff?ence entre le temps qui s'est pass?et Microsecondes().*/
	signed char mode = 0;											/*Le mode de jeu(Quitter = -1,Enjeux = 0,Pause = 1,FinPause = 2,GameOver >= 20).*/
	char tailleFenetre = 4;		
	char waitMove = 0;												/*la taille de la fenetre est definie par le joueur des quil lance le jeu.*/
	char CarteCollision[CARTE_TAILLE_X][CARTE_TAILLE_Y];			/*la carte collision sert ?optimiser les collisions entre les elements et donc ne pas teste toutes les positions*/
	short int timer[3] = { 0,0,0 };									/*Le Tableaux qui contient -> seconde/minute/heure, il est modifie par la fonction AddTimer().*/
	short int score = 0;											/*Le score du joueur qui est affiche en jeu et d? que le joueur perd il est modifi?par la fonction OnColliderEnter().*/
	short int posTeteSnake = TAILLE_BASE_SNAKE - 1;					/*La position de la tete dans le tableau de structure du serpent.*/
	short int tailleSnake = TAILLE_BASE_SNAKE;						/*La taille du serpent*/
	position snakePos[TAILLE_MAX_SNAKE];							/*Le tableau de structure position du serpent.*/
	position directionSnake = { 0,1 };								/*Le vecteur de direction du serpent il est utiliser avec la fonction DeplacementSnake().*/
	position pommeSnake[NOMBRE_MAX_POMME];							/*Le tableau de structure position des pommes.*/
	position trouDeVer[2];											/*Le tableau de structure position des portails les du trou de ver.*/

	srand(time(NULL));												/*Initialise la fonction srand sur le temps actuel.*/
	InitCarteCollision(CarteCollision);								/*Initialise la CarteCollision.*/
	PommeInitPos(pommeSnake, CarteCollision);						/*Initialise la position des pommes.*/
	SnakeInitPos(snakePos, CarteCollision);							/*Initialise la position du serpent.*/
	InitialiserGraphique();											/*Initialise l'interface graphique.*/

	if (argc >= 2)
	{
		if (atoi(argv[1]) < MULTIPLICATEUR_MAX_FENETRE && atoi(argv[1]) > 0)
		{
			tailleFenetre = atoi(argv[1]);									/*On d?init la taille de la fen?re en fonction du choix du joueur.*/
		}
	}

	CreerFenetre(100, 100, (TFL * tailleFenetre), (TFH * tailleFenetre));	/*On cree la fen?re avec les dimensions choisie par le joueur.*/
	ChoisirTitreFenetre(NAME);
	Intro(tailleFenetre);
	InitFrame(tailleFenetre);												/*Dessine le damier.*/
	AfficheTimer(timer, tailleFenetre);								
	AfficheScore(score, tailleFenetre);
	AffichagePomme(pommeSnake, tailleFenetre);
	InitRDTrouDeVer(trouDeVer, CarteCollision, tailleFenetre);				/*Affiche et initialise les portails du trou de ver.*/

	while (mode != -1)														/*-1 = Quitter*/
	{
		mode = Input(mode, &directionSnake, &tailleFenetre, &waitMove);				/*les entre clavier du joueur.*/
		if (Microsecondes() - tempsSnake > SPEED_BASE_SNAKE / ((((float)timer[1] + ((float)timer[0] / 60)) / 4) + 1) && mode < 5 && mode != -1) /*((((float)timer[1] + ((float)timer[0] / 60)) / 4) + 1) = La gestion de la vitesse du serpent par rapport au chronometre.*/
		{
			waitMove = 0;/*Evite que le serpant ce retorune suir lui meme a la meme frame*/
			if (mode == 2)/*FinPause = 2 on r?ffiche tout.*/
			{
				InitFrame(tailleFenetre);
				AfficheSnake(snakePos, tailleSnake, posTeteSnake, tailleFenetre);
				AfficheTimer(timer, tailleFenetre);
				AfficheScore(score, tailleFenetre);
				AffichagePomme(pommeSnake, tailleFenetre);
				AfficheTrouDeVer(trouDeVer, tailleFenetre);
				mode = 0;
			}
			if(mode == 4)
			{
				ResetGame(CarteCollision, snakePos, pommeSnake, trouDeVer, &tailleSnake, &posTeteSnake,timer,&score,tailleFenetre);
				mode = 0;
			}
			if (mode != 1)/*si ce n'est pas la pause alors le serpent ce deplace teste les collision et s'affiche.*/
			{
				DeplacementSnake(directionSnake, snakePos, &posTeteSnake);
				OnColliderEnter(snakePos, posTeteSnake, &tailleSnake, &mode, pommeSnake, &score, CarteCollision, trouDeVer, timer, tailleFenetre);
				if (mode < 20)/*Lorsque le serpent est K.O on ne le fait pas avence. le mode peut-?re mi ?une valeur sup?ieure ou ?ale ?20 dans la fonction OnColliderEnter().*/
				{
					AfficheSnakeExtremite(snakePos, tailleSnake, posTeteSnake, CarteCollision, tailleFenetre);
				}
			}
			else/*Pause*/
			{
				Pause(tailleFenetre);
			}
			tempsSnake = Microsecondes();/*On reinitialise la difference.*/
		}

		if (Microsecondes() - tempsTimer > SPEED_BASE_TIMER && mode != 1 && mode < 5 && mode > -1)/*On attend SPEED_BASE_TIMER en microsecond avant de pouvoir ex?ute ce qui y a dans la condition.*/
		{
			AddTimer(timer, 2);/*On ajoute 1 au chronom?re.*/
			AfficheTimer(timer, tailleFenetre);
			tempsTimer = Microsecondes();/*On reinitialise la difference.*/
		}
	}
	FermerGraphique();/*On ferme l'interface Graphique*/

	return EXIT_SUCCESS;
}
