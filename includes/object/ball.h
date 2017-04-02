#ifndef __BALL__H
#define __BALL__H

#include "../geometry/geometry.h"
#define PI 3.14159265
#define SEGMENTS 1024

typedef struct Ball
{
  Point2D position;
  Vector2D direction;
  float radius;
  float speed;
  GLuint texture;
} Ball;

Ball initBall(Point2D position,Vector2D direction,float radius, float speed, GLuint texture);
