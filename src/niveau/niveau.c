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
  int haut = 0, large = 0;
  int cpt = 0;
  float decalX = 2*limit/mur->largeur, decalY = limit/mur->hauteur, posX = -limit, posY = limit/2 ;


  float x1 = 0, y1 = 0, x2 = 0, y2 = 0 , x3 = 0, y3 = 0, x4 = 0, y4 = 0;

  for (haut = 0; haut < 1/* mur->hauteur */; haut++)
  {
    for ( large = 0; large < mur->largeur; large++)
    {
      /*P1*/
      x1 = (posX + large*decalX) ;
      y1 = (posY - haut*decalY) ;
      mur->niveau[cpt].p1 = PointXY( x1,y1 );

      /*P2*/
      x2 = (posX + (large+1)*decalX);
      y2 = (posY - haut*decalY);
      mur->niveau[cpt].p2 = PointXY( x2,y2 );

      /*P3*/
      x3 = (posX + (large+1)*decalX);
      y3 = (posY - (haut+1)*decalY);
      mur->niveau[cpt].p3 = PointXY( x3,y3 );

      /*P4*/
      x4 = (posX + large*decalX);
      y4 = (posY - (haut+1)*decalY);
      mur->niveau[cpt].p4 = PointXY( x4,y4 );
        
        printf("\n");
      printf("%d - Les coordonnées de p1: x= %f  y= %f \n",cpt, mur->niveau[cpt].p1.x, mur->niveau[cpt].p1.y );
      printf("%d - Les coordonnées de p2: x= %f  y= %f \n",cpt, mur->niveau[cpt].p2.x, mur->niveau[cpt].p2.y );
      printf("%d - Les coordonnées de p3: x= %f  y= %f \n",cpt, mur->niveau[cpt].p3.x, mur->niveau[cpt].p3.y );
      printf("%d - Les coordonnées de p4: x= %f  y= %f \n",cpt, mur->niveau[cpt].p4.x, mur->niveau[cpt].p4.y );


        cpt++;
    }
  }
}

void drawBrik(Brik brik){
  glBegin(GL_QUADS);
          glColor3d( 255, 255, 0 );
          glVertex2f(brik.p1.x, brik.p1.y);
          glVertex2f(brik.p2.x, brik.p2.y);
          glVertex2f(brik.p3.x, brik.p3.y);
          glVertex2f(brik.p4.x, brik.p4.y);
        glEnd();
}

void drawMur(Wall mur){
    
    for (int i = 0; i < mur->hauteur * mur->largeur; i++)
    {
      if (mur->niveau[i].touche == 0)
      {
        drawBrik(mur->niveau[i]);
      }
    }     
}

/*Fonction collision ne marche pas correctement pour le bon déroulement de la partie nous avons décider de le laisser en commentaire
  Vous pouvez néamoins les enlevés pour voir ce que fait la fonction*/

int collision(Wall wall, Player j, Player adv){

  
  for (int i = 0; i < wall->hauteur * wall->largeur; i++)
  {

    if (wall->niveau[i].touche == 0)
    {
      /*Balle arrivant par le bas*
      if ()
      {
        /*shoot vers le haut
        shoot(j->balles); 
        return 1;     
      }*/

      /*Balle arrivant par le haut*
      if ()
      {
        /*shoot vers le haut*
        shoot(j->balles); 
        return 1;     
      }*/

    }

    /*contactBrik(wall->niveau[i], j);*/
  }

  return 0;

}


void contactBrik (Brik brik, Player j){

  /*Vector2D normal = Normalize(j->balles-> direction);

  /*Balle arrivant par le coté droit
  if ( j->balles->position.x <= brik.p2.x /* && j->balles->direction.x < 0  && j->balles->position.y <= brik.p2.y && j->balles->position.y >= brik.p3.y)
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

      }

      /*Balle arrivant par le coté gauche
      if ( j->balles->position.x >= brik.p1.x /*&& j->balles->direction.x > 0 && j->balles->position.y <= brik.p1.y && j->balles->position.y >= brik.p4.y)
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

      }*/
}


