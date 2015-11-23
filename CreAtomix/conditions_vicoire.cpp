
// Auteur : Alfiguigui Mehdi
// Date : 26/11/2012
// Nom du fichier : conditions_victoire.cpp
// Description : regroupe tout ce qui est nécessaire pour detecter une victoire

#include "includes.h"


// vérification de la victoire
char Verifier_Victoire(struct JEU* stJeu)
{
	int iPremierAtomeX = 0;
	int y = 0, x = 0;
	int y2 = 0, x2 = 0;

	// calcule le décalage du premier atome de la molécule victoire
	while (stJeu->stNiveauActuel.MoleculeVictoire[iPremierAtomeX].estAtome != 1)
		++iPremierAtomeX;

	// on parcours la map jusqu'a trouver un atome décale du même décalage que la molécule victoire
	for (y = 0; y < (13 - stJeu->stNiveauActuel.iTailleMolY); ++y)
	{
		for (x = 0; x < (14 - stJeu->stNiveauActuel.iTailleMolX); ++x)
		{
			if (stJeu->stNiveauActuel.Map[y][x + iPremierAtomeX].estAtome == 1)
			{
				// on récupère les coordonées du début de la portion de la map à comparer avec la molécule victoire
				y2 = y;
				x2 = x;

				// on sors de la double boucle for pour économiser du temps de calcul
				y = 13;
				x = 14;
			}
		}
	}

	// on parcours la molecule victoire avec la portion de la map
	for (y = 0; y < stJeu->stNiveauActuel.iTailleMolY; ++y)
	{
		for (x = 0; x < stJeu->stNiveauActuel.iTailleMolX; ++x)
		{
			// si la case de la molécule vicoitre est un atome
			if(stJeu->stNiveauActuel.MoleculeVictoire[ y*stJeu->stNiveauActuel.iTailleMolX + x].estAtome == 1)
			{
				// alors on compare les atomes, si il y a une seule différence, alors il n'y a pas victoire
				if(stJeu->stNiveauActuel.MoleculeVictoire[ y*stJeu->stNiveauActuel.iTailleMolX + x].eSignature
					!= stJeu->stNiveauActuel.Map[y2 + y][x2 + x].eSignature)
				{
					return 0;
				}
			}
		}
	}

	return 1;
}



// calcule les points disponibles en fonction du temps restant,
// du niveau, et du nombre d'atomes présents dans la molécule victoire
void Calculer_Score(struct JEU* stJeu)
{
	int y = 0, x = 0;

	for (y = 0; y < stJeu->stNiveauActuel.iTailleMolY; ++y)
	{
		for (x = 0; x < stJeu->stNiveauActuel.iTailleMolX; ++x)
		{
			// si la case de la molécule vicoitre est un atome
			if(stJeu->stNiveauActuel.MoleculeVictoire[ y*stJeu->stNiveauActuel.iTailleMolX + x].estAtome == 1)
			{
				stJeu->stJoueur.Score += stJeu->stNiveauActuel.NumeroNiveau*200;
			}
		}
	}

	// 5000 points + le temps restant en secondes x 10 offert a chaque niveau !
	stJeu->stJoueur.Score +=
		(( stJeu->stNiveauActuel.iTempsMax  
		- (int)stJeu->stNiveauActuel.HorlogeNiveau.getElapsedTime().asSeconds() )
		* 10)
		+ 5000;

	// jackpot !!!!
	if (stJeu->stNiveauActuel.NumeroNiveau == 11)
	{
		stJeu->stJoueur.Score += 100000;
		stJeu->stNiveauActuel.cJeuFini = 1;
	}
}