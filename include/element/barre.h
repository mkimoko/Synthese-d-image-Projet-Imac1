#ifndef __BARRE__H
#define __BARRE__H


/** STRUCTURES **/

typedef struct Barre
{
	Point2D p1;
	Point2D p2;
	Point2D p3;
	Point2D p4;
	Vector2D direction;
	Color3f color;
} Barre;
typedef Barre* Barres;


/** FONCTIONS **/
Barres BarreFabrik(Point2D p1, Point2D p2, Point2D p3, Point2D p4, Vector2D direction, Color3f color);
void drawBarre(Barres barre);
void moveBarre(Barres barre, int boolean);
int limiteTerrain(Point2D p1,Point2D p2, float limit);


#endif