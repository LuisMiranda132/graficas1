#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>

using namespace std;

class Enemigo{
	static int id;

public:	
	float vel;
	float x, y;
	void draw();
	void update();
	Enemigo(float xi=0,float yi=0):x(xi),y(yi),vel(0.1){};
	bool collideRight(int xa, int ya,int xb, int yb);
	bool collideLeft(int xa, int ya,int xb, int yb);
	bool collideUp(int xa, int ya,int xb, int yb);
	bool collideDown(int xa, int ya,int xb, int yb);
};

class Barrera{

public:
	float x, y;
	void draw();
	Barrera(float xi=0,float yi=0):x(xi),y(yi){};
};

void drawBarrera(int x, int y);

class Bala{

public:
	static const float BULLET_RADIUS;

	float x, y;
	float radius;
	float vel;
	void draw();
	bool collideWall(float wallY);
	void update();
	Bala(float xi=0,float yi=0,float r=0):x(xi),y(yi),radius(r),vel(0.5f){};
};

class Aliado{

public:
	static const float ALLY_WIDTH;
	static const float ALLY_HEIGHT;
	static const float ALLY_MOVE_SPEED;
	static const int ALLY_LEFT;
	static const int ALLY_RIGHT;

	float x, y;
	float width,height;
	bool shot;
	float vel;
	void draw();
	void update(float wallX);
	Bala shoot();
	void onKeyPress(unsigned char key);
	void onSpecialPress(int code);
	void onKeyRelease(unsigned char key);
	void onSpecialRelease(int code);
	void collideWall(float wallX);
	void collideEnemy(Enemigo en);
	void collideBullets();
	Aliado(float xi=0,float yi=0,float w=1.0f, float h=1.0f):
		x(xi),y(yi),width(w),height(h),vel(0.0f),shot(false){};
};