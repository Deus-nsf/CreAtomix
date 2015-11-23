
// Auteur : Alfiguigui Mehdi
// Date : 24/11/2012
// Nom du fichier : main.cpp
// Description : c'est le point de départ du programme.

#include "includes.h"



// permet de reset le tableau des high scores avec des faux scores
void Faux_Scores()
{
	int i = 0;

	FILE* pFlux = fopen("../Files/high_scores.bin", "wb");

	for (i = 0; i < 10; ++i)
	{
		struct JOUEUR stJoueur;
		sprintf(stJoueur.Nom, "Monsieur_%d", i);
		stJoueur.Score = 100000 - i*10000;

		fwrite(&stJoueur, 1, sizeof(struct JOUEUR), pFlux);
	}

	fclose(pFlux);
}



// permet de saisir son nom au lancement d'une partie
void Saisir_Nom(struct JEU* stJeu, sf::Font* Police)
{
	int iContinuer = 1;
	int i = 0;
	sf::Text Blabla_Nom_Joueur;
	char szChaine[200] = "";

	stJeu->stData_SFML.Fenetre.setKeyRepeatEnabled(true);
	sprintf(stJeu->stJoueur.Nom, "\0");

	Blabla_Nom_Joueur.setFont(*Police);
	Blabla_Nom_Joueur.setPosition( 150.0f, 200.0f );

	while(iContinuer == 1)
	{
		while ( stJeu->stData_SFML.Fenetre.pollEvent(stJeu->stData_SFML.Evenements) )
		{
			switch (stJeu->stData_SFML.Evenements.type)
			{
				// fenêtre fermée
			case sf::Event::Closed:
				stJeu->stData_SFML.Fenetre.close();
				iContinuer = 0;
				break;

				// touche pressée
			case sf::Event::KeyPressed:
				if ( stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Return )
				{
					iContinuer = 0;
				}

				// saisie clavier simple (les 26 lettres classiques de l'alphabet)
				if ( (stJeu->stData_SFML.Evenements.key.code >= 0) && (stJeu->stData_SFML.Evenements.key.code <= 25) && (i < 40) )
				{
					stJeu->stJoueur.Nom[i] = stJeu->stData_SFML.Evenements.key.code + 'a';
					stJeu->stJoueur.Nom[i+1] = '\0';
					++i;
				}
				if ( (stJeu->stData_SFML.Evenements.key.code == sf::Keyboard::Back) && (i > 0) )
				{
					--i;
					stJeu->stJoueur.Nom[i] = '\0';
				}
				break;
			}
		}

		sprintf(szChaine, "Saisissez votre nom, entree pour valider : \n\n%s", stJeu->stJoueur.Nom);

		Blabla_Nom_Joueur.setString(szChaine);

		stJeu->stData_SFML.Fenetre.clear(sf::Color::Black);
		stJeu->stData_SFML.Fenetre.draw(Blabla_Nom_Joueur);
		stJeu->stData_SFML.Fenetre.display();
	}

	stJeu->stData_SFML.Fenetre.setKeyRepeatEnabled(false);
}



// permet d'enregistrer le joueur a la fin de sa partie
// si il a eu un assez bon score par rapport aux 10 autres
void Enregistrer_Joueur(struct JEU* stJeu)
{
	FILE* pFlux = NULL;
	struct JOUEUR stTabJoueurs[11];
	struct JOUEUR stJTemp;
	int j = 0, i = 0;

	pFlux = fopen("../Files/high_scores.bin", "rb");

	// on recupère les 10 joueurs du tableau des high scores
	fread(&stTabJoueurs, 10, sizeof(struct JOUEUR), pFlux);

	// on rajoute un 11 eme : soi-même
	stTabJoueurs[10] = stJeu->stJoueur;

	// on trie le tout
	for (j = 0; j < 10; ++j)
	{
		for (i = 0; i < 10; ++i)
		{
			if (stTabJoueurs[i + 1].Score > stTabJoueurs[i].Score)
			{
				stJTemp = stTabJoueurs[i + 1];
				stTabJoueurs[i + 1] = stTabJoueurs[i];
				stTabJoueurs[i] = stJTemp;
			}
		}
	}

	// on réouvre le fichier en ecriture seule
	freopen("../Files/high_scores.bin", "wb", pFlux);

	// on écrase son ancien contenu avec seulement les 10 premiers sur 11 !
	fwrite(&stTabJoueurs, 10, sizeof(struct JOUEUR), pFlux);

	fclose(pFlux);
}




// point d'entrée du programme
int main()
{
	sf::Font Police;	// la police doit toujours exister durant l'execution du programme
	struct JEU stJeu;

	Police.loadFromFile("../Fonts/arial.ttf");

	Charger_Donnees_SFML( &stJeu.stData_SFML );
	Charger_Ressources_Graphiques( &stJeu.stGraph );
	Charger_Textes( &stJeu.stData_SFML, &Police );
	Charger_Donnees_Jeu( &stJeu );

	Traiter_Menu(&stJeu);

	//Faux_Scores();

	if ( stJeu.stNiveauActuel.cJeuFini == 0 )
	{
		Charger_Donnees_Niveau( &stJeu );
		Saisir_Nom( &stJeu, &Police );
		stJeu.stNiveauActuel.HorlogeNiveau.restart();
	}

	while ( stJeu.stData_SFML.Fenetre.isOpen() && (stJeu.stNiveauActuel.cJeuFini == 0) &&
		(stJeu.stNiveauActuel.cDefaite == 0) )
	{
		Traiter_Niveau_En_Cours( &stJeu );
	}

	if (stJeu.stNiveauActuel.cJeuFini == 0)
	{
		// enregistrer high scores
		Enregistrer_Joueur(&stJeu);
	}

	stJeu.stData_SFML.Fenetre.close();

	return EXIT_SUCCESS;
}