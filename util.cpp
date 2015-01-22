#include"util.h"
#define dist(x1,y1,x2,y2) sqrt( pow(x1-x2,2) + pow(y1-y2,2))

bool elcollide(float xo, float yo, float xd, float yd,
			 float xa, float ya, float xb, float yb){

	float mod,mab,yod,yab, interx, intery;
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

void Barrera::collide(Enemigo enemy){
//	for(int i=0; i<this->bloques.size();i++){
		cout<<
			elcollide(enemy.x + 2, enemy.y + 1,
				enemy.x - 2, enemy.y + 1,
				this->bloques[0].second.first + 1.5,
				this->bloques[0].second.second + 1.0,
				this->bloques[0].second.first + 1.5,
				this->bloques[0].second.second)
			<< endl;
//	}
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

bool Enemigo::collideRight(float xa, float ya, float xb, float yb){
//	float mod,mab,yod,yab, interx, intery;
	float xo = x + 2, yo = y + 1,
		xd = x + 2, yd = y - 1;

	if(xa==xb){
		cout << xo <<","<< yo <<"\t"<<xa<<","<<ya<<endl;
		return (xo >= xa) ? abs(yo-ya)<abs(yb-ya) : FALSE;
	}

/*	mod = (yo-yd)/(xo-xd);
	mab = (ya-yb)/(xa-xb);

	yod = yo-xo*mod;
	yab = ya-xa*mod;

	interx = (yod-yab)/(mod - mab);
	intery = (yod - (mod * yab)/mab)/(1-mod/mab);

	return interx<=xo;
*/
}

bool Enemigo::collideLeft(float xa, float ya,float xb, float yb){
//	float mod,mab,yod,yab, interx, intery;
	float xo = x - 2, yo = y + 1,
		xd = x - 2, yd = y - 1;

	if(xa==xb){
		return (xo <= xa) ? abs(yo-ya)<abs(yb-ya) : FALSE;
	}

/*	mod = (yo-yd)/(xo-xd);
	mab = (ya-yb)/(xa-xb);

	yod = yo-xo*mod;
	yab = ya-xa*mod;

	interx = (yod-yab)/(mod - mab);
	intery = (yod - (mod * yab)/mab)/(1-mod/mab);

	return interx<=xo;
*/
}
