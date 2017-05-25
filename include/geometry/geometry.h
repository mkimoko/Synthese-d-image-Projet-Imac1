#ifndef __GEOMETRY__H
#define __GEOMETRY__H

/** STRUCTURES **/

typedef struct
{
	float x, y;
} Vector2D;

typedef struct
{
	float x, y;
} Point2D;



typedef struct
{
	float r, g, b;
} Color3f;


/** FONCTIONS **/

/* Construit le point (x,y) */
Point2D PointXY(float x, float y);
/* Construit le vecteur (x,y) */
Vector2D VectorXY(float x, float y);
/* Construit le vecteur AB = B - A */
Vector2D Vector(Point2D A, Point2D B);
/* Construit le point P + V */
Point2D PointPlusVector(Point2D P, Vector2D V);
/* Addition de vecteur */
Vector2D AddVectors(Vector2D V, Vector2D W);
/* Soustraction de vecteur */
Vector2D SubVectors(Vector2D V, Vector2D W);
/* Multiplication de vecteur par un scalaire */
Vector2D MultVector(Vector2D V, float scalaire);
/* Division de vecteur par un scalaire */
Vector2D DivVector(Vector2D V, float scalaire);
/* Produit scalaire de vecteur */
float DotProduct(Vector2D V, Vector2D W);
/* Norme d'un vecteur */
float Norm(Vector2D V);
/* Normalisé d'un vecteur */
Vector2D Normalize(Vector2D V);

/* Addition de couleurs */
Color3f AddColors(Color3f C, Color3f D);
/* Soustraction de couleurs */
Color3f SubColors(Color3f C, Color3f D);
/* Multiplication de couleurs */
Color3f MultColors(Color3f C, Color3f D);
/* Division de couleurs */
Color3f DivColors(Color3f C, Color3f D);

/* Multiplication de couleur par un scalaire */
Color3f MultColor(Color3f C, float scalaire);
/* Division de couleur par un scalaire */
Color3f DivColor(Color3f C, float scalaire);

#endif