#include "GameHeader.h"



GameHeader::GameHeader()
{
}
void GameHeader::secondInitializeAsteroid()
{
	int x, y, cIndex, t;
	ColorNames c;
	for (int i = 0;i<ASTEROID_COUNT - 2;i++)
	{
	y = 0;
	b->GetInitRandomTheta(x);//extra
	//b->GetInitRandomPosition(x, y);
	b->GetInitRandomColor(cIndex);
	b->GetInitRandomTheta(t);
	asteroidsList[i].setX(x);
	asteroidsList[i].setY(y);
	c = (ColorNames)cIndex;
	asteroidsList[i].setColor(c);
	asteroidsList[i].setAlive(true);
	asteroidsList[i].setCorners(6);
	asteroidsList[i].setTheta(t);
	asteroidsList[i].setStep(ASTEROID_MOVE_STEP);
	if (i<4)
	{
		asteroidsList[i].setRadius(0.8 * b->GetCellSize());
	}
	else
	{
		asteroidsList[i].setRadius(0.5 * b->GetCellSize());
	}
}
}
void GameHeader::initAsteroids()
{
	int x, y, cIndex, t;
	ColorNames c;
	for (int i = 0;i<ASTEROID_COUNT - 2;i++)
	{
		b->GetInitRandomPosition(x, y);
		b->GetInitRandomColor(cIndex);
		b->GetInitRandomTheta(t);
		asteroidsList[i].setX(x);
		asteroidsList[i].setY(y);
		c = (ColorNames)cIndex;
		asteroidsList[i].setColor(c);
		asteroidsList[i].setAlive(true);
		asteroidsList[i].setCorners(6);
		asteroidsList[i].setTheta(t);
		asteroidsList[i].setStep(ASTEROID_MOVE_STEP);
		if (i<4)
		{
			asteroidsList[i].setRadius(0.8 * b->GetCellSize());
		}
		else
		{
			asteroidsList[i].setRadius(0.5 * b->GetCellSize());
		}
	}
}


void GameHeader::initBullet()
{
	for (int i = 0;i < BULLET_COUNT;i++)
	{
		bulletList[i].setRadius(10);
		bulletList[i].setX(spaceShip.getX1());
		bulletList[i].setY(spaceShip.getY1());
		bulletList[i].setColor(RED);
		bulletList[i].setAlive(true);
		bulletList[i].set_isFired(false);
		bulletList[i].setTheta(45);
		bulletList[i].setStep(BULLET_MOVE_STEP);
	}

}

void GameHeader::initSpaceShip()
{
	int x1, y1, x2, y2, x3, y3, cIndex, t;
	ColorNames c;
	x1 = 520;
	y1 = 420;
	x2 = 470;
	y2 = 370;
	x3 = 570;
	y3 = 370;

	//b->GetInitRandomTheta(0);

	spaceShip.setX1(x1);
	spaceShip.setY1(y1);
	spaceShip.setX2(x2);
	spaceShip.setY2(y2);
	spaceShip.setX3(x3);
	spaceShip.setY3(y3);

	spaceShip.setColor(RED);
	spaceShip.setAlive(true);

	spaceShip.setTheta(90);
	spaceShip.setStep(SPACESHIP_MOVE_STEP);

}

void GameHeader::initEnemySpaceShip()
{
	int x1, y1, x2, y2, x3, y3, cIndex, t;
	ColorNames c;
	for (int i = 0;i<ENEMY_SPACESHIP_COUNT;i++)
	{
		b->GetInitRandomPosition(x1, y1);
		//b->GetInitRandomPosition(x2, y2);
		//b->GetInitRandomPosition(x3, y3);
		b->GetInitRandomColor(cIndex);
		b->GetInitRandomTheta(t);
		enemySpaceShipList[i].setX1(x1);
		enemySpaceShipList[i].setY1(y1);
		enemySpaceShipList[i].setX2(x1 + 30);
		enemySpaceShipList[i].setY2(y1 - 30);
		enemySpaceShipList[i].setX3(x1 - 30);
		enemySpaceShipList[i].setY3(y1 - 30);
		c = (ColorNames)cIndex;
		enemySpaceShipList[i].setColor(c);
		enemySpaceShipList[i].setAlive(true);
		//spaceShipList[i].setCorners(6);
		enemySpaceShipList[i].setTheta(t);
		enemySpaceShipList[i].setStep(ENEMY_SPACESHIP_COUNT);

		enemySpaceShipList[i].initEnemyBullet();

	}
}

void GameHeader::resetGame()
{
	initAsteroids();
	initSpaceShip();
	initEnemySpaceShip();
	initBullet();
}
GameHeader::~GameHeader()
{
}
