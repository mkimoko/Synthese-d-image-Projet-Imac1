#ifndef __JOUEUR__H
#define __JOUEUR__H
#define BALLMAX 2


/** STRUCTURES **/

typedef struct Joueur
{
	Barres barre;
	Balles balles;
	int nbBalles;
	int score;
} Joueur;
typedef Joueur* Player;


/** FONCTIONS **/
Player joueurFabrik(Barres barre, Balles balles);

int contactInf(Barres barre, Balles balles);
int contactSup(Barres barre, Balles balles);
void shoot(Balles balles);
int score(Player top, Player down, float limit);
void newBall(Player j, Point2D position, Vector2D direction);

#endif