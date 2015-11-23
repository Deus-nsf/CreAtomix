
// Auteur : Alfiguigui Mehdi
// Date : 25/11/2012
// Nom du fichier : boucle_niveau.cpp
// Description : la boucle d'un niveau en cours

#include "includes.h"

void Traiter_Niveau_En_Cours(struct JEU* stJeu)
{
	if(stJeu->stNiveauActuel.cVictoire == 1)
	{
		Calculer_Score( stJeu );
		stJeu->stNiveauActuel.cVictoire = 0;
		Liberer_Donnees_Niveau( stJeu );
		++stJeu->stNiveauActuel.NumeroNiveau;
		Charger_Donnees_Niveau( stJeu );
	}

	if ( (stJeu->stNiveauActuel.cJeuFini == 0) && (stJeu->stNiveauActuel.cDefaite == 0) )
	{
		// gestion evenements
		while (stJeu->stData_SFML.Fenetre.pollEvent(stJeu->stData_SFML.Evenements))
		{
			// on regarde le type de l'évènement...
			switch (stJeu->stData_SFML.Evenements.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				stJeu->stData_SFML.Fenetre.close();
				break;

				// touche pressée
			case sf::Event::KeyPressed:
				{
					// permet de savoir qu'elle direction va prendre le curseur
					if ( ((stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Left) ||
						(stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Up) ||
						(stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Right) ||
						(stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Down)) && (stJeu->stCurseur.enMouvement == 0))
					{
						stJeu->stCurseur.enMouvement = 1;

						// on definit la distance max que peut parcourir le curseur
						if ( stJeu->stCurseur.ElementSaisi == 0)
							stJeu->stCurseur.iMaxDist = TAILLE_SPRITE;
						else
							stJeu->stCurseur.iMaxDist = 800;


						if ( stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Left )
							stJeu->stCurseur.gauche = 1;
						else if ( stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Up )
							stJeu->stCurseur.haut = 1;
						else if ( stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Right )
							stJeu->stCurseur.droite = 1;
						else
							stJeu->stCurseur.bas = 1;
					}

					if( stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Return )
					{
						if (stJeu->stCurseur.ElementSaisi == 0)
							Saisir_Atome(stJeu);
						else
							Poser_Atome(stJeu);
					}
				}
				break;

				// on ne traite pas les autres types d'évènements
			default:
				break;
			}
		}

		Deplacer_Curseur(stJeu);

		if(stJeu->stNiveauActuel.HorlogeNiveau.getElapsedTime().asSeconds() > stJeu->stNiveauActuel.iTempsMax)
		{
			stJeu->stNiveauActuel.cDefaite = 1;
		}

		// affichage
		stJeu->stData_SFML.Fenetre.clear();

		Afficher_Niveau_En_Cours( stJeu );

		stJeu->stData_SFML.Fenetre.display();
		// fin
	}
}