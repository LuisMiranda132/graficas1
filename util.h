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
	float x, y;
	float vel;
	void draw();
	void update();
	Bala(float xi=0,float yi=0):x(xi),y(yi),vel(0.5f){};
};

class Aliado{

public:
	static const float ALLY_WIDTH;
	static const float ALLY_HEIGHT;

	float x, y;
	float vel;
	vector<Enemigo>* enemyList;
	vector<Bala>* bulletList;
	void draw();
	void update(float wallX);
	void onKeyPress(unsigned char key);
	void onKeyRelease(unsigned char key);
	void collideWall(float wallX);
	bool collideEnemy();
	bool collideBullets();
	Aliado(vector<Enemigo>* e, vector<Bala>* b,float xi=0,float yi=0):x(xi),y(yi),vel(1.0f),enemyList(e), bulletList(b){};
	Aliado(){};
};