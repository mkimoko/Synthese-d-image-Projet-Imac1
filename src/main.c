#include <SDL/SDL.h>
#include <GL/gl.h>   
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "geometry/geometry.c"
#include "element/joueur.c"


#define MYSCALE 0.05

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800; 
static unsigned int WINDOW_HEIGHT = 800;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char** argv) {
  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  
  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    return EXIT_FAILURE;
  }  

  gluOrtho2D(-1., 1., -1., 1.);
    
  /* Titre de la fenêtre */
  SDL_WM_SetCaption("Shall we begin this arkanopong ?!", NULL);


  /****************************JOUEUR 1*************************************/

  /*************************** BALLE 1*****************************/
  Point2D position = PointXY(0.9,0);
  Vector2D direction = VectorXY(0.8,1);
  Color3f color = ColorRGB(255,255,255);
  Balles balles = BallFabrik(position, direction, color); 

  /***********************BARRE 1***********************/

  Point2D p1 = PointXY(0.2/MYSCALE,-0.85/MYSCALE);
  Point2D p2 = PointXY(-0.2/MYSCALE,-0.85/MYSCALE);
  Point2D p3 = PointXY(0.2/MYSCALE,-0.9/MYSCALE);
  Point2D p4 = PointXY(-0.2/MYSCALE,-0.9/MYSCALE);

  Vector2D d = VectorXY(1,0);
  Color3f color2 = ColorRGB(255,255,255);

  Barres barre = BarreFabrik(p1,p2,p3,p4,d,color2);
  int boolean = 0; 
  
  Player j1 = joueurFabrik(barre, balles, color);

  /**************************FIN JOUEUR 1*******************************/





/****************************JOUEUR 2*************************************/

  /*************************** BALLE 2*****************************/
  position = PointXY(-0.9,0);
  direction = VectorXY(-0.8,-1);
  color = ColorRGB(255,255,255);
  balles = BallFabrik(position, direction, color); 

  /***********************BARRE 2***********************/

  p1 = PointXY(0.2/MYSCALE,0.85/MYSCALE);
  p2 = PointXY(-0.2/MYSCALE,0.85/MYSCALE);
  p3 = PointXY(0.2/MYSCALE,0.9/MYSCALE);
  p4 = PointXY(-0.2/MYSCALE,0.9/MYSCALE);

  d = VectorXY(1,0);
  color2 = ColorRGB(255,255,255);

  barre = BarreFabrik(p1,p2,p3,p4,d,color2);
  int boolean2 = 0; 
  
  Player j2 = joueurFabrik(barre, balles, color);    

  /**************************FIN JOUEUR 2*******************************/





  /* Boucle d'affichage */
  int loop = 1;    
  while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks(); 
    
    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT); 

/***********************LES MATRICES DU JOUEUR 1********************************/     

    /* ********************MATRICE DE LA BALLE 1********************* */
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    glScalef(MYSCALE, MYSCALE, 1);
    moveBall(j1->balles);
    j1->balles->position = Translation(j1->balles->position, MultVector(j1->balles->direction, MYSCALE) );
    limiteRepere(j1->balles, 1/MYSCALE);
    glPushMatrix();

    /* ********************MATRICE DE LA BARRE 1********************* */
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    glScalef(MYSCALE, MYSCALE, 1);
    drawBarre(j1->barre);
    moveBarre(j1->barre, boolean);
    glPushMatrix();


  /***********************CONTACT BARRE BALLE J1 + SHOOT**************************/

    /***Contact barre du joueur 1 et balle du joueur 1****/ 
    if ( contactInf(j1->barre, j1->balles) == 1)
    {
      shoot(j1->balles);
    }

    /***Contact barre du joueur 1 et balle du joueur 2****/ 
    if ( contactInf(j1->barre, j2->balles) == 1)
    {
      shoot(j2->balles);
    }


/*****************************FIN DES MATRICES JOUEUR 1*******************************/




/***********************LES MATRICES DU JOUEUR 2********************************/     

    /* ********************MATRICE DE LA BALLE 2********************* */
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    glScalef(MYSCALE, MYSCALE, 1);
    moveBall(j2->balles);
    j2->balles->position = Translation(j2->balles->position, MultVector(j2->balles->direction, MYSCALE) );
    limiteRepere(j2->balles, 1/MYSCALE);
    glPushMatrix();

    /* ********************MATRICE DE LA BARRE 2********************* */
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    glScalef(MYSCALE, MYSCALE, 1);
    drawBarre(j2->barre);
    moveBarre(j2->barre, boolean2);
    glPushMatrix();


    /***********************CONTACT BARRE BALLE J2 + SHOOT**************************/

    /***Contact barre du joueur 2 et balle du joueur 1****/ 
    if ( contactSup(j2->barre, j1->balles) == 1)
    {
      shoot(j1->balles);
    }

    /***Contact barre du joueur 2 et balle du joueur 2****/ 
    if ( contactSup(j2->barre, j2->balles) == 1 )
    {
      shoot(j2->balles);
    }

