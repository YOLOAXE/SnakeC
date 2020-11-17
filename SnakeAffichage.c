#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>
#include "SnakeControlleur.h"
#include "SnakeInit.h"
#include "SnakeAffichage.h"

void AfficheTimer(short int timer[], char tF)
{
	char affichageTimer[6];
	sprintf(affichageTimer, "%02d:%02d", timer[1], timer[0]);
	ChoisirCouleurDessin(COULEUR_BACKGROUND);
	RemplirRectangle(0, (TFH * tF) - (TFH * tF) / 7.5, (TT + 1) * 50, (TFH * tF) / 2);
	ChoisirCouleurDessin(COULEUR_TEXTE);
	EcrireTexte((TFL * tF) / 20, (TFH * tF) - (TFH * tF) / 22, affichageTimer, TT);
}

void AfficheScore(short int score, char tF)
{
	char affichageScore[8];
	sprintf(affichageScore, "%06d", score);
	ChoisirCouleurDessin(COULEUR_BACKGROUND);
	RemplirRectangle((TFL * tF) - (100 + (TFL * tF) / 25), (TFH * tF) - (TFH * tF) / 7.5, (TT + 1) * 50, (TFH * tF) / 2);
	ChoisirCouleurDessin(COULEUR_TEXTE);
	EcrireTexte((TFL * tF) - (90 + (TFL * tF) / 25), (TFH * tF) - (TFH * tF) / 22, affichageScore, TT);
}

void AfficheSnake(position pS[], int taille, short int posTete, char tF)
{
	int i;
	int tailleCareLargeur = ((TFL * tF) - (TFL * tF) / 13) / CARTE_TAILLE_X;
	int tailleCareHauteur = ((TFH * tF) - (TFH * tF) / 5) / CARTE_TAILLE_Y; 
	ChoisirCouleurDessin(COULEUR_SNAKE);
	for (i = posTete; i > posTete - taille; i--)
	{
		RemplirRectangle((TFL * tF) / 25 + pS[ModuloDeuxDirection(i)].pX * tailleCareLargeur, (TFH * tF) / 20 + pS[ModuloDeuxDirection(i)].pY * tailleCareHauteur, tailleCareLargeur, tailleCareHauteur);
	}
}

void AfficheSnakeExtremite(position pS[], int taille, short int posTete, char cC[][CARTE_TAILLE_Y], char tF)
{
	int i;
	float tailleCareLargeur = ((TFL * tF) - (TFL * tF) / 13) / CARTE_TAILLE_X;
	float tailleCareHauteur = ((TFH * tF) - (TFH * tF) / 5) / CARTE_TAILLE_Y;
	ChoisirCouleurDessin(COULEUR_SNAKE);
	RemplirRectangle((TFL * tF) / 25 + pS[posTete].pX * tailleCareLargeur, (TFH * tF) / 20 + pS[posTete].pY * tailleCareHauteur, tailleCareLargeur, tailleCareHauteur);
	RemplirRectangle((TFL * tF) / 25 + pS[ModuloDeuxDirection(posTete - 1)].pX * tailleCareLargeur, (TFH * tF) / 20 + pS[ModuloDeuxDirection(posTete - 1)].pY * tailleCareHauteur, tailleCareLargeur, tailleCareHauteur);
	ChoisirCouleurDessin(COULEUR_POMME);
	RemplirRectangle(((TFL * tF) / 25 + pS[posTete].pX * tailleCareLargeur) + tailleCareLargeur / 1.5f, ((TFH * tF) / 20 + pS[posTete].pY * tailleCareHauteur) + tailleCareHauteur / 4, tailleCareLargeur / 4, tailleCareHauteur / 4);
	RemplirRectangle(((TFL * tF) / 25 + pS[posTete].pX * tailleCareLargeur) + tailleCareLargeur / 3, ((TFH * tF) / 20 + pS[posTete].pY * tailleCareHauteur) + tailleCareHauteur / 4, tailleCareLargeur / 4, tailleCareHauteur / 4);
	cC[pS[posTete].pX][pS[posTete].pY] = 1;
	if (pS[ModuloDeuxDirection(posTete - taille)].pX % 2 == pS[ModuloDeuxDirection(posTete - taille)].pY % 2)
	{
		ChoisirCouleurDessin(COULEUR_GROUND2);
	}
	else
	{
		ChoisirCouleurDessin(COULEUR_GROUND);
	}
	RemplirRectangle((TFL * tF) / 25 + pS[ModuloDeuxDirection(posTete - taille)].pX * tailleCareLargeur, (TFH * tF) / 20 + pS[ModuloDeuxDirection(posTete - taille)].pY * tailleCareHauteur, tailleCareLargeur, tailleCareHauteur);
	cC[pS[ModuloDeuxDirection(posTete - taille)].pX][pS[ModuloDeuxDirection(posTete - taille)].pY] = 0;
}

