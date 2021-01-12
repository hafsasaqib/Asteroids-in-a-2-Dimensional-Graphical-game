#include "Asteroid.h"
#include "util.h"


#define TOP		1
#define RIGHT	2
#define BOTTOM	3
#define LEFT	4



Asteroid::Asteroid()
{
	Color= PINK;
	X=Y=0;
	Radius=48;
	Corners=6;
	Alive=false; 
	theta = 45;
	step = 10;
	
}
Asteroid::Asteroid(ColorNames c, int x, int y, int r, int co, bool a)
{
	setAsteroid(c, x, y, r, co, a);
}
void Asteroid::setAsteroid(ColorNames c, int x, int y, int r,int co,bool a)
{
	Color = c;
	X = x;
	Y = y;
	Radius = r;
	Corners = co;
	Alive =a;
}

void Asteroid::DrawAsteroid()
{
	int ogr = 6, ogh = 7;

	glPushMatrix();
	float sx = (float)Radius / ogr;
	//glTranslatef(x, y, 1);
	//glScalef(sx, 1, 1);

	// Draw Asteroid here
	//DrawLine();
	const int nvertices = 722;
	GLfloat vertices[nvertices][2];
	float hdegree = M_PI / (Corners / 2);
	float angle = 0;
	for (int i = 0; i < nvertices; ++i) {
		vertices[i][0] = Radius * cos(angle);
		vertices[i][1] = Radius * sin(angle);
		angle += hdegree;
	}

	glColor3fv(colors[Color]); // set the circle color
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(X, Y, 0, 1);
	for (int i = 0; i < nvertices; ++i)
		glVertex4f(X + vertices[i][0], Y + vertices[i][1], 0, 1);
	glEnd();
	//cout << "X :" << X << "Y :" << Y << endl;
	glPopMatrix();
}

void Asteroid::update()
{
	//cout << "X :" << X << "Y :" << Y<<endl;
	Point pt(X,Y), v1(0,WINDOW_HEIGHT), v2(WINDOW_WIDTH,0), v3(WINDOW_WIDTH, WINDOW_HEIGHT);
	bool inOne = PointInTriangle( pt,  v1,  v2,  v3);
	if (inOne)
	{
		//cout << "point inside trriangle one";
	}
	else
	{
		//cout << "point not inside trriangle one" << endl;
		pt.setPoint(X, Y), v1.setPoint(0, WINDOW_HEIGHT), v2.setPoint(WINDOW_WIDTH, 0), v3.setPoint(0, 0);
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

float Asteroid::sign(Point p1, Point p2, Point p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Asteroid::PointInTriangle(Point pt, Point v1, Point v2, Point v3)
{
	bool b1, b2, b3;

	b1 = sign(pt, v1, v2) < 0.0f;
	b2 = sign(pt, v2, v3) < 0.0f;
	b3 = sign(pt, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}
void Asteroid::setInitSide()
{
	int s;//for side
	s = GetRandInRange(1, 4);
	if (s==TOP)
	{
		X= GetRandInRange(0, WINDOW_WIDTH);
		Y = 0;
		theta= GetRandInRange(180, 360);
	}
	else if (s == RIGHT)
	{
		X = WINDOW_WIDTH;
		Y = GetRandInRange(0, WINDOW_HEIGHT);
		theta= GetRandInRange(90, 270);
	}
	else if (s == BOTTOM)
	{
		X = GetRandInRange(0, WINDOW_WIDTH);
		Y = WINDOW_HEIGHT;
		theta= GetRandInRange(0, 180);
	}
	else if (s == LEFT)
	{
		X = 0;
		Y = GetRandInRange(0, WINDOW_HEIGHT);
		theta= GetRandInRange(270, 450);
		theta > 360 ? theta - 360 : theta;	//checking for theta in [270,360] OR [0,90]
	}
}
void Asteroid::move()
{

	X=X+ step*cos(theta);
	Y=Y+ step*sin(theta);
}
void Asteroid::rotateRight()
{
	
}
void Asteroid::rotateLeft()
{

}
bool Asteroid::checkAsteroidSpaceShipBulletHit(Bullet *bulletList, int currentBulletNumToFire)
{
	bool isHit = false;
	Point pt1, pt2;
	float r1,r2;
	for (int i = 0; i < currentBulletNumToFire; i++)
	{
		if (bulletList[i].getAlive() == true && bulletList[i].get_isFired() == true)
		{
			pt1.x = this->getX();
			pt1.y = this->getY();
			pt2.x = bulletList[i].getX();
			pt2.y = bulletList[i].getY();
			r2 = 48;
			r1 = 5;
			isHit = C.isCircleCollision(pt1, pt2, r1,r2);
			if (isHit == true)
			{
				this->Alive = false;
				
				return isHit;
			}
		}

	}
	return isHit;
}
Asteroid::~Asteroid()
{
}
