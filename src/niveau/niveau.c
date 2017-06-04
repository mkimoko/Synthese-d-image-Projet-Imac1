#include "../../include/niveau/niveau.h"



Brik brikFabrik(Point2D p1, Point2D p2, Point2D p3, Point2D p4, int propriete){

	Brik brik;

        brik.p1 = p1;
        brik.p2 = p2;
        brik.p3 = p3;
        brik.p4 = p4;
        brik.propriete = propriete;
	
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

    Point2D tmp1 = PointXY( ((-limit/2) +ecart) / ecart, ((limit/4)+ecart)/ecart );
    Point2D tmp2 = PointXY( tmp1.x  + (limit/mur->largeur)/ecart, ((limit/4)+ecart)/ecart );
    Point2D tmp3 = PointXY( tmp2.x / ecart, (tmp2.y + limit/mur->hauteur) / ecart );
    Point2D tmp4 = PointXY( tmp1.x / ecart, tmp3.y / ecart);  

    for (i = 0; i <= max*max; i++)
    {
      for (j = 0; j <= mur->largeur * 2; j++)
      {
        if (i >= mur->hauteur/2)
          mult = 1;
        p1 = PointXY(tmp1.x + (j/2)*tmp1.x * ecart, tmp1.y + (i/2)* tmp1.y * ecart );
        tmp1 = p1;
        p2 = PointXY( tmp2.x + (j/2)*tmp2.x * ecart, tmp1.y + (i/2)* tmp2.y * ecart );
        tmp2 = p2;
        p3 = PointXY( tmp3.x + (j/2)*tmp3.x * ecart, tmp3.y + (i/2)* tmp3.y * ecart );
        tmp3 = p3;
        p4 = PointXY( tmp4.x + (j/2)*tmp4.x * ecart, tmp4.y + (i/2)* tmp4.y * ecart);
        tmp4 = p4;
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
    glBegin(GL_QUADS);
    for (int i = 0; i < mur->hauteur * mur->hauteur; i++)
    {
      glColor3d( 240, 195, 0 );
      glVertex2f(mur->niveau[i].p1.x, mur->niveau[i].p1.y);
      glVertex2f(mur->niveau[i].p2.x, mur->niveau[i].p2.y);
      glVertex2f(mur->niveau[i].p3.x, mur->niveau[i].p3.y);
      glVertex2f(mur->niveau[i].p4.x, mur->niveau[i].p4.y);
    glEnd();
    }
        
}