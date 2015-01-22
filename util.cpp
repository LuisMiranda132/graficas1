#include"util.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265
#define CIRCLE_SEGMENT_LENGTH 0.05

//#####################################################################
//############################  UTIL  #################################
//#####################################################################

float toDegrees(float r){
	return r*PI/180.0;
}

void renderCircle(float r,float cx,float cy){
	glPushMatrix();
		glTranslatef(cx,cy,0.0f);
		glBegin(GL_POLYGON);
		for(float i=0.0f;i<1.0f;i+=CIRCLE_SEGMENT_LENGTH){
			glVertex2f(r*cos(toDegrees(360.0*i)),r*sin(toDegrees(360.0*i)));
			glVertex2f(r*cos(toDegrees(360.0*(i+CIRCLE_SEGMENT_LENGTH))),r*sin(toDegrees(360.0*(i+CIRCLE_SEGMENT_LENGTH))));
		}
		glEnd();
	glPopMatrix();
}

//#####################################################################
//###########################  BARRERA  ###############################
//#####################################################################
void Barrera::draw(){
	glPushMatrix();
		glTranslatef(this->x,this->y,0.0);
		glPushMatrix();
			glTranslatef(-1.75,0.0,0.0);
			glBegin(GL_POLYGON);
				glVertex2f(1.5,1.0);
				glVertex2f(1.5,0.0);
				glVertex2f(-1.5,0.0);
				glVertex2f(-1.5,1.0);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.75,0.0,0.0);
			glBegin(GL_POLYGON);
				glVertex2f(1.5,1.0);
				glVertex2f(1.5,0.0);
				glVertex2f(-1.5,0.0);
				glVertex2f(-1.5,1.0);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.0,-1.5,0.0);
			glPushMatrix();
				glTranslatef(3.5,0.0,0.0);
				glBegin(GL_POLYGON);
					glVertex2f(1.5,1.0);
					glVertex2f(1.5,0.0);
					glVertex2f(-1.5,0.0);
					glVertex2f(-1.5,1.0);
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-3.5,0.0,0.0);
				glBegin(GL_POLYGON);
					glVertex2f(1.5,1.0);
					glVertex2f(1.5,0.0);
					glVertex2f(-1.5,0.0);
					glVertex2f(-1.5,1.0);
				glEnd();
			glPopMatrix();
			glTranslatef(0.0,-1.5,0.0);
			glPushMatrix();
				glTranslatef(-1.75,0.0,0.0);
				glBegin(GL_POLYGON);
					glVertex2f(1.5,1.0);
					glVertex2f(1.5,0.0);
					glVertex2f(-1.5,0.0);
					glVertex2f(-1.5,1.0);
				glEnd();
				glTranslatef(-3.75,0.0,0.0);
				glBegin(GL_POLYGON);
					glVertex2f(1.5,1.0);
					glVertex2f(1.5,0.0);
					glVertex2f(-1.5,0.0);
					glVertex2f(-1.5,1.0);
				glEnd();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(1.75,0.0,0.0);
				glBegin(GL_POLYGON);
					glVertex2f(1.5,1.0);
					glVertex2f(1.5,0.0);
					glVertex2f(-1.5,0.0);
					glVertex2f(-1.5,1.0);
				glEnd();
				glTranslatef(3.75,0.0,0.0);
				glBegin(GL_POLYGON);
					glVertex2f(1.5,1.0);
					glVertex2f(1.5,0.0);
					glVertex2f(-1.5,0.0);
					glVertex2f(-1.5,1.0);
				glEnd();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

//#####################################################################
//###########################  ENEMIGO  ###############################
//#####################################################################

void Enemigo::draw(){
	glPushMatrix();
	glTranslatef(this->x,this->y,0.0);
		glBegin(GL_POLYGON);
			glVertex2f(2.0,1.0);
			glVertex2f(2.0,-1.0);
			glVertex2f(-2.0,-1.0);
			glVertex2f(-2.0,1.0);
		glEnd();
	glPopMatrix();
}

void Enemigo::update(){
	this->x+=this->vel;
}

