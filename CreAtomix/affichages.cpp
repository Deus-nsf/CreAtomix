
// Auteur : Alfiguigui Mehdi
// Date : 25/11/2012
// Nom du fichier : affichages.cpp
// Description : ici sont regroupés les fonctions d'affichage lors d'une partie en cours

#include "includes.h"



// affichage du fond dépendant du niveau
void Afficher_Fond(struct JEU* stJeu)
{
	if (stJeu->stNiveauActuel.NumeroNiveau < 5)
		stJeu->stData_SFML.Fenetre.draw( stJeu->stGraph.Sprites[Fond_ecran_2] );
	else
		stJeu->stData_SFML.Fenetre.draw( stJeu->stGraph.Sprites[Fond_ecran_3] );
}



// affichage de la map
void Afficher_Map(struct JEU* stJeu)
{
	int y = 0, x = 0;
	const float fMapPosX = 350, fMapPosY = 50;

	for (y = 0; y < 13; ++y)
	{
		for (x = 0; x < 14; ++x)
		{
			// si il y a un sprite à la case de la map alors on affiche
			if ( stJeu->stNiveauActuel.Map[y][x].pSprite != NULL )
			{
				// affichage du sol dépendant du niveau
				if (stJeu->stNiveauActuel.NumeroNiveau < 5)
				{
					stJeu->stGraph.Sprites[Sol_1].setPosition(
						fMapPosX + (x*TAILLE_SPRITE), fMapPosY + (y*TAILLE_SPRITE) );
					stJeu->stData_SFML.Fenetre.draw( stJeu->stGraph.Sprites[Sol_1] );
				}
				else
				{
					stJeu->stGraph.Sprites[Sol_3].setPosition(
						fMapPosX + (x*TAILLE_SPRITE), fMapPosY + (y*TAILLE_SPRITE) );
					stJeu->stData_SFML.Fenetre.draw( stJeu->stGraph.Sprites[Sol_3] );
				}
			}
		}
	}


	for (y = 0; y < 13; ++y)
	{
		for (x = 0; x < 14; ++x)
		{
			// si il y a un sprite à la case de la map alors on affiche
			if ( stJeu->stNiveauActuel.Map[y][x].pSprite != NULL )
			{
				// si la case n'est pas du sol, alors on affiche (mur ou atome)
				if( !( (stJeu->stNiveauActuel.Map[y][x].eSignature >= Sol_1) && (stJeu->stNiveauActuel.Map[y][x].eSignature <= Sol_3) ) )
				{
					stJeu->stNiveauActuel.Map[y][x].pSprite->setPosition(
						(float)stJeu->stNiveauActuel.Map[y][x].x, (float)stJeu->stNiveauActuel.Map[y][x].y );

					stJeu->stData_SFML.Fenetre.draw( *stJeu->stNiveauActuel.Map[y][x].pSprite );
				}	
			}
		}
	}
}



// affichage de la molécule victoire
void Afficher_Molecule_Victoire(struct JEU* stJeu)
{
	int iCaseActuelle = 0;
	int y = 0, x = 0;

	for (y = 0; y < stJeu->stNiveauActuel.iTailleMolY; ++y)
	{
		for (x = 0; x < stJeu->stNiveauActuel.iTailleMolX; ++x)
		{
			// si il y a un sprite à la case du tableau dynamique de la molécule victoire alors on affiche
			if ( stJeu->stNiveauActuel.MoleculeVictoire[ (y*stJeu->stNiveauActuel.iTailleMolX) + x ].pSprite != NULL )
			{
				iCaseActuelle = (y*stJeu->stNiveauActuel.iTailleMolX) + x;

				stJeu->stNiveauActuel.MoleculeVictoire[iCaseActuelle].pSprite->setPosition(
					(float)stJeu->stNiveauActuel.MoleculeVictoire[iCaseActuelle].x,
					(float)stJeu->stNiveauActuel.MoleculeVictoire[iCaseActuelle].y );

				stJeu->stData_SFML.Fenetre.draw(
					*stJeu->stNiveauActuel.MoleculeVictoire[iCaseActuelle].pSprite );
			}
		}
	}
}



// affiche le curseur de selection
void Afficher_Curseur(struct JEU* stJeu)
{
	stJeu->stCurseur.ShapeCurseur.setPosition(stJeu->stCurseur.x, stJeu->stCurseur.y);
	stJeu->stData_SFML.Fenetre.draw( stJeu->stCurseur.ShapeCurseur );
}



// affiche les textes
void Afficher_Textes(struct JEU* stJeu)
{
	const char* szChaineMolecule = "Molécule à reproduire :";
	char szChaine[50] = "";
	int iMinutes = 0, iSecondes = 0;


	// gestion affichage niveau
	sprintf(szChaine, "Niveau %d", stJeu->stNiveauActuel.NumeroNiveau);
	
	stJeu->stData_SFML.Texte[0].setString( szChaine );
	stJeu->stData_SFML.Fenetre.draw( stJeu->stData_SFML.Texte[0] );


	// gestion affichage score
	sprintf(szChaine, "Score :\n%d", stJeu->stJoueur.Score);

	stJeu->stData_SFML.Texte[1].setString( szChaine );
	stJeu->stData_SFML.Fenetre.draw( stJeu->stData_SFML.Texte[1] );


	// gestion affichage texte "molecule à reproduire"
	stJeu->stData_SFML.Texte[2].setString( szChaineMolecule );
	stJeu->stData_SFML.Fenetre.draw( stJeu->stData_SFML.Texte[2] );


	// gestion affichage timer
	iMinutes =
		( stJeu->stNiveauActuel.iTempsMax -
		(int)stJeu->stNiveauActuel.HorlogeNiveau.getElapsedTime().asSeconds() ) / 60;

	iSecondes =
		stJeu->stNiveauActuel.iTempsMax -
		(int)stJeu->stNiveauActuel.HorlogeNiveau.getElapsedTime().asSeconds() -
		iMinutes*60;

	sprintf(szChaine, "Temps restant :\n%2d :%3d", iMinutes, iSecondes);

	stJeu->stData_SFML.Texte[3].setString( szChaine );
	stJeu->stData_SFML.Fenetre.draw( stJeu->stData_SFML.Texte[3] );
}



// affiche toutes les données visuelles nécessaires d'un niveau en cours
void Afficher_Niveau_En_Cours(struct JEU* stJeu)
{
	Afficher_Fond( stJeu );

	Afficher_Map( stJeu );
	
	Afficher_Molecule_Victoire( stJeu );

	Afficher_Curseur( stJeu );

	Afficher_Textes( stJeu );
}