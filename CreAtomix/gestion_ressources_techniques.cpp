
// Auteur : Alfiguigui Mehdi
// Date : 25/11/2012
// Nom du fichier : gestion_ressources_techniques.cpp
// Description : ce sont les fonctions de gestion des ressources techniques
// du programme (SFML, graphismes, données de jeu...)

#include "includes.h"


// s'occupe de charger ce qu'il faut pour que la librairie SFML fonctionne bien
void Charger_Donnees_SFML(struct DATA_SFML* stData_SFML)
{
	stData_SFML->Fenetre.create(sf::VideoMode(800, 600, 32), "CreAtomix", sf::Style::Close);
	stData_SFML->Fenetre.setKeyRepeatEnabled(false);
	stData_SFML->Fenetre.setFramerateLimit(FRAMERATE);
	stData_SFML->Fenetre.setVerticalSyncEnabled(false);
	stData_SFML->Horloge.restart();
}


// charge les textes
void Charger_Textes(struct DATA_SFML* stData_SFML, sf::Font* Police)
{
	const char* szChaineInit = "";
	const char* szChaineMolecule = "Molécule à reproduire :";
	
	stData_SFML->Texte[0].setFont( *Police );
	stData_SFML->Texte[0].setColor(sf::Color::Yellow);
	stData_SFML->Texte[0].setPosition( 380, 10 );

	stData_SFML->Texte[1].setFont( *Police );
	stData_SFML->Texte[1].setColor(sf::Color::Yellow);
	stData_SFML->Texte[1].setPosition( 20, 100 );

	stData_SFML->Texte[2].setFont( *Police );
	stData_SFML->Texte[2].setColor(sf::Color::White);
	stData_SFML->Texte[2].setPosition( 20, 350 );
	stData_SFML->Texte[2].setString( szChaineMolecule );

	stData_SFML->Texte[3].setFont( *Police );
	stData_SFML->Texte[3].setColor(sf::Color::Yellow);
	stData_SFML->Texte[3].setPosition( 20, 200 );

	stData_SFML->Texte[4].setFont( *Police );
	stData_SFML->Texte[4].setColor(sf::Color::White);
	stData_SFML->Texte[4].setPosition( 200, 100 );
}



// s'occupe de charger les parties de la spritesheet et les images aux bons endroits
void Charger_Ressources_Graphiques(struct GRAPH* stGraph)
{
	int y = 0, x = 0;

	stGraph->SpriteSheet[0].loadFromFile("../Textures/sprite_sheet.png");

	// création des sprites en fonction de la spritesheet
	for (y = 0; y < 6; ++y)
	{
		for (x = 0; x < 5; ++x)
		{
			stGraph->Sprites[(y*5) + x].setTexture(stGraph->SpriteSheet[0]);
			stGraph->Sprites[(y*5) + x].setTextureRect(sf::IntRect((x*TAILLE_SPRITE) + x, (y*TAILLE_SPRITE) + y, TAILLE_SPRITE, TAILLE_SPRITE));
		}
	}

	stGraph->SpriteSheet[1].loadFromFile("../Textures/chimie_2.png");
	stGraph->Sprites[Fond_ecran_2].setTexture(stGraph->SpriteSheet[1]);

	stGraph->SpriteSheet[2].loadFromFile("../Textures/chimie_3.png");
	stGraph->Sprites[Fond_ecran_3].setTexture(stGraph->SpriteSheet[2]);

	stGraph->SpriteSheet[3].loadFromFile("../Textures/chimie_1.png");
	stGraph->Sprites[Fond_ecran_1].setTexture(stGraph->SpriteSheet[3]);

	stGraph->SpriteSheet[4].loadFromFile("../Textures/high_scores.png");
	stGraph->Sprites[Fond_ecran_4].setTexture(stGraph->SpriteSheet[4]);
}


// s'occupe de charger les données communes au jeu (elements, etc...)
void Charger_Donnees_Jeu(struct JEU* stJeu)
{
	int y = 0, x = 0;

	// chargement de toutes les caracteristiques des éléments
	// en fonction de ceux présents sur la spritesheet
	for (x = 0; x < 30; ++x)
	{
		stJeu->stTabElements[x].pSprite = &stJeu->stGraph.Sprites[x];
		stJeu->stTabElements[x].eSignature = (enum NOM_ELEM) x;

		if ( (x >=0) && (x <= 2) )
		{
			stJeu->stTabElements[x].estAtome = 0;
			stJeu->stTabElements[x].estMur = 0;
		}
		else if ( (x >=3) && (x <= 4) )
		{
			stJeu->stTabElements[x].estAtome = 0;
			stJeu->stTabElements[x].estMur = 1;
		}
		else
		{
			stJeu->stTabElements[x].estAtome = 1;
			stJeu->stTabElements[x].estMur = 0;
		}
	}
	
	// élément "vide"
	stJeu->stTabElements[Vide].pSprite = NULL;

	stJeu->stNiveauActuel.NumeroNiveau = 1;
	stJeu->stNiveauActuel.cJeuFini = 0;
	stJeu->stNiveauActuel.iTempsMax = TEMPS_MAX;

	stJeu->stJoueur.Score = 0;

	// netoyage de la map
	for (y = 0; y < 13; ++y)
	{
		for (x = 0; x < 14; ++x)
		{
			stJeu->stNiveauActuel.Map[y][x] = stJeu->stTabElements[30];
		}
	}
}