#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

class Enemigo{
	static int id;

public:	
	float vel;
	float x, y;
	bool especial;
	void draw();
	void update();
	Enemigo(float xi=0,float yi=0,bool e=0)
		:x(xi),y(yi),vel(0.5),especial(e){};
	bool collideRight(float xa, float ya,float xb, float yb);
	bool collideLeft(float xa, float ya,float xb, float yb);
	bool collideUp(float xa, float ya,float xb, float yb);
	bool collideDown(float xa, float ya,float xb, float yb);
};

class Barrera{

public:
	float x, y;
	vector <pair< bool , pair<float, float> >> bloques;
	
	void draw();
	Barrera(float xi=0,float yi=0):x(xi),y(yi){
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi-1.75,yi)
			));
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi+1.75,yi)
			));
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi-3.5,yi-1.5)
			));
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi+3.5,yi-1.5)
			));
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi-1.75,yi-3.0)
			));
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi+1.75,yi-3.0)
			));
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
