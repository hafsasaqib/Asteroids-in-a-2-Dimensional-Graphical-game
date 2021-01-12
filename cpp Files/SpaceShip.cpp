#include "SpaceShip.h"

int SpaceShip::displayScore=0;

SpaceShip::SpaceShip()
{
	Color = PINK;
	X1 = Y1 = X2 = Y2 =X3 = Y3 =0;
	//centralX = X1 + X2 + X3 / 3; 
	//centralY = Y1 + Y2 + Y3 / 3;
	Alive = false;
	theta = 45;
	score = 0;
	//displayScore=0;
	step = 10;
	lives = 3;
}
float SpaceShip::centralX()
{
	float temp;
	temp= (X1 + X2 + X3) / 3;
	return temp;
}
float SpaceShip::centralY()
{
	float temp;
	temp = (Y1 + Y2 + Y3 )/ 3;
	return temp;
}
SpaceShip::SpaceShip(ColorNames c, float x1, float y1, float x2, float y2, float x3, float y3, bool a,int l ,int s)
{
	setSpaceShip(c, x1, y1, x2, y2, x3, y3, a,l,s);
}
void SpaceShip::setSpaceShip(ColorNames c, float x1, float y1, float x2, float y2, float x3, float y3, bool a,int l, int s)
{
	Color = c;
	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	X3 = x3;
	Y3 = y3;	
	score = s;
	Alive = a;
	lives = l;
	//displayScore = ds;
}

void SpaceShip::DrawTriangle(float x1,float x2, float x3,float y1, float y2, float y3)
{
	glColor3fv(colors[Color]); // Set the triangle colour
							   // ask library to draw triangle at given position...

	glBegin(GL_TRIANGLES);
	/*Draw triangle using given three vertices...*/
	//cout << "X1 ="<<X1 <<   "    Y1 =" << Y1 <<endl;
	//cout << "X2 =" << X2 << "    Y2 =" << Y2 << endl;
	//cout << "X3 =" << X3 << "    Y3 =" << Y3 << endl;
	glVertex4i(x1, y1, 0, 1);
	glVertex4i(x2, y2, 0, 1);
	glVertex4i(x3, y3, 0, 1);
	glEnd();
}
void SpaceShip::DrawTriangle() {
	glColor3fv(colors[Color]); // Set the triangle colour
					   // ask library to draw triangle at given position...

	glBegin(GL_TRIANGLES);
	/*Draw triangle using given three vertices...*/
	//cout << "X1 ="<<X1 <<   "    Y1 =" << Y1 <<endl;
	//cout << "X2 =" << X2 << "    Y2 =" << Y2 << endl;
	//cout << "X3 =" << X3 << "    Y3 =" << Y3 << endl;
	glVertex4i(X1, Y1, 0, 1);
	glVertex4i(X2, Y2, 0, 1);
	glVertex4i(X3, Y3, 0, 1);
	glEnd();

}
void SpaceShip::leftMove()
{
	 float tempCenterX;
	 tempCenterX = centralX();
	 float tempCenterY;
	 tempCenterY = centralY();

	 X1 -= tempCenterX;//first translate the points to the origin.
	 X2 -= tempCenterX;
	 X3 -= tempCenterX;
	 Y1 -= tempCenterY;
	 Y2 -= tempCenterY;
	 Y3 -= tempCenterY;

	 float NewX1 = X1;//new points equal to the already given points.
	 float NewX2 = X2;
	 float NewX3 = X3;
	 float NewY1 = Y1;
	 float NewY2 = Y2;
	 float NewY3 = Y3;

	 NewX1 = X1*(float)cos(Deg2Rad(9)) - Y1*(float)sin(Deg2Rad(9));//on one right button pressed 10 degree rotate because when 10 times right button pressed ship comes to its original position
	 NewX2 = X2*(float)cos(Deg2Rad(9)) - Y2*(float)sin(Deg2Rad(9));
	 NewX3 = X3*(float)cos(Deg2Rad(9)) - Y3*(float)sin(Deg2Rad(9));
	 NewY1 = X1*(float)sin(Deg2Rad(9)) + Y1*(float)cos(Deg2Rad(9));
	 NewY2 = X2*(float)sin(Deg2Rad(9)) + Y2*(float)cos(Deg2Rad(9));
	 NewY3 = X3*(float)sin(Deg2Rad(9)) + Y3*(float)cos(Deg2Rad(9));

	 X1 = NewX1;//alrady given points to the new points.
	 X2 = NewX2;
	 X3 = NewX3;
	 Y1 = NewY1;
	 Y2 = NewY2;
	 Y3 = NewY3;

	 X1 += tempCenterX;//translate back from the origin to the point.
	 X2 += tempCenterX;
	 X3 += tempCenterX;
	 Y1 += tempCenterY;
	 Y2 += tempCenterY;
	 Y3 += tempCenterY;

	 theta += 9;//as counter Clockwise so on every right button pressed an angle of 10 degree backward
	 if (theta >= 360)
	 {
		 theta -= 360;
	 }
	 if (X1 < -20)
	 {
		 X1 += 1020;
		 X2 += 1020;
		 X3 += 1020;
	 }
	 //B.setTheta(theta);
}
void SpaceShip::rightMove()
{
	float tempCenterX; 
	tempCenterX = centralX();
	float tempCenterY;
	tempCenterY = centralY();

	X1 -= tempCenterX;//first translate the points to the origin.
	X2 -= tempCenterX;
	X3 -= tempCenterX;
	Y1 -= tempCenterY;
	Y2 -= tempCenterY;
	Y3 -= tempCenterY;

	float NewX1 = X1;//new points equal to the already given points.
	float NewX2 = X2;
	float NewX3 = X3;
	float NewY1 = Y1;
	float NewY2 = Y2;
	float NewY3 = Y3;

	NewX1 =  X1*(float)cos(Deg2Rad(10)) + Y1*(float)sin(Deg2Rad(10));//on one right button pressed 10 degree rotate because when 10 times right button pressed ship comes to its original position
	NewX2 =  X2*(float)cos(Deg2Rad(10)) + Y2*(float)sin(Deg2Rad(10));
	NewX3 =  X3*(float)cos(Deg2Rad(10)) + Y3*(float)sin(Deg2Rad(10));
	NewY1 = -X1*(float)sin(Deg2Rad(10)) + Y1*(float)cos(Deg2Rad(10));
	NewY2 = -X2*(float)sin(Deg2Rad(10)) + Y2*(float)cos(Deg2Rad(10));
	NewY3 = -X3*(float)sin(Deg2Rad(10)) + Y3*(float)cos(Deg2Rad(10));

	X1 = NewX1;//alrady given points to the new points.
	X2 = NewX2;
	X3 = NewX3;
	Y1 = NewY1;
	Y2 = NewY2;
	Y3 = NewY3;

	X1 += tempCenterX;//translate back from the origin to the point.
	X2 += tempCenterX;
	X3 += tempCenterX;
	Y1 += tempCenterY;
	Y2 += tempCenterY;
	Y3 += tempCenterY;

	theta -= 10;//as counter Clockwise so on every right button pressed an angle of 10 degree backward
	if (theta <= -360)
	{
		theta += 360;
	}
	//B.setTheta(theta);
}
void SpaceShip::topMove()
{
	float slopX = step*cos(Deg2Rad(theta));//find slop so that when rotate its original theta changes anf then run on the slop to move in that direction.
	float slopY = step*sin(Deg2Rad(theta));
	X1 += slopX;
	X2 += slopX;
	X3 += slopX;
	Y1 += slopY;
	Y2 += slopY;
	Y3 += slopY;

	if (Y1 > 860)
	{
		Y1 -= 840;
		Y2 -= 840;
		Y3 -= 840;
	}
	if (Y1 < -20)
	{
		Y1 += 840;
		Y2 += 840;
		Y3 += 840;
	}
	if (X1 < -20)
	{
		X1 += 1020;
		X2 += 1020;
		X3 += 1020;
	}
	if (X1 > 1020)
	{
		X1 -= 1020;
		X2 -= 1020;
		X3 -= 1020;
	}
	//B.setTheta(theta);
}
void SpaceShip::bottomMove()
{
	Y1 -= 5;
	Y2 -= 5;
	Y3 -= 5;

	if (Y1 < -20)
	{
		Y1 += 840;
		Y2 += 840;
		Y3 += 840;
	}
	//B.setTheta(theta);
}
SpaceShip::~SpaceShip()
{
}

