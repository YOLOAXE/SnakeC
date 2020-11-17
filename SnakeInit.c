#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "SnakeControlleur.h"
#include "SnakeInit.h"
#include "SnakeAffichage.h"

void SnakeInitPos(position p[], char cC[][CARTE_TAILLE_Y])
{
	int i;
	for (i = -1; i < TAILLE_BASE_SNAKE; i++)
	{
		p[ModuloDeuxDirection(i)].pX = CARTE_TAILLE_X / 2;
		p[ModuloDeuxDirection(i)].pY = CARTE_TAILLE_Y / 2;
		cC[CARTE_TAILLE_X / 2][CARTE_TAILLE_Y / 2] = 1;
	}
}

void PommeInitPosElement(position p[], short int pos, char cC[][CARTE_TAILLE_Y], char tF)
{
	char v, c, l;
	for (v = 0; v < POMME_MAX_TESTSPAWN; v++)
	{
		p[pos].pX = rand() % CARTE_TAILLE_X;
		p[pos].pY = rand() % CARTE_TAILLE_Y;

		if (cC[p[pos].pX][p[pos].pY] < 1)
		{
			v = POMME_MAX_TESTSPAWN;
		}

		for (c = 0; c < CARTE_TAILLE_X && v == POMME_MAX_TESTSPAWN - 1; c++)
		{
			for (l = 0; l < CARTE_TAILLE_Y; l++)
			{
				if (cC[c][l] == 0)
				{
					p[pos].pX = c;
					p[pos].pY = l;
					c = CARTE_TAILLE_X;
					l = CARTE_TAILLE_Y;
					v = POMME_MAX_TESTSPAWN;
				}
			}
		}
	}
	cC[p[pos].pX][p[pos].pY] = 2;
	AffichagePomme(p, tF);
}

void PommeInitPos(position p[], char cC[][CARTE_TAILLE_Y])
{
	char i, v;
	for (i = 0; i < NOMBRE_MAX_POMME; i++)
	{
		for (v = 0; v < 5; v++)
		{
			p[i].pX = rand() % CARTE_TAILLE_X;
			p[i].pY = rand() % CARTE_TAILLE_Y;
			if (cC[p[i].pX][p[i].pY] < 1)
			{
				v = 5;
			}
		}
		cC[p[i].pX][p[i].pY] = 2;
	}
}

void InitCarteCollision(char cC[][CARTE_TAILLE_Y])
{
	char l, c;
	for (c = 0; c < CARTE_TAILLE_X; c++)
	{
		for (l = 0; l < CARTE_TAILLE_Y; l++)
		{
			cC[c][l] = 0;
		}
	}
}
void ResetGame(char cC[][CARTE_TAILLE_Y],position pS[],position pP[],position tDV[],short int* taille, short int* posTete,short int timer[],short int* score,char tF)
{
	char i;
	for(i = 0;i < 3;i++)
	{
		timer[i] = 0;	
	}							
	*score = 0;											
	*posTete = TAILLE_BASE_SNAKE - 1;				
	*taille = TAILLE_BASE_SNAKE;		
	InitCarteCollision(cC);								
	PommeInitPos(pP, cC);						
	SnakeInitPos(pS, cC);
	InitRDTrouDeVer(tDV, cC, tF);	
	InitFrame(tF);											
	AfficheTimer(timer, tF);								
	AfficheScore(*score, tF);
	AffichagePomme(pP, tF);
	AfficheSnake(pS, *taille, *posTete, tF);
	AfficheTrouDeVer(tDV, tF);
}

char RealocTailleFenetre(char taille)
{
	FermerGraphique();
	InitialiserGraphique();	
	CreerFenetre(100, 100, (TFL * taille), (TFH * taille));	
	ChoisirTitreFenetre(NAME);
	return taille;
}