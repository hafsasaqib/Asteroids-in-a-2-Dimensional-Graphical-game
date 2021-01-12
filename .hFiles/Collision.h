#pragma once
#include"util.h "
#include<iostream>

class Collision
{
	int radius1,radius2;
	Point p1, p2;

public:

	Collision();
	bool isCircleCollision(Point,Point,int,int);	
	float calDistance(Point p1, Point p2);
	bool triangleCircleCollision(Point p1, Point p2, Point p3, int r1);
	virtual ~Collision();
};

