#include "Bullet.h"



Bullet::Bullet()
{
	Color = RED;
	X=0;
	Y=0;
	Radius=0;
	theta=0;
	step=10;
	Alive=true;
	isFired = false;
}
Bullet::Bullet(ColorNames c, int x, int y, int r, float t, bool a, bool f)
{
	setBullet(c, x, y, r, t, a,f);
}
void Bullet::setBullet(ColorNames c, int x, int y, int r, float t, bool a, bool f)
{
	Color = c;
	X = x;
	Y = y;
	theta = t;
	Radius = r;
	//corners = co;
	Alive = a;
	isFired = f;
}
const int nvertices = 722;
GLfloat vertices[nvertices][2];
void InitCircleVertices(float Radius) {

	float hdegree = M_PI / 360.0;
	float angle = 0;
	for (int i = 0; i < nvertices; ++i) {
		vertices[i][0] = Radius * cos(angle);
		vertices[i][1] = Radius * sin(angle);
		angle += hdegree;
	}
}
void Bullet::DrawCircle() {
	glColor3fv(colors[Color]); // set the circle color
	InitCircleVertices(Radius);
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(X, Y, 0, 1);
	for (int i = 0; i < nvertices; ++i)
		glVertex4f(X + vertices[i][0], Y + vertices[i][1], 0, 1);
	glEnd();
}
void Bullet::move()
{
	X = X + step*cos(theta);
	Y = Y + step*sin(theta);
}
void Bullet::leftMove()
{
	X -= 5;
}
void Bullet::rightMove()
{
	X += 5;
}
void Bullet::topMove()
{
	Y += 5;
}
void Bullet::bottomMove()
{
	Y -= 5;
}


float Bullet::sign(Point p1, Point p2, Point p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Bullet::PointInTriangle(Point pt, Point v1, Point v2, Point v3)
{
	bool b1, b2, b3;

	b1 = sign(pt, v1, v2) < 0.0f;
	b2 = sign(pt, v2, v3) < 0.0f;
	b3 = sign(pt, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

void Bullet::update()
{
	Point pt(X, Y), v1(0, WINDOW_HEIGHT), v2(WINDOW_WIDTH, 0), v3(WINDOW_WIDTH, WINDOW_HEIGHT);
	bool inOne = PointInTriangle(pt, v1, v2, v3);
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
			Alive = false;
			isFired = false;
		}
	}
}

Bullet::~Bullet()
{
}
