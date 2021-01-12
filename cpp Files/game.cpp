//============================================================================
// Name        : Usama Zafar.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game
//============================================================================

#ifndef AsteroidS_CPP_
#define AsteroidS_CPP_
#include "Board.h"
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include"Asteroid.h"
#include "SpaceShip.h"
#include "EnemySpaceShip.h"
#include "Bullet.h"
#include "GameHeader.h"
using namespace std;

//**********************************************//
//				GLOBAL VARIABLES				//
//**********************************************//

GameHeader GH;

//**********************************************//

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)bbbbb
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

//Number of Vertices used to draw Bomberman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}



//void DrawBomberman(float sx/*center x*/, float sy/*center y*/,
//		float radius/*Radius*/,
//		const ColorNames &colorname/*Bomberman Colour*/) {
//
//	glColor3fv(colors[colorname]); // set the circle color
//	InitPMVertices(radius);
//	glBegin (GL_TRIANGLE_FAN);
//	glVertex4f(sx, sy, 0, 1);
//	for (int i = 0; i < npmvertices; ++i)
//		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
//	glEnd();
//	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
//			radius / 10, colors[BLACK]);
//}
/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// draw four asteroids

	GH.b->Draw();
	int x, y; 

	//===========================================================================================================
	GH.spaceShip.setScore(0);
	SpaceShip::displayScore = 0;

	for (int i = 0; i < ASTEROID_COUNT; i++)
	{
		if (GH.asteroidsList[i].getAlive() == false)
		{
			GH.spaceShip.setScore(GH.spaceShip.getScore() + 5);
			SpaceShip::displayScore+=10;
		}
	}
	for (int i = 0; i < ENEMY_SPACESHIP_COUNT; i++)
	{
		if (GH.enemySpaceShipList[i].getAlive() == false)
		{
			SpaceShip::displayScore += 5;
			GH.spaceShip.setScore(GH.spaceShip.getScore() + 5);
		}
	}

	if (GH.BonusScores- GH.currentTime>=1)
	{
		DrawString(GH.BonusX, GH.BonusY,   "+10",  colors[7] );
	}
	for (int i = 0; i < ASTEROID_COUNT; i++)
	{
		if (GH.collisionChk)
		{
			bool  isHitted = false;
			isHitted= GH.asteroidsList[i].checkAsteroidSpaceShipBulletHit(GH.bulletList, GH.currentBulletNumToFire);//Collision between Spaceship Bullet and Asteroid.
			if (isHitted)
			{
				GH.BonusScores += GH.currentTime;
				GH.BonusX = GH.asteroidsList[i].getX();
				GH.BonusY = GH.asteroidsList[i].getY();
				//GH.spaceShip.setScore(GH.spaceShip.getScore()+5);
				
			}
			//asteroidsList[i].checkSpaceShipBulletHit(bulletList, currentBulletNumToFire);
			//asteroidsList[i].checkAsteroidHit(bulletList, spaceShip);
		}
		if (GH.asteroidsList[i].getAlive() == true)
		{
			GH.asteroidsList[i].DrawAsteroid();
			GH.asteroidsList[i].move();
			GH.asteroidsList[i].update();
		}


	}
	for (int i = 0; i < ENEMY_SPACESHIP_COUNT; i++)
	{
		if (GH.collisionChk)
		{
			bool  isHitted = false;
			isHitted= GH.enemySpaceShipList[i].checkSpaceShipEnemySpaceShipBulletHit(GH.bulletList, GH.currentBulletNumToFire);//Collision between Spaceship Bullet and Enemy SpaceShip .
			if (isHitted)
			{
				GH.BonusScores += GH.currentTime;

			}
		}		
		if (GH.enemySpaceShipList[i].getAlive()==true)
		{
			GH.enemySpaceShipList[i].move();
			GH.enemySpaceShipList[i].DrawTriangle();
			GH.enemySpaceShipList[i].update();
			GH.enemySpaceShipList[i].drawEnemyBullet();

			if (GH.enemySpaceShipList[i].getenemyBulletFireTimer() - GH.currentTime <= 0.0)
			{
				GH.enemySpaceShipList[i].fireEnemyBullet();
				GH.enemySpaceShipList[i].setenemyBulletFireTimer(ENEMY_BULLET_FIRE_INTERVAL + GH.currentTime);//to add the time in the previous time (5 + 0)+(5 + 10).....
			}
		}
		else
		{
			GH.BonusX = GH.asteroidsList[i].getX();
			GH.BonusY = GH.asteroidsList[i].getY();
			//GH.spaceShip.setScore(GH.spaceShip.getScore() + 5);
			
		}

	}
	if (GH.spaceShip.getAlive())
	{
		for (int i = 0; i < GH.currentBulletNumToFire; i++)
		{
			if (GH.bulletList[i].getAlive() == true && GH.bulletList[i].get_isFired() == true)
			{
				GH.bulletList[i].move();
				GH.bulletList[i].update();
				GH.bulletList[i].DrawCircle();
			}
		}
	}


	if (GH.spaceShip.getLives()>0)
	{
		if (GH.spaceShip.getAlive()==true)
			{
				if (GH.collisionChk)
				{
					GH.spaceShip.checkSpaceShipAsteroidCollision(GH.asteroidsList);//Collision between Spaceship and Asteroid.
					GH.spaceShip.checkSpaceShipEnemySpaceShipCollision(GH.enemySpaceShipList);//Collision between Spaceship and Enemy spaceShip .
					GH.spaceShip.checkSpaceShipEnemySpaceShipBulletHit(GH.enemySpaceShipList,BULLET_COUNT);
								

					//spaceShip.checkSpaceShipBulletHit(bulletList, currentBulletNumToFire);
					//spaceShip.checkAsteroidHit(asteroidsList, ASTEROID_COUNT);
					//spaceShip.setLives(spaceShip.getLives()-1);

				}
				if (GH.spaceShip.getAlive())
				{
					GH.spaceShip.DrawTriangle();
				}
				else
				{
					GH.spaceShip.setLives(GH.spaceShip.getLives() - 1);
					GH.resetGame();
					GH.currentBulletNumToFire = 0;
					//collisionChk = false;
				}
				
			}
	}	
	//DrawString(560, 810, "Usama Zafar", colors[5]);
	DrawString(760, 810, "Press R to reset", colors[5]);
	DrawString(760, 780, "Press C For Collision", colors[5]);


	string temp;
	temp = Num2Str(SpaceShip::displayScore);
	DrawString(150, 810, temp, colors[5]);

	string temp2;
	temp2 = Num2Str(GH.spaceShip.getLives());
	//===========================================================================================================

	GH.b->GetInitTextPosition(x, y);
	//cout << endl <<"Text Position = "<< x << "  y= " << y << endl << flush;

	DrawString(x, y-30, "Fired Bullets=" + Num2Str(GH.currentBulletNumToFire), colors[5]);
	DrawString(x, y - 60, "Time=" + Num2Str(GH.currentTime), colors[5]);
	DrawString(x, y, "Score = ", colors[5]);
	string collStr = (GH.collisionChk == true ? "TRUE" : "FALSE");
	DrawString(x, y - 90, "Collision=" +collStr , colors[5]);
	DrawString(x + 350, y, "Lives=", colors[5]);

	int step = 20;
	int startPos = 430;
	for (int i = 0; i < GH.spaceShip.getLives(); i++)
	{
		startPos = 430;
 
		GH.spaceShip.DrawTriangle(x + startPos+step,x + startPos + step -10,x + startPos + step +10,y+20,y,y);
		step += 20;
	}

	if (GH.spaceShip.getLives()<=0)
	{
		if ((GH.blinkTimer - GH.currentTime < -2))
		{
			GH.blinkTimer = GH.blinkTimer + 2;
		}
		else
		{
			DrawString(460, 420, "GAME OVER", colors[5]);
			//blinkTimer = blinkTimer + 3;
		}
	}
	////////////////////////////////////////////////////

	if (GH.spaceShip.getScore()==20)
	{
		GH.secondInitializeAsteroid();
		GH.initEnemySpaceShip();
	}

	////////////////////////////////////////////////////
	glutSwapBuffers(); // do not modify this line..

	glutPostRedisplay();
	

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
{
	if (key== GLUT_KEY_LEFT)				/*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/
	{
		GH.spaceShip.leftMove();
	} 
	else if (key== GLUT_KEY_RIGHT )			/*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/
	{
		GH.spaceShip.rightMove();
		//spaceShip.DrawTriangle();
	} 
	else if (key== GLUT_KEY_UP)				/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/
	{
		GH.spaceShip.topMove();
	}
	else if (key== GLUT_KEY_DOWN)			/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/
	{
		GH.spaceShip.bottomMove();
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	
	 glutPostRedisplay();
	
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
	{
		//GH.b->score += 5;
		GH.bulletList[GH.currentBulletNumToFire].setX(GH.spaceShip.getX1());
		GH.bulletList[GH.currentBulletNumToFire].setY(GH.spaceShip.getY1());
		GH.bulletList[GH.currentBulletNumToFire].setTheta(Deg2Rad(GH.spaceShip.getTheta()));
		GH.bulletList[GH.currentBulletNumToFire].set_isFired(true);
		if (GH.currentBulletNumToFire>= BULLET_COUNT-1)
		{
			for (int i = 0; i <BULLET_COUNT ; i++)
			{
				GH.bulletList[i].setAlive(true);
			}
			GH.currentBulletNumToFire=0;
		}
		else
		{
			GH.currentBulletNumToFire++;
		}		

	}
	if (key == 'c' || key == 'C')
	{
		GH.collisionChk = !GH.collisionChk;
	}
	if (key == 'd' || key == 'D')
	{
		GH.spaceShip.setLives(GH.spaceShip.getLives()-1);
	}
	if (key == 'r' || key == 'R')
	{
		GH.resetGame();
		GH.currentBulletNumToFire = 0;
		GH.collisionChk = false;
	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	GH.currentTime++;

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}



/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	GH.b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	GH.b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Osama's Asteroids"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...


	//=====================================================//
	
	GH.resetGame();
	GH.blinkTimer = 2 + GH.currentTime;
	//=====================================================//


	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
