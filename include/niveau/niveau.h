#ifndef __NIVEAU__H
#define __NIVEAU__H

/** STRUCTURES **/

typedef struct Brik
{
	Point2D p1;
	Point2D p2;
	Point2D p3;
	Point2D p4;
	int propriete;
	struct Brik *next;
}Brik;
typedef Brik* Mur;



/** FONCTIONS **/

Mur murFabrik(Point2D p1, Point2D p2, Point2D p3, Point2D p4, int propriete);
void chargeLvl(char *chemin, Mur mur);


#endif