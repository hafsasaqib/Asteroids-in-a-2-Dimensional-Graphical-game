#pragma once
#include "util.h"
#include "Bullet.h"
#include "Collision.h"

#define	ENEMY_BULLET_COUNT	10
#define	ENEMY_BULLET_MOVE_STEP	10



class EnemySpaceShip
{
	int X1, Y1, X2, X3, Y2, Y3;
	ColorNames Color;
	bool Alive;
	int theta;
	int step;
	int currentEnemyBulletNumToFire;
	float enemyBulletFireTimer ;


	Collision C;

public:
	EnemySpaceShip();

	EnemySpaceShip(ColorNames, int, int, int, int, int, int, bool,int,int);
	void setEnemySpaceShip(ColorNames, int, int, int, int, int, int, bool,int,int);
	void setX1(int X1) { this->X1 = X1; }
	int getX1() { return this->X1; }
	void setY1(int Y1) { this->Y1 = Y1; }
	int getY1() { return this->Y1; }
	void setX2(int X2) { this->X2 = X2; }
	int getX2() { return this->X2; }
	void setY2(int Y2) { this->Y2 = Y2; }
	int getY2() { return this->Y2; }
	void setX3(int X3) { this->X3 = X3; }
	int getX3() { return this->X3; }
	void setY3(int Y3) { this->Y3 = Y3; }
	int getY3() { return this->Y3; }
	void setAlive(bool Alive) { this->Alive = Alive; }
	bool getAlive() { return this->Alive; }
	void setTheta(int theta) { this->theta = theta; }
	int getTheta() { return this->theta; }
	void setStep(int step) { this->step = step; }
	int getStep() { return this->step; }
	void setColor(ColorNames Color) { this->Color = Color; }
	ColorNames getColor() { return this->Color; }
	void setcurrentEnemyBulletNumToFire(int currentEnemyBulletNumToFire) { this->currentEnemyBulletNumToFire = currentEnemyBulletNumToFire; }
	int getcurrentEnemyBulletNumToFire() { return this->currentEnemyBulletNumToFire; }
	void setenemyBulletFireTimer(float enemyBulletFireTimer) { this->enemyBulletFireTimer = enemyBulletFireTimer; }
	float getenemyBulletFireTimer() { return this->enemyBulletFireTimer; }



	bool checkSpaceShipEnemySpaceShipBulletHit(Bullet *bulletList, int currentBulletNumToFire);

	Bullet enemyBulletList[ENEMY_BULLET_COUNT];

	int centralX();
	int centralY();
	virtual void move();
	void DrawTriangle();
	void setInitSide();
	virtual void update();
	bool PointInTriangle(Point pt, Point v1, Point v2, Point v3);
	float sign(Point p1, Point p2, Point p3);
	void initEnemyBullet();
	void drawEnemyBullet();
	void fireEnemyBullet();

	virtual ~EnemySpaceShip();
};

