
// Auteur : Alfiguigui Mehdi
// Date : 24/11/2012
// Nom du fichier : gestion_curseur.cpp
// Description : les fonctions de gestion du déplacement du curseur, de collisions, de saisie, etc...

#include "includes.h"



// ces fonctions detectent les collisions entre le curseur, et les éléments de la map
char Tester_Collisions_Gauche(struct JEU* stJeu)
{
	// si la case a gauche n'est pas un sol et que mon curseur possède un sprite, alors il y a collision
	if( (stJeu->stNiveauActuel.Map[ stJeu->stCurseur.iCaseY ][ stJeu->stCurseur.iCaseX - 1 ].eSignature
		>= Mur_1) && (stJeu->stCurseur.ElementSaisi == 1) )
		return 1;
	// sinon il n'y a pas collision
	else
		return 0;
}

char Tester_Collisions_Haut(struct JEU* stJeu)
{
	if( (stJeu->stNiveauActuel.Map[ stJeu->stCurseur.iCaseY - 1 ][ stJeu->stCurseur.iCaseX ].eSignature
		>= Mur_1) && (stJeu->stCurseur.ElementSaisi == 1) )
		return 1;
	else
		return 0;
}

char Tester_Collisions_Droite(struct JEU* stJeu)
{
	if( (stJeu->stNiveauActuel.Map[ stJeu->stCurseur.iCaseY ][ stJeu->stCurseur.iCaseX + 1 ].eSignature
		>= Mur_1) && (stJeu->stCurseur.ElementSaisi == 1) )
		return 1;
	else
		return 0;
}

char Tester_Collisions_Bas(struct JEU* stJeu)
{
	if( (stJeu->stNiveauActuel.Map[ stJeu->stCurseur.iCaseY + 1 ][ stJeu->stCurseur.iCaseX ].eSignature
		>= Mur_1) && (stJeu->stCurseur.ElementSaisi == 1) )
		return 1;
	else
		return 0;
}



