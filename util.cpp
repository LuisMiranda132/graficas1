#include"util.h"

void drawBar(){
	glBegin(GL_POLYGON);
		glVertex2f(1.5,1.0);
		glVertex2f(1.5,0.0);
		glVertex2f(-1.5,0.0);
		glVertex2f(-1.5,1.0);
	glEnd();
}

void Barrera::draw(){
		for(int i=0; i<this->bloques.size();i++){
			glPushMatrix();
			glTranslatef(
				this->bloques[i].second.first,
				this->bloques[i].second.second,
				0.0);
				drawBar();
			glPopMatrix();	
		}
}

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

