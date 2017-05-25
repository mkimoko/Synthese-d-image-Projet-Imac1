#include "../../include/element/balle.h"



Balles BallFabrik(Point2D position, Vector2D direction, Color3f color){

	Balles balles = malloc(sizeof(Ball));

	if(balles != NULL){
		balles->position = position;
		balles->direction = direction;
		balles->color = color;
		balles->next = NULL;
		return balles;
	} 

	printf("Erreur ! Création de la balle non réussie\n");
	return NULL;
}

void drawBall(Balles ball){
  int i;
 
  glBegin(GL_TRIANGLE_FAN);
  glColor3d(ball->color.r, ball->color.g, ball->color.b);
   
  for (i = 0; i <= SEGMENTS; i++)
      glVertex2f(cos(i*(M_PI/(SEGMENTS/2))), sin(i*(M_PI/(SEGMENTS/2))));
  glEnd();
}

void moveBall(Balles ball){
	glTranslatef(ball->position.x + ball->direction.x, ball->position.y + ball->direction.y, 0);
	drawBall(ball);
}

void limiteRepere(Balles balles, float limit){

	if ( ( balles->position.x <= -(limit-4)  && balles->position.y <= limit-4 && balles->position.y >= -(limit-4) )  ||  ( balles->position.x >= (limit-4)  && balles->position.y <= limit-4 && balles->position.y >= -(limit-4) ) )
	{
		balles->direction.x = balles->direction.x * (-1);
	}

}