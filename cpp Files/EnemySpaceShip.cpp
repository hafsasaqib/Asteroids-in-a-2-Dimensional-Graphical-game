#include "EnemySpaceShip.h"
#define TOP		1
#define RIGHT	2
#define BOTTOM	3
#define LEFT	4


EnemySpaceShip::EnemySpaceShip()
{
	Color = PINK;
	X1 = Y1 = X2 = Y2 = X3 = Y3 = 0;
	Alive = false;
	theta = 45;
	step = 10;
	currentEnemyBulletNumToFire = 0;
	enemyBulletFireTimer = ENEMY_BULLET_FIRE_INTERVAL;

}
EnemySpaceShip::EnemySpaceShip(ColorNames c, int x1, int y1, int x2, int y2, int x3, int y3, bool a, int NumToFire, int interval)
{
	setEnemySpaceShip(c, x1, y1, x2, y2, x3, y3, a, NumToFire, interval);
}
void EnemySpaceShip::setEnemySpaceShip(ColorNames c, int x1, int y1, int x2, int y2, int x3, int y3, bool a,int NumToFire, int interval)
{
	Color = c;
	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	X3 = x3;
	Y3 = y3;
	Alive = a;
	currentEnemyBulletNumToFire = NumToFire;
	enemyBulletFireTimer = interval;
}
int EnemySpaceShip::centralX()
{
	int temp;
	temp = (X1 + X2 + X3) / 3;
	return temp;
}
int EnemySpaceShip::centralY()
{
	int temp;
	temp = (Y1 + Y2 + Y3) / 3;
	return temp;
}
void EnemySpaceShip::initEnemyBullet()//initialization of enemy bullet
{
	int t;
	currentEnemyBulletNumToFire = 0;
	for (int i = 0;i < ENEMY_BULLET_COUNT;i++)
	{
		enemyBulletList[i].setRadius(5);
		enemyBulletList[i].setX(X1);
		enemyBulletList[i].setY(Y1);
		enemyBulletList[i].setColor(Color);
		enemyBulletList[i].setAlive(true);
		enemyBulletList[i].set_isFired(false);
		t = GetRandInRange(0, 359);
		enemyBulletList[i].setTheta(t);
		enemyBulletList[i].setStep(ENEMY_BULLET_MOVE_STEP);
	}

}
void EnemySpaceShip::drawEnemyBullet()
{
	for (int i = 0;i < currentEnemyBulletNumToFire;i++)
	{
		if (enemyBulletList[i].getAlive() == true && enemyBulletList[i].get_isFired() == true)
		{
			enemyBulletList[i].move();
			enemyBulletList[i].update();
			enemyBulletList[i].DrawCircle();
		}

	}
}