bool Enemigo::collideRight(int xa, int ya,int xb, int yb){
	float mod,mab,yod,yab, interx, intery;
	int xo = x + 2, yo = y+1,
		xd = x - 2, yd = y+1;

	if(xa==xb)
		return xo>=xa;

	mod = (yo-yd)/(xo-xd);
	mab = (ya-yb)/(xa-xb);

	yod = yo-xo*mod;
	yab = ya-xa*mod;

	interx = (yod-yab)/(mod - mab);
	intery = (yod - (mod * yab)/mab)/(1-mod/mab);

	return interx<=xo;
}

bool Enemigo::collideLeft(int xa, int ya,int xb, int yb){
	float mod,mab,yod,yab, interx, intery;
	int xo = x - 2, yo = y+1,
		xd = x - 2, yd = y+1;
	if(xa==xb)
		return xo<=xa;

	mod = (yo-yd)/(xo-xd);
	mab = (ya-yb)/(xa-xb);

	yod = yo-xo*mod;
	yab = ya-xa*mod;

	interx = (yod-yab)/(mod - mab);
	intery = (yod - (mod * yab)/mab)/(1-mod/mab);

	return interx<=xo;
}

//#####################################################################
//###########################  ALIADO  ################################
//#####################################################################

const float Aliado::ALLY_WIDTH = 4.0f;
const float Aliado::ALLY_HEIGHT = 2.0f;
const float Aliado::ALLY_MOVE_SPEED = 1.0f;
const int Aliado::ALLY_LEFT = 0;
const int Aliado::ALLY_RIGHT = 1;

void Aliado::draw(){
	float hw = ALLY_WIDTH/2.0f;
	float hh = ALLY_HEIGHT/2.0f;
	glPushMatrix();
		glTranslatef(this->x,this->y,0.0f);
		glBegin(GL_POLYGON);
			glVertex2f(hw,hh);
			glVertex2f(-hw,hh);
			glVertex2f(-hw,-hh);
			glVertex2f(hw,-hh);
		glEnd();
	glPopMatrix();
}

void Aliado::update(float wallX){
	this->x+=this->vel;
	this->collideWall(wallX);
}

Bala Aliado::shoot(){
	this->shot = true;
	return Bala::Bala(this->x,this->y,Bala::BULLET_RADIUS);
}

void Aliado::onSpecialPress(int code){
	switch(code){
		case ALLY_LEFT: this->vel = -ALLY_MOVE_SPEED;break;
		case ALLY_RIGHT: this->vel = ALLY_MOVE_SPEED;break;
		default:break;
	}
}

void Aliado::onSpecialRelease(int code){
	switch(code){
		case 0: this->vel = 0.0f;break;
		case 1: this->vel = 0.0f;break;
		default:break;
	}
}

void Aliado::collideWall(float wallX){
	float halfWidth = this->width/2.0f;
	if(this->x + halfWidth >= wallX)
		this->x = wallX-halfWidth;
	else if(this->x - halfWidth <= -wallX)
		this->x = -wallX+halfWidth;
}

void Aliado::collideEnemy(Enemigo en){
	float enemyLeft = en.x - 2.0f;
	float enemyRight = en.x + 2.0f;
	float enemyUp = en.y + 1.0f;
	float enemyDown = en.y - 1.0f;

	float halfWidth = this->width/2.0f;
	float halfHeight = this->height/2.0f;
	float myLeft = this->x - halfWidth;
	float myRight = this->x + halfWidth;
	float myUp = this->y + halfHeight;
	float myDown = this->y - halfHeight;

	if(myLeft <= enemyRight && myRight >= enemyLeft && myUp >= enemyDown && myDown <= enemyUp)
		cout << "Collided with enemy" << endl;
}

//#####################################################################
//############################  BALA  #################################
//#####################################################################

const float Bala::BULLET_RADIUS = 0.5f;

void Bala::draw(){
	renderCircle(this->radius,this->x,this->y);
}

bool Bala::collideWall(float wallY){
	float myUp = this->y + this->radius;
	if(myUp >= wallY)
		return true;
	else
		return false;
}

void Bala::update(){
	this->y += this->vel;
}
		