#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../../include/geometry/geometry.h"

#define min(x,y) (x<y ? x : y)
#define max(x,y) (x>=y ? x : y)

Point2D PointXY(float x, float y)
{
	Point2D point;
	point.x = x;
	point.y = y;

	return point;
}

Vector2D VectorXYZ(float x, float y)
{
	Vector2D vector;
	vector.x = x;
	vector.y = y;

	return vector;
}

Vector2D Vector(Point2D A, Point2D B)
{
	Vector3D vector;
	vector.x = B.x - A.x;
	vector.y = B.y - A.y;

	return vector;
}

Point2D PointPlusVector(Point2D P, Vector2D V)
{
	Point2D point;
	point.x = P.x + V.x;
	point.y = P.y + V.y;

	return point;
}

Vector2D AddVectors(Vector2D V, Vector2D W)
{
	Vector2D vector;
	vector.x = V.x + W.x;
	vector.y = V.y + W.y;

	return vector;
}

Vector2D SubVectors(Vector2D V, Vector2D W)
{
	Vector2D vector;
	vector.x = V.x - W.x;
	vector.y = V.y - W.y;

	return vector;
}

Vector2D MultVector(Vector2D V, float scalaire)
{
	Vector3D vector;
	vector.x = V.x * scalaire;
	vector.y = V.y * scalaire;

	return vector;
}

Vector2D DivVector(Vector2D V, float scalaire)
{
	Vector2D vector;
	vector.x = V.x / scalaire;
	vector.y = V.y / scalaire;

	return vector;
}

float DotProduct(Vector2D V, Vector2D W)
{
	return (V.x * W.x) + (V.y * W.y);
}

float Norm(Vector2D V)
{
	return sqrt((V.x * V.x) + (V.y * V.y));
}

Vector2D Normalize(Vector2D V)
{
	float norm = Norm(V);
	Vector2D vector;
	vector.x = V.x / norm;
	vector.y = V.y / norm;

	return vector;
}

Color3f AddColors(Color3f C, Color3f D)
{
	Color3f addition;
	addition.r = min(C.r + D.r, 1.f);
	addition.g = min(C.g + D.g, 1.f);
	addition.b = min(C.b + D.b, 1.f);
	
	return addition;
}

Color3f SubColors(Color3f C, Color3f D)
{
	Color3f substraction;
	substraction.r = max(C.r - D.r, 0.f);
	substraction.g = max(C.g - D.g, 0.f);
	substraction.b = max(C.b - D.b, 0.f);
	
	return substraction;
}

Color3f MultColors(Color3f C, Color3f D){
	Color3f multiplication;
	multiplication.r = C.r * D.r;
	multiplication.g = C.g * D.g;
	multiplication.b = C.b * D.b;
	
	return multiplication;
}

Color3f DivColors(Color3f C, Color3f D)
{
	Color3f division;
	division.r = C.r / D.r;
	division.g = C.g / D.g;
	division.b = C.b / D.b;
	
	return division;
}

Color3f MultColor(Color3f C, float scalaire){
	Color3f multiplication;
	multiplication.r = C.r * scalaire;
	multiplication.g = C.g * scalaire;
	multiplication.b = C.b * scalaire;
	
	return multiplication;
}

Color3f DivColor(Color3f C, float scalaire)
{
	Color3f division;
	division.r = C.r / scalaire;
	division.g = C.g / scalaire;
	division.b = C.b / scalaire;
	
	return division;
}