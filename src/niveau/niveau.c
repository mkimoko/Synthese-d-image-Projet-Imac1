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
	int i = 0, cpt = 0;
  Wall mur = malloc(sizeof(Mur));

	do{

        caractereActuel = fgetc(fichier); // On lit le caractère
        if (caractereActuel !=  ' ' && caractereActuel !=  EOF)
        {
            if (i == 0)
            {
              mur->largeur = atoi(&caractereActuel);
              printf("La largeure du mur est de %d\n", mur->largeur);
            }

            if (i == 2)
            {
              mur->hauteur = atoi(&caractereActuel);
              printf("La longueur du mur est de %d\n", mur->hauteur);
            }
          }
          i++;

    } while (i < 4); 

    for (i = 0; i <= mur->hauteur * mur->largeur * 2; i++)
    {
      caractereActuel = fgetc(fichier); // On lit le caractère
      if ( caractereActuel !=  ' ' ){
        if (caractereActuel ==  EOF)
          return mur;

        mur->niveau[cpt].propriete = atoi(&caractereActuel);
        printf("La propriete du %de bric est %d\n",cpt+1, mur->niveau[cpt].propriete );
        cpt++;
      }
        
    }
    return mur;
  }


void Placement(Wall mur, int limit){
  float i = 0, j = 0;
  int cpt = 0;

  float x1 = 0, y1 = 0, x2 = 0, y2 = 0 , x3 = 0, y3 = 0, x4 = 0, y4 = 0;

  for (cpt = 0; cpt < mur->hauteur * mur->largeur ; cpt++)
  {
    if (x1 >= limit-2)
    {
      i = 0;
      j++;
    }
    /*P1*/
      x1 = (-limit + i*(limit/mur->largeur));
      y1 = (limit/2 - limit/(mur->hauteur) - j*(limit/mur->hauteur)) ;
      mur->niveau[cpt].p1 = PointXY( x1,y1 );

    /*P2*/
      x2 = (-limit + (i+1)*(limit/mur->largeur));
      y2 = (limit/2 - limit/(mur->hauteur) - j*(limit/mur->hauteur));
      mur->niveau[cpt].p2 = PointXY( x2,y2 );

    /*P3*/
      x3 = (-limit + (i+1)*(limit/mur->largeur));
      y3 = (limit/2 - limit/(mur->hauteur) - (j+1)*(limit/mur->hauteur));
      mur->niveau[cpt].p3 = PointXY( x3,y3 );

    /*P4*/
      x4 = (-limit + i*(limit/mur->largeur));
      y4 = (limit/2 - limit/(mur->hauteur) - (j+1)*(limit/mur->hauteur));
      mur->niveau[cpt].p4 = PointXY( x4,y4 );


      i++;

      printf("\n");
      printf("%d - Les coordonnées de p1: x= %f  y= %f \n",cpt, mur->niveau[cpt].p1.x, mur->niveau[cpt].p1.y );
      printf("%d - Les coordonnées de p2: x= %f  y= %f \n",cpt, mur->niveau[cpt].p2.x, mur->niveau[cpt].p2.y );
      printf("%d - Les coordonnées de p3: x= %f  y= %f \n",cpt, mur->niveau[cpt].p3.x, mur->niveau[cpt].p3.y );
      printf("%d - Les coordonnées de p4: x= %f  y= %f \n",cpt, mur->niveau[cpt].p4.x, mur->niveau[cpt].p4.y );
  }

    

    /*printf("\n");
      printf(" limit/largeur = %f\n",limit/mur->largeur);*/

    /*Placement des points p1 et p4*/
      /*mur->niveau[cpt].p1 = PointXY( (2-limit + i*(limit/mur->largeur)), (limit/2 + limit/(2*mur->hauteur) - j*(limit/mur->hauteur)) );
      mur->niveau[cpt].p4 = PointXY( (2-limit + i*(limit/mur->largeur)), (limit/2 + limit/(2*mur->hauteur) - (j+1)*(limit/mur->hauteur)) ); */
  
     /*Placement des points p2 et p3*/
      /*mur->niveau[cpt].p2 = PointXY( (2-limit + (i+1)*(limit/mur->largeur)), (limit/2 + limit/(2*mur->hauteur) - j*(limit/mur->hauteur)) );
      mur->niveau[cpt].p3 = PointXY( (2-limit + (i+1)*(limit/mur->largeur)), (limit/2 + limit/(2*mur->hauteur) - (j+1)*(limit/mur->hauteur)) );*/

      
      
  
}


void drawMur(Wall mur){
    
    for (int i = 0; i < mur->hauteur * mur->largeur; i++)
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
/*
  Vector2D normal = Normalize(j->balles-> direction);
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
  return 0;
*/
}


