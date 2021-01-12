#pragma once
#include "Board.h"
#include "util.h"
#include"Asteroid.h"
#include "SpaceShip.h"
#include "EnemySpaceShip.h"
#include "Bullet.h"
class GameHeader
{
public:
	
	//**********************************************//
	//				GLOBAL VARIABLES				//
	//**********************************************//

	int currentBulletNumToFire = 0;
	Board *b;
	Asteroid asteroidsList[ASTEROID_COUNT];
	SpaceShip spaceShip;
	Bullet bulletList[BULLET_COUNT];
	EnemySpaceShip enemySpaceShipList[ENEMY_SPACESHIP_COUNT];

	double currentTime = 0;
	bool collisionChk = false;
	double blinkTimer = 0;


	int BonusX = 0;
	int BonusY = 0;

	int BonusScores = 1;


	//**********************************************//
	//				GLOBAL FUNCTIONS				//
	//**********************************************//
	void secondInitializeAsteroid();
	void initAsteroids();
	void initBullet();
	void initSpaceShip();
	void initEnemySpaceShip();
	void resetGame();

	GameHeader();
	~GameHeader();
};