void GameOver(short int score, short int timer[], char tF)
{
	char affichageTimer[13];
	char affichageScore[14];
	EffacerEcran(COULEUR_BACKGROUND);
	ChoisirCouleurDessin(COULEUR_TEXTE2);
	EcrireTexte(((TFL * tF) / 2) - 40, ((TFH * tF) / 2) - 15, "Game Over", TT);
	ChoisirCouleurDessin(COULEUR_TEXTE);
	sprintf(affichageTimer, "Temps %02d:%02d", timer[1], timer[0]);
	EcrireTexte(((TFL * tF) / 2) - 50, (TFH * tF) / 1.8f, affichageTimer, TT);
	sprintf(affichageScore, "Score %d", score);
	EcrireTexte(((TFL * tF) / 2) - 30, (TFH * tF) / 1.5f, affichageScore, TT);
}

void AffichagePomme(position p[], char tF)
{
	char i;
	float tailleCareLargeur = ((TFL * tF) - (TFL * tF) / 13) / CARTE_TAILLE_X;
	float tailleCareHauteur = ((TFH * tF) - (TFH * tF) / 5) / CARTE_TAILLE_Y;
	ChoisirCouleurDessin(COULEUR_POMME);
	for (i = 0; i < NOMBRE_MAX_POMME; i++)
	{
		RemplirRectangle((TFL * tF) / 25 + p[i].pX * tailleCareLargeur, (TFH * tF) / 20 + p[i].pY * tailleCareHauteur, tailleCareLargeur, tailleCareHauteur);
	}
	ChoisirCouleurDessin(COULEUR_POMME2);
	for (i = 0; i < NOMBRE_MAX_POMME; i++)
	{
		RemplirRectangle(((TFL * tF) / 25 + p[i].pX * tailleCareLargeur) + tailleCareLargeur / 1.5f, ((TFH * tF) / 20 + p[i].pY * tailleCareHauteur) + tailleCareHauteur / 4, tailleCareLargeur / 4, tailleCareHauteur / 4);
	}
}

void AfficheTrouDeVer(position tDV[], char tF)
{
	char i;
	float tailleCareLargeur = ((TFL * tF) - (TFL * tF) / 13) / CARTE_TAILLE_X;
	float tailleCareHauteur = ((TFH * tF) - (TFH * tF) / 5) / CARTE_TAILLE_Y;
	ChoisirCouleurDessin(COULEUR_TROUDEVER);
	for (i = 0; i < 2; i++)
	{
		RemplirRectangle((TFL * tF) / 25 + tDV[i].pX * tailleCareLargeur, (TFH * tF) / 20 + tDV[i].pY * tailleCareHauteur, tailleCareLargeur, tailleCareHauteur);
	}
	ChoisirCouleurDessin(COULEUR_TROUDEVER2);
	for (i = 0; i < 2; i++)
	{
		RemplirRectangle(((TFL * tF) / 25 + tDV[i].pX * tailleCareLargeur)+tailleCareLargeur/4, ((TFH * tF) / 20 + tDV[i].pY * tailleCareHauteur)+ tailleCareHauteur/4, tailleCareLargeur/2, tailleCareHauteur/2);
	}
}

void InitRDTrouDeVer(position tDV[], char cC[][CARTE_TAILLE_Y], char tF)
{
	char v, i, c, l;
	float tailleCareLargeur = ((TFL * tF ) - (TFL * tF) / 13) / CARTE_TAILLE_X;
	float tailleCareHauteur = ((TFH * tF) - (TFH * tF) / 5) / CARTE_TAILLE_Y;
	for (i = 0; i < 2; i++)
	{
		if(cC[tDV[i].pX][tDV[i].pY] == 3)
		{
			if (tDV[i].pX % 2 == tDV[i].pY % 2)
			{
				ChoisirCouleurDessin(COULEUR_GROUND2);
			}
			else
			{
				ChoisirCouleurDessin(COULEUR_GROUND);
			}
			RemplirRectangle((TFL * tF) / 25 + tDV[i].pX * tailleCareLargeur, (TFH * tF) / 20 + tDV[i].pY * tailleCareHauteur, tailleCareLargeur, tailleCareHauteur);
			cC[tDV[i].pX][tDV[i].pY] = 0;
		}
	}
	for (i = 0; i < 2; i++)
	{
		for (v = 0; v < TROUDEVER_MAX_TESTSPAWN; v++)
		{
			tDV[i].pX = rand() % CARTE_TAILLE_X;
			tDV[i].pY = rand() % CARTE_TAILLE_Y;
			if (cC[tDV[i].pX][tDV[i].pY] < 1)
			{
				v = TROUDEVER_MAX_TESTSPAWN;
			}

			for (c = 0; c < CARTE_TAILLE_X && v == TROUDEVER_MAX_TESTSPAWN - 1; c++)
			{
				for (l = 0; l < CARTE_TAILLE_Y; l++)
				{
					if (cC[c][l] == 0)
					{
						tDV[i].pX = c;
						tDV[i].pY = l;
						c = CARTE_TAILLE_X;
						l = CARTE_TAILLE_Y;
						v = TROUDEVER_MAX_TESTSPAWN;
					}
				}
			}
		}
		cC[tDV[i].pX][tDV[i].pY] = 3;
	}
	AfficheTrouDeVer(tDV, tF);
}

