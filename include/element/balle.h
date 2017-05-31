#ifndef __BALLE__H
#define __BALLE__H

#define SEGMENTS 128


/** STRUCTURES **/

typedef struct Ball
{
	Point2D position;
	Vector2D direction;
	Color3f color;
	struct Ball *next;
} Ball;
typedef Ball* Balles;


/** FONCTIONS **/
Balles BallFabrik(Point2D position, Vector2D direction, Color3f color);
void drawBall(Balles ball);
void moveBall(Balles ball);
void limiteRepere(Balles balles, float limit);
int horsLimite(Balles balles, float limit);


#endif