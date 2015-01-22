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
	void draw();
	void update();
	Enemigo(float xi=0,float yi=0):x(xi),y(yi),vel(0.1){};
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
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi-3.75,yi-3.0)
			));
		bloques.push_back(
			pair< bool , pair<float, float> >::pair(
			TRUE,
			pair< float, float >::pair(xi+3.75,yi-3.0)
			));
	};

	void collide(Enemigo enemy);
};

void drawBarrera(int x, int y);