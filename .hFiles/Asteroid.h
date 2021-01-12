#pragma once
#include "util.h"
#include "Collision.h"
#include "Bullet.h"

class Asteroid
{
	
protected:
	ColorNames Color;
	int X, Y;
	int Radius;
	int Corners;
	bool Alive;
	int theta;
	int step;	

	Collision C;

public:
	
	Asteroid();
	Asteroid(ColorNames c, int x, int y, int r, int co, bool a);
	void setAsteroid(ColorNames,int,int,int,int,bool);

	void setColor(ColorNames Color) { this->Color = Color; }
	ColorNames getColor() { return this->Color; }
	void setX(int X) { this->X = X; }
	int getX() { return this->X; }
	void setY(int Y) { this->Y = Y; }
	int getY() { return this->Y; }
	void setRadius(int Radius) { this->Radius = Radius; }
	int getRadius() { return this->Radius; }
	void setCorners(int Corners) { this->Corners = Corners; }
	int getCorners() { return this->Corners; }
	void setAlive(bool Alive) { this->Alive = Alive; }
	bool getAlive() { return this->Alive; }
	void setTheta(int theta) { this->theta = theta; }
	int getTheta() { return this->theta; }
	void setStep(int step) { this->step = step; }
	int getStep() { return this->step; }

	bool checkAsteroidSpaceShipBulletHit(Bullet *bulletList, int currentBulletNumToFire);


	virtual void update();
	void rotateRight();
	void rotateLeft();
	virtual void move();
	void DrawAsteroid();
	void setInitSide();
	bool PointInTriangle(Point pt, Point v1, Point v2, Point v3);
	float sign(Point p1, Point p2, Point p3);

	~Asteroid();
};

