#ifndef __JOUEUR__H
#define __JOUEUR__H


/** STRUCTURES **/

typedef struct Joueur
{
	Barres barre;
	Balles balles;
	Color3f color;
} Joueur;
typedef Joueur* Player;


/** FONCTIONS **/
Barres joueurFabrik(Barres barre, Balles balles, Color3f color);

int contactInf(Barres barre, Balles balles);
int contactSup(Barres barre, Balles balles);
void shoot(Balles balles);

#endif