void EnemySpaceShip::fireEnemyBullet()
{	
	enemyBulletList[currentEnemyBulletNumToFire].setX(X1);
	enemyBulletList[currentEnemyBulletNumToFire].setY(Y1);
	enemyBulletList[currentEnemyBulletNumToFire].set_isFired(true);

	if (currentEnemyBulletNumToFire >= ENEMY_BULLET_COUNT-1)//after coming to Max limit then equal to zero
	{
		for (int i = 0; i <ENEMY_BULLET_COUNT; i++)//after reaching the limit of Max set all the Alive True
		{
			enemyBulletList[i].setAlive(true);
		}
		currentEnemyBulletNumToFire = 0;
	}
	else
	{
		currentEnemyBulletNumToFire++;
	}	
}
void EnemySpaceShip::DrawTriangle() {
	glColor3fv(colors[Color]); // Set the triangle colour
							   // ask library to draw triangle at given position...

	glBegin(GL_TRIANGLES);
	/*Draw triangle using given three vertices...*/
	glVertex4i(X1, Y1, 0, 1);
	glVertex4i(X2, Y2, 0, 1);
	glVertex4i(X3, Y3, 0, 1);
	glEnd();
}
void EnemySpaceShip::move()
{
	X1 = X1 + step*cos(theta);
	Y1 = Y1 + step*sin(theta);
	X2 = X2 + step*cos(theta);
	Y2 = Y2 + step*sin(theta);
	X3 = X3 + step*cos(theta);
	Y3 = Y3 + step*sin(theta);
}
EnemySpaceShip::~EnemySpaceShip()
{
}
float EnemySpaceShip::sign(Point p1, Point p2, Point p3)							//////
{																						//					
	return (p1.x-p3.x)*(p2.y-p3.y) - (p2.x-p3.x)*(p1.y-p3.y);							//
}																						//
bool EnemySpaceShip::PointInTriangle(Point pt, Point v1, Point v2, Point v3)			//
{																						//				
	bool b1, b2, b3;																	//checking that either the point is within the screen? 
	b1 = sign(pt, v1, v2) < 0.0f;														//	
	b2 = sign(pt, v2, v3) < 0.0f;														//				
	b3 = sign(pt, v3, v1) < 0.0f;														//	
																						//			
	return ((b1==b2)&&(b2==b3));														//	
}																					//////	
void EnemySpaceShip::update()
{
	//cout << "X :" << X << "Y :" << Y<<endl;
	Point pt(X1, Y1), v1(0, WINDOW_HEIGHT), v2(WINDOW_WIDTH, 0), v3(WINDOW_WIDTH, WINDOW_HEIGHT);
	bool inOne = PointInTriangle(pt, v1, v2, v3);
	if (inOne)
	{
		//cout << "point inside trriangle one";
	}
	else
	{
		//cout << "point not inside trriangle one" << endl;
		pt.setPoint(X1, Y1), v1.setPoint(0, WINDOW_HEIGHT), v2.setPoint(WINDOW_WIDTH, 0), v3.setPoint(0, 0);
		inOne = PointInTriangle(pt, v1, v2, v3);
		if (inOne)
		{
			//cout << "point inside trriangle two" << endl;
		}
		else
		{
			//cout << "point not inside trriangle two" << endl;
			setInitSide();
		}
	}
}
void EnemySpaceShip::setInitSide()
{
	int s;//for side
	s = GetRandInRange(1, 4);
	if (s == TOP)
	{
		X1 = GetRandInRange(0, WINDOW_WIDTH);
		Y1 = 0;		 
		X2=(X1 + 30);
		Y2=(Y1 - 30);
		X3=(X1 - 30);
		Y3=(Y1 - 30);
		theta = GetRandInRange(180, 360);
	}
	else if (s == RIGHT)
	{
		X1 = WINDOW_WIDTH;
		Y1 = GetRandInRange(0, WINDOW_HEIGHT);
		X2 = (X1 + 30);
		Y2 = (Y1 - 30);
		X3 = (X1 - 30);
		Y3 = (Y1 - 30);
		theta = GetRandInRange(90, 270);
	}
	else if (s == BOTTOM)
	{
		X1 = GetRandInRange(0, WINDOW_WIDTH);
		Y1 = WINDOW_HEIGHT;
		X2 = (X1 + 30);
		Y2 = (Y1 - 30);
		X3 = (X1 - 30);
		Y3 = (Y1 - 30);
		theta = GetRandInRange(0, 180);
	}
	else if (s == LEFT)
	{
		X1 = 0;
		Y1 = GetRandInRange(0, WINDOW_HEIGHT);
		X2 = (X1 + 30);
		Y2 = (Y1 - 30);
		X3 = (X1 - 30);
		Y3 = (Y1 - 30);
		theta = GetRandInRange(270, 450);
		theta > 360 ? theta - 360 : theta;	//checking for theta in [270,360] OR [0,90]
	}
}
bool EnemySpaceShip::checkSpaceShipEnemySpaceShipBulletHit(Bullet *bulletList, int currentBulletNumToFire)
{
	bool isHit = false;
	Point pt1, pt2;
	float r1,r2;
	for (int i = 0; i < currentBulletNumToFire; i++)
	{
		if (bulletList[i].getAlive()==true && bulletList[i].get_isFired()==true)
		{
			pt1.x = this->getX1();//this->centralX();
			pt1.y = this->getY1();//this->centralY();

			pt2.x = bulletList[i].getX();
			pt2.y = bulletList[i].getY();
			r1=5;
			r2 =15;
			isHit = C.isCircleCollision(pt1, pt2, r1,r2);
			if (isHit==true)
			{
				this->Alive = false;
				return isHit;
			}
		}

	}
	return isHit;
}