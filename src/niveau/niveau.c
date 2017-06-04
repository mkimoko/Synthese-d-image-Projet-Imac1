#include "../../include/niveau/niveau.h"



Brik brikFabrik(Point2D p1, Point2D p2, Point2D p3, Point2D p4, int propriete){

	Brik brik;

        brik.p1 = p1;
        brik.p2 = p2;
        brik.p3 = p3;
        brik.p4 = p4;
        brik.propriete = propriete;
        brik.touche = 0;
	
	return brik;

}


Wall chargeLvl(char *chemin, int limit, float ecart){

	char caractereActuel;
	FILE *fichier = malloc(sizeof(FILE));
	fichier = fopen(chemin,"r+");
	int i = 0, j = 0;
  Point2D p1, p2, p3, p4;
  Wall mur = malloc(sizeof(Mur));

	do{

        caractereActuel = fgetc(fichier); // On lit le caractère


        if (i == 0)
        {
        	mur->largeur = atoi(&caractereActuel);
        }

        if (i == 2)
        {
        	mur->hauteur = atoi(&caractereActuel);
        }

        i++;

    } while (i <= 4);

    int mult = -1, max = 0;

    if (mur->hauteur >= mur->largeur)
      max = mur->hauteur;
    else
      max = mur->largeur;


    for (i = 0; i <= max*max; i++)
    {
      for (j = 0; j <= mur->largeur * 2; j++)
      {
        if (i >= mur->hauteur/2)
          mult = 1;
        p1 = PointXY( 20*(limit-ecart + i*( limit/mur->largeur )), 20*( (limit/4) - i*(limit/mur->hauteur+ecart) - (limit/mur->hauteur+ecart) ) );
        p2 = PointXY( 20*(-limit+ecart + i*limit/mur->largeur), 20*( (limit/4) - i*(limit/mur->hauteur+ecart) - (limit/mur->hauteur+ecart) ) );
        p3 = PointXY( p2.x, 20*( (limit/4) - i*(limit/mur->hauteur+ecart) ) );
        p4 = PointXY( (p1.x), 20*( (limit/4) - i*(limit/mur->hauteur+ecart) ) );

        
      }
      caractereActuel = fgetc(fichier); // On lit le caractère

      if ( caractereActuel !=  ' '  && caractereActuel !=  EOF)
       {
           mur->niveau[i] = brikFabrik(p1, p2, p3, p4, atoi(&caractereActuel) );
           printf("\nmur->p1.x = %f,mur->p1.y = %f, \nmur->p2.x = %f, mur->p2.y = %f, \nmur->p3.x = %f,mur->p3.y = %f, \nmur->p4.x = %f mur->p4.y = %f,\n", mur->niveau[i].p1.x,mur->niveau[i].p1.y, mur->niveau[i].p2.x,mur->niveau[i].p2.y, mur->niveau[i].p3.x,mur->niveau[i].p3.y, mur->niveau[i].p4.x,mur->niveau[i].p4.y);        }
    }
    return mur;
}

void drawMur(Wall mur){
    
    for (int i = 0; i < mur->hauteur * mur->hauteur; i++)
    {
      if (mur->niveau[i].touche == 0)
      {
        glBegin(GL_QUADS);
          glColor3d( 240, 195, 0 );
          glVertex2f(mur->niveau[i].p1.x, mur->niveau[i].p1.y);
          glVertex2f(mur->niveau[i].p2.x, mur->niveau[i].p2.y);
          glVertex2f(mur->niveau[i].p3.x, mur->niveau[i].p3.y);
          glVertex2f(mur->niveau[i].p4.x, mur->niveau[i].p4.y);
        glEnd();
      }
    }     
}

void collision(Wall wall, Player j, Player adv){
  for (int i = 0; i < wall->hauteur * wall->largeur; i++)
  {
    if ( j->balles->position.x <= wall->niveau[i].p1.x-4  && j->balles->position.x >= wall->niveau[i].p2.x-4 && ( j->balles->position.y == wall->niveau[i].p1.y+4 || j->balles->position.y == wall->niveau[i].p3.y-4 ) )
    {
      wall->niveau[i].touche == 1;
      if (wall->niveau[i].propriete == 1)
      {
        adv->nbBalles--;
      }

      if (wall->niveau[i].propriete == 2)
      {
        j->nbBalles++;
      }

      if (wall->niveau[i].propriete == 3)
      {
        if ( (j->balles->direction.y > 0 && j->barre->p1.y > 0) || (j->balles->direction.y < 0 && j->barre->p1.y < 0) || (adv->balles->direction.y > 0 && adv->barre->p1.y < 0) || (adv->balles->direction.y < 0 && adv->barre->p1.y > 0))
        {
          j->balles->direction = MultVector(j->balles->direction, 0.5);
        }
      }

      if (wall->niveau[i].propriete == 3)
      {
        if ( (j->balles->direction.y > 0 && j->barre->p1.y < 0) || (j->balles->direction.y < 0 && j->barre->p1.y > 0) || (adv->balles->direction.y > 0 && j->barre->p1.y > 0) || (j->balles->direction.y < 0 && j->barre->p1.y < 0))
        {
          j->balles->direction = MultVector(j->balles->direction, 2);
        }
      }

      shoot(j->balles);
    }
  }

}


