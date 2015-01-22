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

//#####################################################################
//###########################  BARRERA  ###############################
//#####################################################################
void Barrera::draw(){

		for(int i=0; i<this->bloques.size();i++){
			if(this->bloques[i].first){
				glPushMatrix();
				glColor3f(i*0.1,i*0.1,i*0.1);
				glTranslatef(
					this->bloques[i].second.first,
					this->bloques[i].second.second,
					0.0);
					drawBar();
				glPopMatrix();	
			}	
		}
}


void Barrera::collide(Enemigo enemy){
	for(int i=0; i<this->bloques.size();i++){
		if( enemy.collideRight(
				this->bloques[i].second.first-1.5,
				this->bloques[i].second.second+1.0,
				this->bloques[i].second.first-1.5,
				this->bloques[i].second.second)||
			enemy.collideDown(
				this->bloques[i].second.first+1.5,
				this->bloques[i].second.second+1.0,
				this->bloques[i].second.first-1.5,
				this->bloques[i].second.second+1.0)||
			enemy.collideLeft(
				this->bloques[i].second.first+1.5,
				this->bloques[i].second.second+1.0,
				this->bloques[i].second.first+1.5,
				this->bloques[i].second.second)){
			bloques[i].first = false;
		}
	}
}

//#####################################################################
//###########################  ENEMIGO  ###############################
//#####################################################################

void Enemigo::draw(){
	glPushMatrix();
	glTranslatef(this->x,this->y,0.0);
		glBegin(GL_POLYGON);
			if(this->especial)
				glColor3f(0.53,0.40,0.80);
			else
				glColor3f(1,0.6,0.07);		
			glVertex2f(2.0,1.0);
			glVertex2f(2.0,-1.0);
			glVertex2f(-2.0,-1.0);
			glVertex2f(-2.0,1.0);
		glEnd();
	glPopMatrix();
	glColor3b(1.0,1.0,1.0);
}

void Enemigo::update(){
	this->x+=this->vel;
}

bool Enemigo::collideRight(float xa, float ya, float xb, float yb){
//	float mod,mab,yod,yab, interx, intery;
	float xo = x + 2, yo = y + 1,
		xd = x + 2, yd = y - 1;

	if(dist(xa,ya,xb,yb)<dist(xo,yo,xd,yd)){
		//cout << xo << " >= " << xa << "\t4 >" << abs(xo-xa) << endl;
		return (xo >= xa) && 4>abs(xo-xa) ? 
			abs(yo-ya)<abs(yo-yd) : FALSE;
	}else{
		cout<<xo<<" >= "<<xa<<endl;
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
	if(dist(xa,ya,xb,yb)<dist(xo,yo,xd,yd)){
		return (xo <= xa) && 4>abs(xo-xa) ? abs(yo-ya)<abs(yo-yd) : FALSE;
	}else{
		return (xo <= xa) ? abs(yo-ya)<abs(yb-ya) : FALSE;
	}

/*	mod = (yo-yd)/(xo-xd);
	mab = (ya-yb)/(xa-xb);

	yod = yo-xo*mod;
	yab = ya-xa*mod;

	interx = (yod-yab)/(mod - mab);
	intery = (yod - (mod * yab)/mab)/(1-mod/mab);

	return interx<=xo;
<<<<<<< HEAD
*/
}

bool Enemigo::collideDown(float xa, float ya,float xb, float yb){
//	float mod,mab,yod,yab, interx, intery;
	float xo = x + 2, yo = y - 1,
		xd = x - 2, yd = y - 1;

	if(dist(xa,ya,xb,yb)<dist(xo,yo,xd,yd)){
		return (yo <= ya && 2>abs(ya-yo)) ? abs(xa-xo)<abs(xo-xd) : FALSE;
	}else{
		return (yo <= ya) ? abs(xa-xo)<abs(xa-xb) : FALSE;
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
