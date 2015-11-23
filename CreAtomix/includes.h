
// Auteur : Alfiguigui Mehdi
// Date : 24/11/2012
// Nom du fichier : includes.h
// Description : c'est le header general du programme,
// il va inclure toutes les données nécessaires pour que le programme fonctionne correctement,
// déclarer des defines, la liste des structs et enums, les prototypes des fonctions, etc...

#ifndef _INCLUDES
#define _INCLUDES

#define _CRT_SECURE_NO_WARNINGS

#define FRAMERATE 120
#define TAILLE_SPRITE 32
#define TEMPS_MAX 179 //179

#include <SFML/Graphics.hpp>


// précision, les différents atomes sont gérés selon la logique suivante :
// nom de l'atome, position des liens (0 : pas de liens, 1 : lien simple, 2 : double lien)
// répartis ainsi : gauche, gauche-haut, haut, haut-droite, droite, droite-bas, bas, bas-gauche
// par exemple, un atome d'hydrogène comme ceci -H= s'écrira :
// Hydro_10002000
enum NOM_ELEM
{
	Sol_1,
	Sol_2,
	Sol_3,

	Mur_1,
	Mur_2,

	Hydro_10000000,
	Hydro_01000000,
	Hydro_00100000,
	Hydro_00010000,
	Hydro_00001000,
	Hydro_00000100,
	Hydro_00000010,
	Hydro_00000001,

	Oxy_10001000,
	Oxy_00100010,
	Oxy_20000000,
	Oxy_00200000,
	Oxy_00002000,
	Oxy_00000020,

	Carb_10101010,
	Carb_20010100,
	Carb_01002001,
	Carb_10102000,
	Carb_10001020,
	Carb_10201000,
	Carb_01110010,
	Carb_10100010,
	Carb_00101010,
	Carb_20001010,
	Carb_10002010,

	Vide,

	Fond_ecran_1 = Vide,
	Fond_ecran_2,
	Fond_ecran_3,
	Fond_ecran_4,
};


// les données de la SFML
struct DATA_SFML
{
	sf::RenderWindow Fenetre;
	sf::Clock Horloge;
	sf::Event Evenements;
	sf::Text Texte[5];
};


// les données graphiques
struct GRAPH
{
	sf::Texture SpriteSheet[10];
	sf::Sprite Sprites[35];
};


// les données du joueur
struct JOUEUR
{
	char Nom[50];
	long int Score;
};


// les données d'un élément
struct ELEMENT
{
	sf::Sprite* pSprite;
	int x, y;
	enum NOM_ELEM eSignature;
	char estAtome;
	char estMur;
};


// les données concernant le niveau
struct NIVEAU
{
	int NumeroNiveau;
	char CheminNiveau;
	sf::Clock HorlogeNiveau;
	int iTempsMax;
	struct ELEMENT Map[13][14];
	struct ELEMENT* MoleculeVictoire;
	int iTailleMolY, iTailleMolX;
	char cVictoire;
	char cDefaite;
	char cJeuFini;
};


// les données concernant le curseur
struct CURSEUR
{
	char ElementSaisi;
	sf::RectangleShape ShapeCurseur;
	float x, y;
	int iCaseY, iCaseX;
	int iMaxDist;
	char enMouvement;
	char droite, gauche, haut, bas;
};


// la struct générale du programme
struct JEU
{
	struct DATA_SFML stData_SFML;
	struct GRAPH stGraph;
	struct JOUEUR stJoueur;
	struct ELEMENT stTabElements[31];
	struct NIVEAU stNiveauActuel;
	struct CURSEUR stCurseur;
};


//////// prototypes des fonctions ////////

void Charger_Donnees_SFML(struct DATA_SFML*);	// fini
void Charger_Ressources_Graphiques(struct GRAPH*);	// fini
void Charger_Textes(struct DATA_SFML*, sf::Font*);	// fini
void Charger_Donnees_Jeu(struct JEU*);	// fini

void Charger_Donnees_Niveau(struct JEU*);	// fini
void Liberer_Donnees_Niveau(struct JEU*);	// fini

void Deplacer_Curseur(struct JEU*);	// fini
void Saisir_Atome(struct JEU*);	// fini
void Poser_Atome(struct JEU*);	// fini
char Verifier_Victoire(struct JEU*);	// fini
void Calculer_Score(struct JEU*);	// fini
void Enregistrer_Joueur(struct JEU*);	// fini

void Traiter_Menu(struct JEU*);		// fini
void Afficher_Menu(struct JEU*);	// fini
void Afficher_High_Scores(struct JEU*, int*);	// fini
void Traiter_Niveau_En_Cours(struct JEU*);	// fini
void Afficher_Niveau_En_Cours(struct JEU*);	// fini

////////////////// fin ///////////////////


#endif // _INCLUDES