// déplacement du curseur
void Deplacer_Curseur(struct JEU* stJeu)
{
	const int iInterTempsMs = 1;	// valeur "symbolyque" puisque l'application est verouillée a 120 FPS
	const int iDecalage = 8;	// 1, 2, 4, 8, 16, ou 32 (vitesse de déplacement curseur)

	// si le curseur est en mouvement
	if ( stJeu->stCurseur.enMouvement == 1 )
	{
		// et que l'intervalle de temps a été dépassé et qu'on peut encore parcourir une distance
		if ( (stJeu->stData_SFML.Horloge.getElapsedTime().asMilliseconds() > iInterTempsMs) && (stJeu->stCurseur.iMaxDist > 0) )
		{
			// alors on bouge à gauche si le mouvement est vers la gauche tant qu'on est dans la map
			if ( (stJeu->stCurseur.gauche == 1) && (stJeu->stCurseur.iCaseX > 0) )
			{
				// si il y a collision, alors on ne peut plus parcourir de distance
				if ( Tester_Collisions_Gauche(stJeu) )
					stJeu->stCurseur.iMaxDist = 0;
				// sinon on déplace le curseur et on reduit du même offset la distance max que l'on peut parcourir
				else
				{
					stJeu->stCurseur.x -= iDecalage;
					stJeu->stCurseur.iMaxDist -= iDecalage;

					// a chaque fois que le curseur à parcouru la taille d'un sprite
					if ( (stJeu->stCurseur.iMaxDist % TAILLE_SPRITE) == 0 )
					{
						if (stJeu->stCurseur.ElementSaisi == 1)
						{
							struct ELEMENT stTemp;
							stTemp = stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX - 1];

							stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX - 1] =
								stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX];

							stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX] = stTemp;
						}

						// on modifie le numéro qui correspond à la case de la map
						--stJeu->stCurseur.iCaseX;
					}
				}
			}

			else if ( (stJeu->stCurseur.haut == 1) && (stJeu->stCurseur.iCaseY > 0) )
			{
				if ( Tester_Collisions_Haut(stJeu) )
					stJeu->stCurseur.iMaxDist = 0;
				else
				{
					stJeu->stCurseur.y -= iDecalage;
					stJeu->stCurseur.iMaxDist -= iDecalage;

					if ( (stJeu->stCurseur.iMaxDist % TAILLE_SPRITE) == 0 )
					{
						if (stJeu->stCurseur.ElementSaisi == 1)
						{
							struct ELEMENT stTemp;
							stTemp = stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY - 1][stJeu->stCurseur.iCaseX];

							stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY - 1][stJeu->stCurseur.iCaseX] =
								stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX];

							stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX] = stTemp;
						}

						--stJeu->stCurseur.iCaseY;
					}
				}
			}

			else if ( (stJeu->stCurseur.droite == 1) && (stJeu->stCurseur.iCaseX < 13) )
			{
				if ( Tester_Collisions_Droite(stJeu) )
					stJeu->stCurseur.iMaxDist = 0;
				else
				{
					stJeu->stCurseur.x += iDecalage;
					stJeu->stCurseur.iMaxDist -= iDecalage;

					if ( (stJeu->stCurseur.iMaxDist % TAILLE_SPRITE) == 0 )
					{
						if (stJeu->stCurseur.ElementSaisi == 1)
						{
							struct ELEMENT stTemp;
							stTemp = stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX + 1];

							stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX + 1] =
								stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX];

							stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX] = stTemp;
						}

						++stJeu->stCurseur.iCaseX;
					}
				}
			}

			else if ( (stJeu->stCurseur.bas == 1) && (stJeu->stCurseur.iCaseY < 12) )
			{
				if ( Tester_Collisions_Bas(stJeu) )
					stJeu->stCurseur.iMaxDist = 0;
				else
				{
					stJeu->stCurseur.y += iDecalage;
					stJeu->stCurseur.iMaxDist -= iDecalage;

					if ( (stJeu->stCurseur.iMaxDist % TAILLE_SPRITE) == 0 )
					{
						if (stJeu->stCurseur.ElementSaisi == 1)
						{
							struct ELEMENT stTemp;
							stTemp = stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY + 1][stJeu->stCurseur.iCaseX];

							stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY + 1][stJeu->stCurseur.iCaseX] =
								stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX];

							stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX] = stTemp;
						}

						++stJeu->stCurseur.iCaseY;
					}
				}
			}

			else
				stJeu->stCurseur.iMaxDist = 0;
			
			// déplacement de l'atome saisi
			if ( stJeu->stCurseur.ElementSaisi == 1 )
			{
				stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX].x =
					(int)stJeu->stCurseur.x - 2;
				stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX].y =
					(int)stJeu->stCurseur.y - 2;
			}


			stJeu->stData_SFML.Horloge.restart();
		}

		if (stJeu->stCurseur.iMaxDist == 0)
		{
			stJeu->stCurseur.gauche = 0;
			stJeu->stCurseur.haut = 0;
			stJeu->stCurseur.droite = 0;
			stJeu->stCurseur.bas = 0;

			stJeu->stCurseur.enMouvement = 0;
		}
	}
}



// permet de stocker un atome dans le curseur pour le déplacer
void Saisir_Atome(struct JEU* stJeu)
{
	if ( (stJeu->stCurseur.enMouvement == 0) &&
		(stJeu->stNiveauActuel.Map[stJeu->stCurseur.iCaseY][stJeu->stCurseur.iCaseX].estAtome == 1) )
	{
		stJeu->stCurseur.ShapeCurseur.setOutlineColor(sf::Color::Green);
		stJeu->stCurseur.ElementSaisi = 1;
	}
}



// permet de poser un atome sur la map
void Poser_Atome(struct JEU* stJeu)
{
	if ( stJeu->stCurseur.enMouvement == 0 )
	{
		stJeu->stCurseur.ShapeCurseur.setOutlineColor(sf::Color::Red);
		stJeu->stCurseur.ElementSaisi = 0;

		stJeu->stNiveauActuel.cVictoire = Verifier_Victoire(stJeu);
	}
}