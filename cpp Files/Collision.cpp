#include "Collision.h"
using namespace std;

Collision::Collision()
{
	radius1=radius2=0;
	p1.setPoint(0, 0);
	p2.setPoint(0, 0);
}


bool Collision::isCircleCollision(Point p1, Point p2, int r1, int r2)
{
	float distanceBetweenPoints;
	distanceBetweenPoints = calDistance(p1, p2);// sqrtf(((p2.y - p1.y) ^ 2 + (p2.x - p1.x) ^ 2));
	//cout << "distanceBetweenPoints = "<< distanceBetweenPoints<<" r1+ r2 ="<< r1 + r2<<endl;
	float Radius_ = r1 + r2;
	if (distanceBetweenPoints<(Radius_))
	{
		return true;
	}
	else
	{
		return false;
	}
}











float Collision::calDistance(Point p1, Point p2)//distance between triangle midpoint and its vertex
{

	return  sqrtf(((p2.y - p1.y) *(p2.y - p1.y) + (p2.x - p1.x) *(p2.x - p1.x)));
}











bool Collision::triangleCircleCollision(Point p1, Point p2,  Point p3 ,int r1)//3 points(triangle midpoint ,vertex and circle centre) and circle radius.
{
	float distanceBetweenPoints = calDistance(p1, p3);// abs((((p3.y - p1.y) * 2) -( (p3.x - p1.x) * 2))*0.5);//distance between circle centre and triangle midpoint 
	float temp = (calDistance(p1, p2) + r1);
	if (temp >(distanceBetweenPoints))
	{
		return true;
	}
	else
	{
		return false;
	}
}
Collision::~Collision()
{

}