bool SpaceShip::checkSpaceShipAsteroidCollision(Asteroid *asteroid)
{
	bool isHit = false;
	Point pt1, pt2;
	float r1, r2;
	for (int i = 0; i < ASTEROID_COUNT; i++)
	{
		if (asteroid[i].getAlive())
		{
			pt1.x = this->centralX();
			pt1.y = this->centralY();

			pt2.x = asteroid[i].getX();
			pt2.y = asteroid[i].getY();
			r1 = 25;
			r2 = 48;
			isHit = C.isCircleCollision(pt1, pt2, r1, r2);
			if (isHit == true)
			{
				this->Alive = false;
				return isHit;
			}
		}
	}
	return isHit;
}

bool SpaceShip::checkSpaceShipEnemySpaceShipCollision(EnemySpaceShip *enemySpaceShip)
{
	bool isHit = false;
	Point pt1, pt2;
	float r1, r2;
	for (int i = 0; i < ASTEROID_COUNT; i++)
	{
		if (enemySpaceShip[i].getAlive())
		{
			pt1.x = this->centralX();
			pt1.y = this->centralY();

			pt2.x = enemySpaceShip[i].centralX();
			pt2.y = enemySpaceShip[i].centralY();
			r1 = 25;
			r2 = 48;
			isHit = C.isCircleCollision(pt1, pt2, r1, r2);
			if (isHit == true)
			{
				this->Alive = false;
				return isHit;
			}
		}
	}
	return isHit;
}
bool SpaceShip::checkSpaceShipEnemySpaceShipBulletHit(EnemySpaceShip *enemySpaceShipList, int currentEnemyBulletNumToFire)
{
	bool isHit = false;
	Point pt1, pt2;
	float r1,r2;
	for (int i = 0; i < currentEnemyBulletNumToFire; i++)
	{
		if (enemySpaceShipList[i].enemyBulletList[i].getAlive() == true && enemySpaceShipList[i].enemyBulletList[i].get_isFired() == true)
		{
			pt1.x = this->getX1();
			pt1.y = this->getY1();

			pt2.x = enemySpaceShipList[i].enemyBulletList[i].getX();
			pt2.y = enemySpaceShipList[i].enemyBulletList[i].getY();
			r1 = 1;
			r2 = 48;
			isHit = C.isCircleCollision(pt1, pt2, r1, r2);
			if (isHit == true)
			{
				this->Alive = false;
				return isHit;
			}
		}

	}
	return isHit;
}

