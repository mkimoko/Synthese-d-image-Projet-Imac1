#ifndef __NIVEAU__H
#define __NIVEAU__H

#define MAX 50

/** STRUCTURES **/

typedef struct Brik
{
	Point2D p1;
	Point2D p2;
	Point2D p3;
	Point2D p4;
	int propriete;
	int touche;
}Brik;

typedef struct Mur
{
	int hauteur;
	int largeur; 
	struct Brik niveau[MAX];
}Mur;
typedef Mur* Wall;



/** FONCTIONS **/
Brik brikFabrik(Point2D p1, Point2D p2, Point2D p3, Point2D p4, int propriete);
Wall chargeLvl(char *chemin, float limit, float ecart);
int collision(Wall wall, Player j, Player adv);
void Placement(Wall mur, int limit);
void contactBrik (Brik brik, Player j);

#endif