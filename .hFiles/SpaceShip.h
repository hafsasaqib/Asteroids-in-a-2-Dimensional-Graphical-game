#pragma once
#include "util.h"
#include "Collision.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "EnemySpaceShip.h"

class SpaceShip
{
	float X1,Y1,X2,X3,Y2,Y3;
	//int centralX, centralY;
	ColorNames Color;
	bool Alive;
	float theta;
	int step;
	int score;
	int lives;

	Collision C;
	EnemySpaceShip ESS;

public:
	static int displayScore;
	SpaceShip();
	SpaceShip(ColorNames,float , float, float, float, float, float, bool,int,int);
	void setSpaceShip(ColorNames, float, float, float, float, float, float, bool,int,int);
	void setX1(int X1) { this->X1 = X1; }
	float getX1() { return this->X1; }
	void setY1(float Y1) { this->Y1 = Y1; }
	float getY1() { return this->Y1; }
	void setX2(float X2) { this->X2 = X2; }
	float getX2() { return this->X2; }
	void setY2(float Y2) { this->Y2 = Y2; }
	float getY2() { return this->Y2; }
	void setX3(float X3) { this->X3 = X3; }
	float getX3() { return this->X3; }
	void setY3(float Y3) { this->Y3 = Y3; }
	float getY3() { return this->Y3; }
	void setAlive(bool Alive) { this->Alive = Alive; }
	bool getAlive() { return this->Alive; }
	void setTheta(float theta) { this->theta = theta; }
	float getTheta() { return this->theta; }
	void setStep(int step) { this->step = step; }
	int getStep() { return this->step; }
	//void setDisplayScore(int displayScore) { this->displayScore = displayScore; }
	//int getDisplayScore() { return this->displayScore; }
	void setScore(int score) { this->score = score; }
	int getScore() { return this->score; }
	void setColor(ColorNames Color) { this->Color = Color; }
	ColorNames getColor() { return this->Color; }
	void setLives(int lives) { this->lives = lives; }
	float getLives() { return this->lives; }
	//bool checkSpaceShipBulletHit(Bullet *bulletList, int currentBulletNumToFire);
	//bool checkAsteroidHit(Asteroid *Asteroid, int asteroidCount);

	bool checkSpaceShipAsteroidCollision(Asteroid *asteroid);
	bool checkSpaceShipEnemySpaceShipCollision(EnemySpaceShip *enemySpaceShipList);
	bool checkSpaceShipEnemySpaceShipBulletHit(EnemySpaceShip *enemySpaceShipList, int currentEnemyBulletNumToFire);

	float centralX();
	float centralY();
	void leftMove();
	void rightMove();
	void topMove();
	void bottomMove();
	void DrawTriangle();
	void DrawTriangle(float x1,float x2, float x3,float y1, float y2, float y3);
	virtual ~SpaceShip();
};

