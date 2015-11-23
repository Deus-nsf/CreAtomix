
// Auteur : Alfiguigui Mehdi
// Date : 26/11/2012
// Nom du fichier : conditions_victoire.cpp
// Description : regroupe tout ce qui est n�cessaire pour detecter une victoire

#include "includes.h"


// v�rification de la victoire
char Verifier_Victoire(struct JEU* stJeu)
{
	int iPremierAtomeX = 0;
	int y = 0, x = 0;
	int y2 = 0, x2 = 0;

	// calcule le d�calage du premier atome de la mol�cule victoire
	while (stJeu->stNiveauActuel.MoleculeVictoire[iPremierAtomeX].estAtome != 1)
		++iPremierAtomeX;

	// on parcours la map jusqu'a trouver un atome d�cale du m�me d�calage que la mol�cule victoire
	for (y = 0; y < (13 - stJeu->stNiveauActuel.iTailleMolY); ++y)
	{
		for (x = 0; x < (14 - stJeu->stNiveauActuel.iTailleMolX); ++x)
		{
			if (stJeu->stNiveauActuel.Map[y][x + iPremierAtomeX].estAtome == 1)
			{
				// on r�cup�re les coordon�es du d�but de la portion de la map � comparer avec la mol�cule victoire
				y2 = y;
				x2 = x;

				// on sors de la double boucle for pour �conomiser du temps de calcul
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
			// si la case de la mol�cule vicoitre est un atome
			if(stJeu->stNiveauActuel.MoleculeVictoire[ y*stJeu->stNiveauActuel.iTailleMolX + x].estAtome == 1)
			{
				// alors on compare les atomes, si il y a une seule diff�rence, alors il n'y a pas victoire
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
// du niveau, et du nombre d'atomes pr�sents dans la mol�cule victoire
void Calculer_Score(struct JEU* stJeu)
{
	int y = 0, x = 0;

	for (y = 0; y < stJeu->stNiveauActuel.iTailleMolY; ++y)
	{
		for (x = 0; x < stJeu->stNiveauActuel.iTailleMolX; ++x)
		{
			// si la case de la mol�cule vicoitre est un atome
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