#pragma once
#include "util.h"

class Bullet
{
	ColorNames Color;
	int X;
	int Y;
	int Radius;
	float theta;
	int step;
	bool Alive;
	bool isFired;
public:
	Bullet();
	void setX(int x) { this->X = x; }
	int getX() { return this->X; }
	void setY(int y) { this->Y = y; }
	int getY() { return this->Y; }
	void setRadius(int radius) { this->Radius = radius; }
	int getRadius() { return this->Radius; }
	void setTheta(float theta) { this->theta = theta; }
	float getTheta() { return this->theta; }
	void setStep(int step) { this->step = step; }
	int getStep() { return this->step; }
	void setAlive(bool Alive) { this->Alive = Alive; }
	bool getAlive() { return this->Alive; }
	void setColor(ColorNames Color) { this->Color = Color; }
	ColorNames getColor() { return this->Color; }
	void set_isFired(bool isFired) { this->isFired = isFired; }
	bool get_isFired() { return this->isFired; }


	Bullet(ColorNames c, int x, int y, int r, float t, bool a,bool);
	void setBullet(ColorNames, int, int, int, float, bool,bool);
	void leftMove();
	void rightMove();
	void topMove();
	void bottomMove();
	void move();
	void DrawCircle();
	float sign(Point p1, Point p2, Point p3);
	bool PointInTriangle(Point pt, Point v1, Point v2, Point v3);
	void update();

	~Bullet();
};

