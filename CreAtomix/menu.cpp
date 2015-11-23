
// Auteur : Alfiguigui Mehdi
// Date : 27/11/2012
// Nom du fichier : menu.cpp
// Description : c'est le menu principal du jeu

#include "includes.h"



// cette fonction affiche les éléments du menu
void Afficher_Menu(struct JEU* stJeu, sf::RectangleShape* CurseurMenu)
{
	stJeu->stData_SFML.Fenetre.draw(stJeu->stGraph.Sprites[Fond_ecran_1]);
	stJeu->stData_SFML.Fenetre.draw(*CurseurMenu);
}



// cette fonction affiche les high-scores
void Afficher_High_Scores(struct JEU* stJeu, int* iGameState)
{
	FILE* pFlux = NULL;
	int iContinuer = 1;
	int i = 0;

	pFlux = fopen("../Files/high_scores.bin", "rb");

	while ( iContinuer == 1 )
	{
		while ( stJeu->stData_SFML.Fenetre.pollEvent(stJeu->stData_SFML.Evenements) )
		{
			// on regarde le type de l'évènement...
			switch (stJeu->stData_SFML.Evenements.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				stJeu->stData_SFML.Fenetre.close();
				iContinuer = 0;
				*iGameState = 3;
				break;

				// touche pressée
			case sf::Event::KeyPressed:
				if ( (stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Return) ||
					(stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Escape))
				{
					iContinuer = 0;
					*iGameState = 1;
				}
				break;
			}
		}
		
		stJeu->stData_SFML.Fenetre.clear();
		stJeu->stData_SFML.Fenetre.draw(stJeu->stGraph.Sprites[Fond_ecran_4]);

		for (i = 0; i < 10; ++i)
		{
			struct JOUEUR stJoueur;
			char szChaine[50] = "";

			fread(&stJoueur, 1, sizeof(struct JOUEUR), pFlux);
			sprintf(szChaine, "%s", stJoueur.Nom);
			sprintf(stJoueur.Nom, "%-s", szChaine);

			stJeu->stData_SFML.Texte[4].setString(stJoueur.Nom);
			stJeu->stData_SFML.Fenetre.draw(stJeu->stData_SFML.Texte[4]);

			sprintf(stJoueur.Nom, "%10d", stJoueur.Score);

			stJeu->stData_SFML.Texte[4].setPosition(500, stJeu->stData_SFML.Texte[4].getPosition().y);
			stJeu->stData_SFML.Texte[4].setString(stJoueur.Nom);
			stJeu->stData_SFML.Fenetre.draw(stJeu->stData_SFML.Texte[4]);

			stJeu->stData_SFML.Texte[4].setPosition(200, stJeu->stData_SFML.Texte[4].getPosition().y + 40);
		}

		rewind(pFlux);
		stJeu->stData_SFML.Texte[4].setPosition(200, 100);

		stJeu->stData_SFML.Fenetre.display();
	}

	fclose(pFlux);
}




// boucle du menu
void Traiter_Menu(struct JEU* stJeu)
{
	sf::RectangleShape CurseurMenu;
	int iGameState = 1;
	int iEtatMenu = 0;

	CurseurMenu.setSize(sf::Vector2f(300, 50));
	CurseurMenu.setFillColor(sf::Color::Transparent);
	CurseurMenu.setOutlineColor(sf::Color::Blue);
	CurseurMenu.setOutlineThickness(2);
	CurseurMenu.setPosition(250, 325);

	while ( stJeu->stData_SFML.Fenetre.isOpen() && (iGameState > 0) && (stJeu->stNiveauActuel.cJeuFini == 0) )
	{
		while ( stJeu->stData_SFML.Fenetre.pollEvent(stJeu->stData_SFML.Evenements) )
		{
			// on regarde le type de l'évènement...
			switch (stJeu->stData_SFML.Evenements.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				stJeu->stData_SFML.Fenetre.close();
				iGameState = 3;
				break;

				// touche pressée
			case sf::Event::KeyPressed:
				{
					if (stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Return)
					{
						switch(iEtatMenu)
						{
							case 0:
								iGameState = 0;
								break;

							case 1:
								iGameState = 2; 
								break;

							case 2:
								iGameState = 3;
								break;

							default:
								break;
						}
					}

					if (stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Up)
					{
						if (iEtatMenu == 0)
						{
							CurseurMenu.setPosition(250, 465);
							iEtatMenu = 2;
						}
						else
						{
							CurseurMenu.setPosition(250, CurseurMenu.getPosition().y - 70);
							--iEtatMenu;
						}
					}

					if (stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Down)
					{
						if (iEtatMenu == 2)
						{
							CurseurMenu.setPosition(250, 325);
							iEtatMenu = 0;

						}
						else
						{
							CurseurMenu.setPosition(250, CurseurMenu.getPosition().y + 70);
							++iEtatMenu;
						}
					}
				}
				break;

				// on ne traite pas les autres types d'évènements
			default:
				break;
			}
		}

		// appels des différentes fonctions :

		stJeu->stData_SFML.Fenetre.clear();

		switch (iGameState)
		{
		case 0:
			stJeu->stNiveauActuel.cJeuFini = 0;
			break;
		case 1:
			Afficher_Menu(stJeu, &CurseurMenu);
			break;
		case 2 :
			Afficher_High_Scores(stJeu, &iGameState);
			break;
		case 3 :
			stJeu->stNiveauActuel.cJeuFini = 1;
			break;
		}

		// c'est tres sale oui, mais ca me permet d'eviter un bug
		// sans ca, quand on ferme le programme en cliquand sur la croix dans les high scores
		// le processus ne se détruit pas completement, ce qui empeche de relancer le jeu
		if (iGameState == 3)
			stJeu->stNiveauActuel.cJeuFini = 1;


		stJeu->stData_SFML.Fenetre.display();
	}
}