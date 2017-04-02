#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "../includes/sdl_tools.h"
#include "ball.c"


/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


int main(int argc, char** argv) {

    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    SDL_Surface* screen = NULL;
    if(NULL == (screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, 
        SDL_DOUBLEBUF))) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("Raytracing powa :D", NULL);
    
    /* Création d'une surface SDL dans laquelle le raytracer dessinera */
    SDL_Surface* framebuffer = NULL;
    if(NULL == (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH, 
        WINDOW_HEIGHT, BIT_PER_PIXEL, 0, 0, 0, 0))) {
        fprintf(stderr, "Erreur d'allocation pour le framebuffer. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    int loop = 1;
    while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    
    /* Placer ici le code de dessin */
    draw_ball();
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
          printf("clic en (%d, %d)\n", e.button.x, e.button.y);
          break;
          
        /* Touche clavier */
        case SDL_KEYDOWN:
          printf("touche pressée (code = %d)\n", e.key.keysym.sym);
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
  
    SDL_Quit();
    
    return EXIT_SUCCESS;
}