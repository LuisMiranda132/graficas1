#include <GL\glew.h>
#include <GL\freeglut.h>

class Enemigo{
	static int id;

public:	
	float vel;
	float x, y;
	void draw();
	void update();
	Enemigo(float xi=0,float yi=0):x(xi),y(yi),vel(0.05){};
	bool collideRight(int xa, int ya,int xb, int yb);
	bool collideLeft(int xa, int ya,int xb, int yb);
	bool collideUp(int xa, int ya,int xb, int yb);
	bool collideDown(int xa, int ya,int xb, int yb);
};