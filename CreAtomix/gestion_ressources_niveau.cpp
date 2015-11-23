
// Auteur : Alfiguigui Mehdi
// Date : 25/11/2012
// Nom du fichier : gestion_ressources_niveau.cpp
// Description : ce sont les fonctions de gestion des ressources d'un niveau

#include "includes.h"



// lecture des données de la map
void Lire_Map(struct JEU* stJeu, FILE* pFluxNiveau)
{
	int y = 0, x = 0;
	int iValeurMap = 0;
	const int iMapPosX = 350, iMapPosY = 50;

	// balise
	while (fgetc(pFluxNiveau) != '*');

	for (y = 0; y < 13; ++y)
	{
		for (x = 0; x < 14; ++x)
		{
			fscanf(pFluxNiveau, "%d", &iValeurMap);

			if ( iValeurMap != 88 )
			{
				stJeu->stNiveauActuel.Map[y][x] = stJeu->stTabElements[iValeurMap];
				stJeu->stNiveauActuel.Map[y][x].x = iMapPosX + x*TAILLE_SPRITE;
				stJeu->stNiveauActuel.Map[y][x].y = iMapPosY + y*TAILLE_SPRITE;
			}
		}
	}
}



// placement du curseur
void Placer_Curseur(struct JEU* stJeu)
{
	const float fMapPosX = 576, fMapPosY = 276;
	const float fBordure = 2.0f;

	// gestion curseur
	stJeu->stCurseur.ElementSaisi = 0;

	stJeu->stCurseur.x = fMapPosX;
	stJeu->stCurseur.y = fMapPosY;

	stJeu->stCurseur.ShapeCurseur.setSize(sf::Vector2f(TAILLE_SPRITE - fBordure*2, TAILLE_SPRITE - fBordure*2));
	stJeu->stCurseur.ShapeCurseur.setOutlineColor(sf::Color::Red);
	stJeu->stCurseur.ShapeCurseur.setOutlineThickness(fBordure);
	stJeu->stCurseur.ShapeCurseur.setFillColor(sf::Color::Transparent);

	stJeu->stCurseur.iCaseY = 7;
	stJeu->stCurseur.iCaseX = 7;

	stJeu->stCurseur.enMouvement = 0;
}



// renseignement de la taille de la molecule victoire du niveau
void Renseigner_Taille_Molecule(struct JEU* stJeu, FILE* pFluxNiveau)
{
	// balise
	while (fgetc(pFluxNiveau) != '*');

	fscanf(pFluxNiveau, "%d", &stJeu->stNiveauActuel.iTailleMolY);
	fscanf(pFluxNiveau, "%d", &stJeu->stNiveauActuel.iTailleMolX);

	// renseignement de la taille du tableau dynamique
	stJeu->stNiveauActuel.MoleculeVictoire = (struct ELEMENT*)
											calloc(stJeu->stNiveauActuel.iTailleMolY *
													stJeu->stNiveauActuel.iTailleMolX,
													sizeof(struct ELEMENT));
}



// lecture des données de la molécule victoire
void Lire_Molecule_Victoire(struct JEU* stJeu, FILE* pFluxNiveau)
{
	int y = 0, x = 0;
	int iValeurMap = 0;
	int iCaseActuelle = 0;
	const int iMolPosX = 50, iMolPosY = 400;

	// balise
	while (fgetc(pFluxNiveau) != '*');

	for (y = 0; y < stJeu->stNiveauActuel.iTailleMolY; ++y)
	{
		for (x = 0; x < stJeu->stNiveauActuel.iTailleMolX; ++x)
		{
			fscanf(pFluxNiveau, "%d", &iValeurMap);

			if ( iValeurMap != 88 )
			{
				iCaseActuelle =  (y*stJeu->stNiveauActuel.iTailleMolX) + x;

				stJeu->stNiveauActuel.MoleculeVictoire[iCaseActuelle] = stJeu->stTabElements[iValeurMap];
				stJeu->stNiveauActuel.MoleculeVictoire[iCaseActuelle].x = iMolPosX + x*TAILLE_SPRITE;
				stJeu->stNiveauActuel.MoleculeVictoire[iCaseActuelle].y = iMolPosY + y*TAILLE_SPRITE;
			}
		}
	}
}



// chargement des données d'un niveau en fonction des informations contenues dans
// un fichier map correspondant au niveau
void Charger_Donnees_Niveau(struct JEU* stJeu)
{
	FILE* pFluxNiveau = NULL;
	char szCheminNiveau[50] = "";
	
	sprintf(szCheminNiveau, "../Files/level_%d.txt", stJeu->stNiveauActuel.NumeroNiveau);
	pFluxNiveau = fopen(szCheminNiveau, "r");

	if(pFluxNiveau == NULL)
	{
		stJeu->stNiveauActuel.cJeuFini = 1;
	}
	else
	{
		Lire_Map(stJeu, pFluxNiveau);

		Placer_Curseur(stJeu);

		Renseigner_Taille_Molecule(stJeu, pFluxNiveau);

		Lire_Molecule_Victoire(stJeu, pFluxNiveau);

		stJeu->stNiveauActuel.cVictoire = 0;
		stJeu->stNiveauActuel.cDefaite = 0;
		stJeu->stNiveauActuel.HorlogeNiveau.restart();
		fclose(pFluxNiveau);
	}
}



// libération des données alouées dynamiquement
void Liberer_Donnees_Niveau(struct JEU* stJeu)
{
	int y = 0, x = 0;

	free(stJeu->stNiveauActuel.MoleculeVictoire);
	stJeu->stNiveauActuel.MoleculeVictoire = NULL;

	for (y = 0; y < 13; ++y)
	{
		for (x = 0; x < 14; ++x)
		{
			stJeu->stNiveauActuel.Map[y][x] = stJeu->stTabElements[Vide];
		}
	}
}