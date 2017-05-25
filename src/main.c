#include <SDL/SDL.h>
#include <GL/gl.h>   
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "geometry/geometry.c"
#include "element/balle.c"
#include "element/barre.c"

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

  /********** Balle*******/
  Point2D position = PointXY(0.9,0);
  Vector2D direction = VectorXY(0.8,0.15);
  Color3f color = ColorRGB(255,255,255);
  Balles balles = BallFabrik(position, direction, color); 

  /***********************BARRE***********************/

  Point2D p1 = PointXY(0.2/MYSCALE,-0.85/MYSCALE);
  Point2D p2 = PointXY(-0.2/MYSCALE,-0.85/MYSCALE);
  Point2D p3 = PointXY(0.2/MYSCALE,-0.9/MYSCALE);
  Point2D p4 = PointXY(-0.2/MYSCALE,-0.9/MYSCALE);

  Vector2D d = VectorXY(1,0);
  Color3f color2 = ColorRGB(255,255,255);

  Barres barre = BarreFabrik(p1,p2,p3,p4,d,color2);
  int boolean = 0; 
  
  /* Boucle d'affichage */
  int loop = 1;    
  while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks(); 
    
    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);  

    /* ********************MATRICE DE LA BALLE********************* */
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    glScalef(MYSCALE, MYSCALE, 1);
    moveBall(balles);
    balles->position = Translation(balles->position, MultVector(balles->direction, MYSCALE) );
    limiteRepere(balles, 1/MYSCALE);
    glPushMatrix();

    /* ********************MATRICE DE LA BARRE********************* */
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    glScalef(MYSCALE, MYSCALE, 1);
    drawBarre(barre);
    moveBarre(barre, boolean);
    glPushMatrix();


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

          if( e.key.keysym.sym == SDLK_LEFT){
            if (limiteTerrain(barre->p1, barre->p2,1/MYSCALE) != 2)
            {
              boolean = 1;
              barre->direction.x = -10;
              moveBarre(barre, boolean);
              barre->p1 = Translation(barre->p1, MultVector(barre->direction, MYSCALE) );
              barre->p2 = Translation(barre->p2, MultVector(barre->direction, MYSCALE) );
              barre->p3 = Translation(barre->p3, MultVector(barre->direction, MYSCALE) );
              barre->p4 = Translation(barre->p4, MultVector(barre->direction, MYSCALE) );
            } 
          }

          if( e.key.keysym.sym == SDLK_RIGHT){
            if (limiteTerrain(barre->p1, barre->p2,1/MYSCALE) != 1 )
            {
              boolean = 1;
              barre->direction.x = 10;
              moveBarre(barre, boolean);
              barre->p1 = Translation(barre->p1, MultVector(barre->direction, MYSCALE) );
              barre->p2 = Translation(barre->p2, MultVector(barre->direction, MYSCALE) );
              barre->p3 = Translation(barre->p3, MultVector(barre->direction, MYSCALE) );
              barre->p4 = Translation(barre->p4, MultVector(barre->direction, MYSCALE) );
            }
            
          }
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
