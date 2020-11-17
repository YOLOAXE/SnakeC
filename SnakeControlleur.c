#include "SnakeControlleur.h"
#include "SnakeInit.h"
#include "SnakeAffichage.h"

void AddTimer(short int tabTime[], short int taille)
{
	short int i;
	tabTime[0]++;
	for (i = 0; i < taille; i++)
	{
		if (tabTime[i] >= 60)
		{
			tabTime[i] = 0;
			tabTime[i + 1]++;
		}
	}
}

short int ModuloDeuxDirection(short int pos)
{
	if (pos >= 0)
	{
		return pos % TAILLE_MAX_SNAKE;
	}
	else
	{
		return TAILLE_MAX_SNAKE + pos;
	}
}

void OnColliderEnter(position pS[], short int posTete, short int* taille, char* mode, position pP[], short int* score, char cC[][CARTE_TAILLE_Y], position tDV[], short int timer[], char tF)
{
	short int i;
	if (pS[posTete].pX > CARTE_TAILLE_X - 1 || pS[posTete].pX < 0 || pS[posTete].pY > CARTE_TAILLE_Y - 1 || pS[posTete].pY < 0)
	{
		GameOver(*score, timer, tF);
		*mode = 20;
	}
	if (cC[pS[posTete].pX][pS[posTete].pY] == 1)
	{
		GameOver(*score, timer, tF);
		*mode = 20;
	}
	if (cC[pS[posTete].pX][pS[posTete].pY] == 2)
	{
		*score += 5;
		AfficheScore(*score, tF);
		*taille += 2;
		cC[pS[posTete].pX][pS[posTete].pY] = 0;
		for (i = 0; i < NOMBRE_MAX_POMME; i++)
		{
			if (pS[posTete].pX == pP[i].pX && pS[posTete].pY == pP[i].pY)
			{
				PommeInitPosElement(pP, i, cC, tF);
				return;
			}
		}
	}
	if (cC[pS[posTete].pX][pS[posTete].pY] == 3)
	{
		if (pS[posTete].pX == tDV[0].pX && pS[posTete].pY == tDV[0].pY)
		{
			pS[posTete].pX = tDV[1].pX;
			pS[posTete].pY = tDV[1].pY;
			cC[tDV[1].pX][tDV[1].pY] = 0;
		}
		else
		{
			pS[posTete].pX = tDV[0].pX;
			pS[posTete].pY = tDV[0].pY;
			cC[tDV[0].pX][tDV[0].pY] = 0;
		}
		InitRDTrouDeVer(tDV, cC, tF);
	}
}

void DeplacementSnake(position dS, position pS[], short int* posTete)
{
	pS[ModuloDeuxDirection(*posTete + 1)].pX = pS[*posTete].pX + dS.pX;
	pS[ModuloDeuxDirection(*posTete + 1)].pY = pS[*posTete].pY + dS.pY;
	*posTete = ModuloDeuxDirection(*posTete + 1);
}

signed char Input(signed char mode, position* dS,char * taille,char * wM)
{
	short int key;
	if (ToucheEnAttente())
	{
		key = Touche();
		/*printf("%d \n",key);  KeySym*/
		if (mode < 20)
		{
			if (key == -229)/*Escape*/
			{
				return -1;
			}
			else if (key == 32)/*Space bar*/
			{
				if (mode == 1)
				{
					return 2;
				}
				else
				{
					return 1;
				}
			}
			else if (key == -174)/*Haut*/
			{
				if (dS->pY != 1 && *wM == 0)
				{
					dS->pX = 0;
					dS->pY = -1;
					*wM = 1;
				}
			}
			else if (key == -172)/*Bas*/
			{
				if (dS->pY != -1 && *wM == 0)
				{
					dS->pX = 0;
					dS->pY = 1;
					*wM = 1;
				}
			}
			else if (key == -175)/*Gauche*/
			{
				if (dS->pX != 1 && *wM == 0)
				{
					dS->pX = -1;
					dS->pY = 0;
					*wM = 1;
				}
			}
			else if (key == -173)/*Droite*/
			{
				if (dS->pX != -1 && *wM == 0)
				{
					dS->pX = 1;
					dS->pY = 0;
					*wM = 1;
				}
			}
			else if (key == -85 || key == 43 && *taille < MULTIPLICATEUR_MAX_FENETRE)
			{
				*taille = RealocTailleFenetre(*taille+1);
				return 2;
			}
			else if (key == -83 || key == 45 && *taille > 1)
			{
				*taille = RealocTailleFenetre(*taille-1);
				return 2;
			}
		}
		else
		{
			if (key == -229)/*Escape*/
			{
				return -1;
			}
			else if (key == 32)/*Space bar*/
			{
				return 4;
			}
		}

	}
	return mode;
}