void InitFrame(char tF)
{
	char c, l;
	EffacerEcran(COULEUR_BACKGROUND);
	ChoisirCouleurDessin(COULEUR_CADRE);
	RemplirRectangle((TFL * tF) / 30, (TFH * tF) / 25, (TFL * tF) - (TFL * tF) / 17, (TFH * tF) - (TFH * tF) / 5.6);
	ChoisirCouleurDessin(COULEUR_GROUND);
	RemplirRectangle((TFL * tF) / 25, (TFH * tF) / 20, (TFL * tF) - (TFL * tF) / 13, (TFH * tF) - (TFH * tF) / 5);
	ChoisirCouleurDessin(COULEUR_GROUND2);
	for (c = 0; c < CARTE_TAILLE_X; c++)
	{
		for (l = 0; l < CARTE_TAILLE_Y; l++)
		{
			if (l % 2 == c % 2)
			{
				RemplirRectangle(((TFL * tF) / 25) + (c*(((TFL * tF) - (TFL * tF) / 13) / CARTE_TAILLE_X)), ((TFH * tF) / 20) + (l * (((TFH * tF) - (TFH * tF) / 5) / CARTE_TAILLE_Y)), ((TFL * tF) - (TFL * tF) / 13) / CARTE_TAILLE_X, ((TFH * tF) - (TFH * tF) / 5) / CARTE_TAILLE_Y);
			}
		}
	}
}

void Pause(char tF)
{
	ChoisirCouleurDessin(COULEUR_TEXTE2);
	EcrireTexte(((TFL * tF) / 2) - 40, ((TFH * tF) / 2) - 15, "PAUSE", TT);
}

void Attendre(unsigned long wait)
{
	unsigned long timer = Microsecondes();
	while(Microsecondes() - timer < wait){}
}

void Intro(char tF)
{
	char i,l;
	unsigned long temps = Microsecondes();
	char NameTotal[11] = NAME;
	char UneLettre[2];
	EffacerEcran(COULEUR_BACKGROUND);
	ChoisirCouleurDessin(COULEUR_INTRO);

	for(i = 0; i < 11;)
	{
		if(Microsecondes() - temps > TEMPS_INTRO/10)
		{
			UneLettre[0] = NameTotal[i];
			EcrireTexte((((TFL * tF) / 2) - 100)+ (i*TFL/10), ((TFH * tF) / 2) - 15, UneLettre , TT);
			temps = Microsecondes();
			i++;
		}
	}
	Attendre(TEMPS_INTRO/4);
	ChoisirCouleurDessin(COULEUR_POMME);
	RemplirRectangle((((TFL * tF) / 2) - 100), ((TFH * tF) / 2) + 5,(TT+1)*105,(TT+1)*3);

	Attendre(TEMPS_INTRO);
	for(i = 0; i < 101;i++)
	{
		ChoisirCouleurDessin(CouleurParComposante(i,0,0));
		RemplirRectangle(0,(TFH * tF) * i/100,(TFL * tF),(TFH * tF)/100);/*Haut ---> Bas*/
		RemplirRectangle(0,(TFH * tF)-((TFH * tF) * i/100),(TFL * tF),(TFH * tF)/100);/*Bas ---> Haut*/
		RemplirRectangle((TFL * tF) * i/100,0,(TFL * tF)/100,(TFH * tF));/*Gauche ---> Droite*/
		RemplirRectangle((TFL * tF)-((TFL * tF) * i/100),0,(TFL * tF)/100,(TFH * tF));/*Droite ---> Gauche*/
		Attendre(TEMPS_INTRO/100);
	}
	Attendre(TEMPS_INTRO);
	EffacerEcran(COULEUR_BACKGROUND);
	ChoisirCouleurDessin(COULEUR_INTRO);
	Attendre(TEMPS_INTRO/4);
	EcrireTexte(((TFL * tF)/20),((TFH * tF) / 20), "Echap: Quitter." , TT);
	Attendre(TEMPS_INTRO/4);
	EcrireTexte(((TFL * tF)/20),((TFH * tF) / 20)+50, "Espace : Pause / Recommencer." , TT);
	Attendre(TEMPS_INTRO/4);
	EcrireTexte(((TFL * tF)/20),((TFH * tF) / 20)+100, "Fleches Directionelles : Diriger." , TT);
	Attendre(TEMPS_INTRO/4);
	EcrireTexte(((TFL * tF)/20),((TFH * tF) / 20)+150, "+ : Agrandir la fenetre." , TT);
	Attendre(TEMPS_INTRO/4);
	EcrireTexte(((TFL * tF)/20),((TFH * tF) / 20)+200, "- : Diminuer la fenetre." , TT);
	Attendre(TEMPS_INTRO*2);
}