/*****************************FIN DES MATRICES JOUEUR 2*******************************/









    /* Echange du front et du back buffer : mise à jour de la fenêtre */
    SDL_GL_SwapBuffers();
    
    /* Boucle traitant les evenements */
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      /* L'utilisateur ferme la fenêtre : */
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
      
      /* Quelques exemples de traitement d'evenements : */
      switch(e.type) {
        /* Clic souris */
        case SDL_MOUSEBUTTONUP:
          
          break;

          case SDL_MOUSEMOTION: 
          
          break;


        /* Touche clavier */
        case SDL_KEYDOWN:


        /*********************CAS BARRE JOUEUR 1**************************/
          if( e.key.keysym.sym == SDLK_LEFT){


            if (limiteTerrain(j1->barre->p1, j1->barre->p2,1/MYSCALE) != 2)
            {
              boolean = 1;
              j1->barre->direction.x = -10;
              moveBarre(j1->barre, boolean);
              j1->barre->p1 = Translation(j1->barre->p1, MultVector(j1->barre->direction, MYSCALE) );
              j1->barre->p2 = Translation(j1->barre->p2, MultVector(j1->barre->direction, MYSCALE) );
              j1->barre->p3 = Translation(j1->barre->p3, MultVector(j1->barre->direction, MYSCALE) );
              j1->barre->p4 = Translation(j1->barre->p4, MultVector(j1->barre->direction, MYSCALE) );
            } 
          }

          if( e.key.keysym.sym == SDLK_RIGHT){
            if (limiteTerrain(j1->barre->p1, j1->barre->p2,1/MYSCALE) != 1 )
            {
              boolean = 1;
              j1->barre->direction.x = 10;
              moveBarre(j1->barre, boolean);
              j1->barre->p1 = Translation(j1->barre->p1, MultVector(j1->barre->direction, MYSCALE) );
              j1->barre->p2 = Translation(j1->barre->p2, MultVector(j1->barre->direction, MYSCALE) );
              j1->barre->p3 = Translation(j1->barre->p3, MultVector(j1->barre->direction, MYSCALE) );
              j1->barre->p4 = Translation(j1->barre->p4, MultVector(j1->barre->direction, MYSCALE) );
            }
          }

          /***********************FIN CAS BARRE JOUEUR 1********************/


          /*********************CAS BARRE JOUEUR 2**************************/

          if( e.key.keysym.sym == SDLK_a){

            
            if (limiteTerrain(j2->barre->p1, j2->barre->p2,1/MYSCALE) != 2)
            {
              boolean2 = 1;
              j2->barre->direction.x = -10;
              moveBarre(j2->barre, boolean2);
              j2->barre->p1 = Translation(j2->barre->p1, MultVector(j2->barre->direction, MYSCALE) );
              j2->barre->p2 = Translation(j2->barre->p2, MultVector(j2->barre->direction, MYSCALE) );
              j2->barre->p3 = Translation(j2->barre->p3, MultVector(j2->barre->direction, MYSCALE) );
              j2->barre->p4 = Translation(j2->barre->p4, MultVector(j2->barre->direction, MYSCALE) );
            } 
          }

          if( e.key.keysym.sym == SDLK_z){
            if (limiteTerrain(j2->barre->p1, j2->barre->p2,1/MYSCALE) != 1 )
            {
              boolean2 = 1;
              j2->barre->direction.x = 10;
              moveBarre(j2->barre, boolean2);
              j2->barre->p1 = Translation(j2->barre->p1, MultVector(j2->barre->direction, MYSCALE) );
              j2->barre->p2 = Translation(j2->barre->p2, MultVector(j2->barre->direction, MYSCALE) );
              j2->barre->p3 = Translation(j2->barre->p3, MultVector(j2->barre->direction, MYSCALE) );
              j2->barre->p4 = Translation(j2->barre->p4, MultVector(j2->barre->direction, MYSCALE) );
            }
          }

          /***********************FIN CAS BARRE JOUEUR 2********************/


          if( e.key.keysym.sym == SDLK_q)
            SDL_Quit();
          break;

          
        default:
          break;
      }


    }

    /* Calcul du temps écoulé */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    /* Si trop peu de temps s'est écoulé, on met en pause le programme */
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }
  
  /* Liberation des ressources associées à la SDL */ 
  SDL_Quit();
  
  return EXIT_SUCCESS;
}
