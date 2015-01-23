#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

class Bala;
class Bloque;
class Barrera;
class Enemigo;
class Aliado;

class Bloque{

public:
	float x,y;
	float width;
	float height;
	bool toRemove;

	void draw();
	bool collideBullet(Bala &bala);
	Bloque(float xi=0,float yi=0,float w=3.0f,float h=0.5f):x(xi),y(yi),width(w),height(h),toRemove(false){};
};

class Enemigo{
	static int id;

public:	
	float vel;
	float x, y;
	bool especial,toRemove;
	void draw();
	void update();
	Enemigo(float xi=0,float yi=0,bool e=0)
		:x(xi),y(yi),vel(0.5),especial(e),toRemove(false){};
	bool collideWall(float wallX);
	void goDown();
	bool collideBlock(Bloque b);
	bool collideRight(float xa, float ya,float xb, float yb);
	bool collideLeft(float xa, float ya,float xb, float yb);
	bool collideUp(float xa, float ya,float xb, float yb);
	bool collideDown(float xa, float ya,float xb, float yb);
};

class Bala{

public:
	static const float BULLET_RADIUS;

	float x, y;
	float radius;
	float vel;
	bool toRemove;
	void draw();
	bool collideWall(float wallY);
	bool collideEnemy(Enemigo en);
	void update();
	Bala(float xi=0,float yi=0,float r=0):x(xi),y(yi),radius(r),vel(0.5f),toRemove(false){};
};

class Barrera{

public:
	float x, y;
	vector <Bloque> bloques;
	
	void draw();
	Barrera(float xi=0,float yi=0):x(xi),y(yi){
		bloques.push_back(Bloque::Bloque(xi-1.75,yi));
		bloques.push_back(Bloque::Bloque(xi+1.75,yi));
		bloques.push_back(Bloque::Bloque(xi-3.5,yi-1.5));
		bloques.push_back(Bloque::Bloque(xi+3.5,yi-1.5));
		bloques.push_back(Bloque::Bloque(xi-1.75,yi-3.0));
		bloques.push_back(Bloque::Bloque(xi+1.75,yi-3.0));
/*		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi-5,yi-3.0)
			));
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi+5,yi-3.0)
			));
*/
	};

	void collide(Enemigo enemy);
};

void drawBarrera(int x, int y);


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
	bool collideEnemy(Enemigo en);
	void collideBullets();
	Aliado(float xi=0,float yi=0,float w=1.0f, float h=1.0f):
		x(xi),y(yi),width(w),height(h),vel(0.0f),shot(false){};
};
