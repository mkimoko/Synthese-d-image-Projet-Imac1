#include "ball.h"



Ball initBall(Ball ball,Point2D position,Vector2D direction,float radius, float speed, GLuint texture){
	ball.position = position;
	ball.direction = direction;
	ball.raduis = raduis;
	ball.speed = speed;
	ball.texture = texture;
}

void draw_ball(){
	int i;
	glColor3ub(255, 255, 0);
	  
	    glBegin(GL_LINE_LOOP);
	      glVertex2f(0.5, 0.5);
	    for (i = 0; i <= SEGMENTS; i++)
	    {
	      glVertex2f(cos(0-i*(PI/(SEGMENTS/2))), sin(0+i*(PI/(SEGMENTS/2))));
	    }
  glEnd();
}



