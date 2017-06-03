#include "../../include/niveau/niveau.h"



Mur murFabrik(Point2D p1, Point2D p2, Point2D p3, Point2D p4, int propriete){

	Mur mur = malloc(sizeof(Brik));

    if (mur != NULL)
    {
        mur->p1 = p1;
        mur->p2 = p2;
        mur->p3 = p3;
        mur->p4 = p4;
        mur->propriete = propriete;
        mur->next = NULL;
    }
	
	return mur;

}


void chargeLvl(char *chemin, Mur mur){

	char caractereActuel;
	FILE *fichier = malloc(sizeof(FILE));
	fichier = fopen(chemin,"r+");
	mur = malloc(sizeof(Brik));
	int i = 0, largeur = 0, hauteur = 0;

	do{

        caractereActuel = fgetc(fichier); // On lit le caractère

        printf("%c", caractereActuel); // On l'affiche

        if (i == 0)
        {
        	largeur = atoi(&caractereActuel);
        	printf("La largeur a été enregistré %d\n", largeur );
        }

        if (i == 2)
        {
        	hauteur = atoi(&caractereActuel);
        	printf("La hauteur a été enregistré %d\n", hauteur );
        }

        i++;

    } while (i <= 3);

    for (i = 0; i < hauteur*largeur*2; i++)
    {
       caractereActuel = fgetc(fichier); // On lit le caractère

       printf("%c\t", caractereActuel); // On l'affiche

       mur->propriete = atoi(&caractereActuel);
       printf("La valeur de tab[%d] est de %d\n",i, mur->propriete );
       mur->next = malloc(sizeof(Brik));
       mur = mur->next;
 
    }
	

}