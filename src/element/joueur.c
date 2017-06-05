#include "balle.c"
#include "barre.c"
#include "../../include/element/joueur.h"


Player joueurFabrik(Barres barre, Balles balles){

	Player j = malloc(sizeof(Joueur));

	if (j != NULL)
	{
		j->barre = barre;
		j->balles = balles;
		j->vie = 3;
		newBall(j, j->balles->position, j->balles->direction);
		return j; 
	}

	printf("Joueur non créer\n");
	return NULL;
}


int contactInf(Barres barre, Balles balles){
	/*Contact avec la barre du bas*/

	if (balles->position.y <= barre->p1.y + 2  && balles->position.x + 2 <= barre->p1.x + 2  &&  balles->position.x >= barre->p2.x - 2)
	{
		return 1;
	}
	return 0;
}

int contactSup(Barres barre, Balles balles){
	/*Contact avec la barre du haut*/

	if (balles->position.y >= barre->p1.y - 2  && balles->position.x + 2 <= barre->p1.x + 2  &&  balles->position.x >= barre->p2.x - 2)
	{
		return 1;
	}
	return 0;
}


void shoot(Balles balles){
	Vector2D normal = Normalize(balles-> direction);

	balles->direction.y = balles->direction.y * -1;
	
	if (balles->position.x <= normal.x)
	{
		balles->direction.x = normal.x + fabs( normal.x - balles->direction.x);	
	}

	if (balles->position.x >= normal.x)
	{
		balles->direction.x = normal.x - fabs( normal.x - balles->direction.x);	
	}
}



int score(Player top, Player down, float limit){

	/*Si joueur du bas marque un point */
	if ( horsLimite(top->balles, limit) == 1 || horsLimite(down->balles, limit) == 1 )
	{
		top->vie = top->vie-1;
		return 1; 
	}


	/*Si joueur du haut marque un point */
	if ( horsLimite(top->balles, limit) == -1 || horsLimite(down->balles, limit) == -1 )
	{
		down->vie--; 
		return -1;
	}

	return 0;
	
}

void newBall(Player j, Point2D position, Vector2D direction){

		j->balles->next = BallFabrik(position, direction, j->balles->color);
		j->balles = j->balles->next;
		j->balles->next = NULL;
		return;	
}