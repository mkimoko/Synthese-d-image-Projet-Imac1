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

/*Probleme au niveau de l'attribution des points des briques => problème affichage*/
Wall chargeLvl(char *chemin, float limit, float ecart){

	char caractereActuel;
	FILE *fichier = malloc(sizeof(FILE));
	fichier = fopen(chemin,"r+");
	int i = 0;
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

    int espace = 0;


    for (i = 0; i <= mur->hauteur * mur->largeur * 2; i++)
    {
      caractereActuel = fgetc(fichier); // On lit le caractère
      if ( caractereActuel !=  ' ' ){
        if (caractereActuel ==  EOF)
        {
          return mur;
        }

        p1 = PointXY( -20*(limit - i*( limit/mur->largeur )+espace) , 20*( (limit/4) - (limit/mur->hauteur+ecart) ) );
        

        p2 = PointXY( -20*(limit - (i+1)*( limit/mur->largeur )+espace), 20*( (limit/4) - (limit/mur->hauteur+ecart) ) );
        
        p3 = PointXY( p2.x, 20*( (limit/mur->hauteur/mur->hauteur) ) );
        
        p4 = PointXY( (p1.x), 20*( (limit/mur->hauteur/mur->hauteur) ) );

        mur->niveau[i] = brikFabrik(p1, p2, p3, p4, caractereActuel);
      }
        
  }
      return mur;
  }

void drawMur(Wall mur){
    
    for (int i = 0; i < mur->hauteur * mur->hauteur; i++)
    {
      if (mur->niveau[i].touche == 0)
      {
        glBegin(GL_QUADS);
          glColor3d( 255, 255, 0 );
          glVertex2f(mur->niveau[i].p1.x, mur->niveau[i].p1.y);
          glVertex2f(mur->niveau[i].p2.x, mur->niveau[i].p2.y);
          glVertex2f(mur->niveau[i].p3.x, mur->niveau[i].p3.y);
          glVertex2f(mur->niveau[i].p4.x, mur->niveau[i].p4.y);
        glEnd();
      }
    }     
}

/*Fonction collision ne marche pas correctement pour le bon déroulement de la partie nous avons décider de le laisser en commentaire
  Vous pouvez néamoins les enlevés pour voir ce que fait la fonction*/

int collision(Wall wall, Player j, Player adv){

  /*Vector2D normal = Normalize(j->balles-> direction);
  for (int i = 0; i < wall->hauteur * wall->largeur; i++)
  {

    if (wall->niveau[i].touche == 0)
    {
      if ( ( (j->balles->position.y <= wall->niveau[i].p1.y+2  && j->balles->position.y >= wall->niveau[i].p2.y+2) && ( j->balles->position.x <= wall->niveau[i].p1.x-2 || j->balles->position.x >= wall->niveau[i].p3.x+2) )   ||     ( (j->balles->position.x >= wall->niveau[i].p1.x+2  && j->balles->position.x <= wall->niveau[i].p2.x+2) && ( j->balles->position.y >= wall->niveau[i].p1.y+2 || j->balles->position.y >= wall->niveau[i].p4.y+2) ) )
      {

        j->balles->direction.x = j->balles->direction.x * (-1);


        if (j->balles->position.y <= normal.y)
          {
            j->balles->direction.y = normal.y + fabs( normal.y - j->balles->direction.y); 
          }

        if (j->balles->position.y >= normal.y)
          {
            j->balles->direction.y = normal.y - fabs( normal.y - j->balles->direction.y); 
          }

        wall->niveau[i].touche = 1;
        if (wall->niveau[i].propriete == 1)
        {
          adv->vie--;
        }

        if (wall->niveau[i].propriete == 2)
        {
          j->vie++;
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
        return 1 ;
      }
    }
    
  }
  return 0;*/

}


