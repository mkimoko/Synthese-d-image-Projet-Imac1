#include "../../include/element/barre.h"

Barres BarreFabrik(Point2D p1, Point2D p2, Point2D p3, Point2D p4, Vector2D direction, Color3f color){

	Barres barre = malloc(sizeof(Barre));

	if (barre != NULL)
	{
		barre->p1 = p1;
		barre->p2 = p2;
		barre->p3 = p3;
		barre->p4 = p4;

		barre->direction = direction;
		barre->color = color;

		return barre;
	}

	return NULL;
}


void drawBarre(Barres barre){
	glBegin(GL_QUADS);
		glColor3d(barre->color.r, barre->color.g, barre->color.b);
		glVertex2f(barre->p1.x, barre->p1.y);
		glVertex2f(barre->p2.x, barre->p2.y);
		glVertex2f(barre->p4.x, barre->p4.y);
		glVertex2f(barre->p3.x, barre->p3.y);
	glEnd();
}

void moveBarre(Barres barre, int boolean){
	if (boolean == 1)
	{
		glTranslatef(barre->p1.x + barre->direction.x, barre->direction.y, 0);
		glTranslatef(barre->p2.x + barre->direction.x, barre->direction.y, 0);
		glTranslatef(barre->p3.x + barre->direction.x, barre->direction.y, 0);
		glTranslatef(barre->p4.x + barre->direction.x, barre->direction.y, 0);
	}
	
}

int limiteTerrain(Point2D p1,Point2D p2, float limit){
	if (p1.x >= limit)
	{
		return 1;
	}

	 if (p2.x <= limit*-1){

	 	return 2;
	 } 
	return 0;
}









