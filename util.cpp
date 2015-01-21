#include"util.h"
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

void Aliado::collideWall(float wallX){
	if(this->x >= wallX)
		this->x = wallX;
	else if(this->x <= -wallX)
		this->x = -wallX;
}