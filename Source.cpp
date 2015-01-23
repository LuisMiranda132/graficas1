#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "util.h"

using namespace std;

#define DEF_floorGridScale	1.0f
//#define DEF_floorGridXSteps	20.0f
//#define DEF_floorGridZSteps	20.0f
#define DEF_floorGridXSteps	40.0f
#define DEF_floorGridZSteps	40.0f

#define WALL_WIDTH 25.0f
#define SECRET_WALL 30.0f
#define WALL_HEIGHT 30.0f
#define ALLY_OFFSET 3.0f
#define ENEMY_RELOAD_TIME 1
#define SECRET_SHIP_TIME 3
#define SECRET_SHIP_Y 27.0f
#define SECRET_SHIP_X -23.0f
#define SCORE_X 40.0f
#define SCORE_Y 0.0f
#define SCORE_OFFSET 15

#define morados 2
#define numEne 6
#define niveles 2

random_device rd;
mt19937 eng(rd());
uniform_int_distribution<int> dist(0,1);

int delay = 50;

vector<Enemigo> enemigos;
vector<Enemigo> enemigosSecretos;
vector<Barrera> barreras;
vector<Bala> balasEnemigas;
vector<Bala> balasAliadas;
Aliado ally;
int score = 0;
bool play = true;

void drawNumber(int n,float x, float y){
	glPushMatrix();
	glTranslatef(x,y,0.0f);
	glScalef(0.03,0.03,0.03);
	glutStrokeCharacter(GLUT_STROKE_ROMAN,n+48);
	glPopMatrix();
}

void drawScore(float x, float y){
	if(score == 0){
		drawNumber(0,x,y);
	}else if(score > 0){
		int a = score;
		int i = 0;
		while(a !=0){
			drawNumber(a%10,x+i*SCORE_OFFSET,y);
			a /= 10;
			++i;
		}
	}
}

bool toRemoveEnemy(Enemigo &en){
	return en.toRemove;
}

bool toRemoveBala(Bala &bal){
	return bal.toRemove;
}

bool toRemoveBloque(Bloque &blo){
	return blo.toRemove;
}

void collideWorld(){
	bool down = false;
	for(int j=0; j<enemigos.size(); j++){
		if(enemigos[j].collideWall(WALL_WIDTH)){
			down = true;
		}else if(ally.collideEnemy(enemigos[j])){
			play = false;	
		}
	}
	if(down){
		for(int i=0;i<enemigos.size();++i){
			enemigos[i].goDown();
		}
	}
}

void collideBarrera(){
	for(int i=0;i<barreras.size();++i){
		for(int j=0;j<barreras[i].bloques.size();++j){
			for(int k=0;k<balasAliadas.size();++k){
				if(barreras[i].bloques[j].collideBullet(balasAliadas[k])){
					barreras[i].bloques[j].toRemove = true;
					balasAliadas[k].toRemove = true;
					score -= 30;
				}
			}
			balasAliadas.erase(remove_if(balasAliadas.begin(),balasAliadas.end(),toRemoveBala),balasAliadas.end());
			for(int k=0;k<balasEnemigas.size();++k){
				if(barreras[i].bloques[j].collideBullet(balasEnemigas[k])){
					barreras[i].bloques[j].toRemove = true;
					balasEnemigas[k].toRemove = true;
				}
			}
			balasEnemigas.erase(remove_if(balasEnemigas.begin(),balasEnemigas.end(),toRemoveBala),balasEnemigas.end());
		}
		barreras[i].bloques.erase(remove_if(barreras[i].bloques.begin(),barreras[i].bloques.end(),toRemoveBloque),barreras[i].bloques.end());
	}
}

void cargarEnemigos(){
	int dummy,mor=morados;
	for(int j=0; j<niveles; j++){
		for(int i =0; i<numEne;i++){
			dummy=dist(eng);
			if(mor&&dummy){
				enemigos.push_back(
					Enemigo::Enemigo(
					-20.0+6.0*i+(j % 2)*3,24-5*j,dummy));
				mor--;
			}else{
				enemigos.push_back(
					Enemigo::Enemigo(
					-20.0+6.0*i+(j % 2)*3,24-5*j));
			}
		}
	}
}

void cargarBarreras(){
	barreras.push_back(Barrera::Barrera(-16.0,-16.0));
	barreras.push_back(Barrera::Barrera(0.0,-16.0));
	barreras.push_back(Barrera::Barrera(16.0,-16.0));
}

void cargarAliado(){
	ally = Aliado::Aliado(-WALL_WIDTH+Aliado::ALLY_WIDTH/2.0f+2.0f,-WALL_HEIGHT+Aliado::ALLY_HEIGHT/2.0f + ALLY_OFFSET,Aliado::ALLY_WIDTH,Aliado::ALLY_HEIGHT);
}

void updateEnemigos(){
	for(int j=0; j<enemigos.size(); j++)
		enemigos[j].update();

	for(int j=0; j<enemigosSecretos.size(); j++)
		enemigosSecretos[j].update();

	for(int k=0; k<enemigos.size(); ++k){
		for(int j=0;j<balasAliadas.size();++j){
			Bala* b = &(balasAliadas[j]);
			if(b->collideEnemy(enemigos[k])){
				if(enemigos[k].especial){
					enemigos[k].especial = false;
					score += 100;
				}else{
					enemigos[k].toRemove = true;
				}
				balasAliadas[j].toRemove = true;
				score+=100;
			}
		}
		balasAliadas.erase(remove_if(balasAliadas.begin(),balasAliadas.end(),toRemoveBala),balasAliadas.end());
		for(int j=0;j<barreras.size();++j){
			for(int i=0;i<barreras[j].bloques.size();++i){
				if(enemigos[k].collideBlock(barreras[j].bloques[i])){
					barreras[j].bloques[i].toRemove = true;
				}
			}
			barreras[j].bloques.erase(remove_if(barreras[j].bloques.begin(),barreras[j].bloques.end(),toRemoveBloque),barreras[j].bloques.end());
		}
	}
	enemigos.erase(remove_if(enemigos.begin(),enemigos.end(),toRemoveEnemy),enemigos.end());

	for(int k=0; k<enemigosSecretos.size(); ++k){
		if(enemigosSecretos[k].x >= SECRET_WALL)
			enemigosSecretos[k].toRemove = true;
		for(int j=0;j<balasAliadas.size();++j){
			Bala* b = &(balasAliadas[j]);
			if(b->collideEnemy(enemigosSecretos[k])){
				enemigosSecretos[k].toRemove = true;
				balasAliadas[j].toRemove = true;
				score+=300;
			}
		}
		balasAliadas.erase(remove_if(balasAliadas.begin(),balasAliadas.end(),toRemoveBala),balasAliadas.end());
	}
	enemigosSecretos.erase(remove_if(enemigosSecretos.begin(),enemigosSecretos.end(),toRemoveEnemy),enemigosSecretos.end());
}

void updateBalas(float wallY){
	for(int i=0;i<balasEnemigas.size();++i){
		balasEnemigas[i].update();
		if(ally.collideBullet(balasEnemigas[i])){
			play = false;
			break;
		}
		if(balasEnemigas[i].collideWall(wallY)){
			balasEnemigas.erase(balasEnemigas.begin()+i);
			--i;
		}
	}
	if(!play) return;
	for(int i=0;i<balasAliadas.size();++i){
		balasAliadas[i].update();
		if(balasAliadas[i].collideWall(wallY)){
			balasAliadas.erase(balasAliadas.begin()+i);
			--i;
		}
	}
}

void drawEnemigos(){
	for(int j=0; j<enemigos.size(); j++)
		enemigos[j].draw();
	for(int j=0; j<enemigosSecretos.size(); j++)
		enemigosSecretos[j].draw();
}

void drawBarreras(){
	for(int i =0;i<3;i++)
		barreras[i].draw();
}

void drawBalas(){
	for(int i=0;i<balasEnemigas.size();++i){
		balasEnemigas[i].draw();
	}
	for(int i=0;i<balasAliadas.size();++i){
		balasAliadas[i].draw();
	}
}

void changeViewport(int w, int h) {
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ar = (float) w / (float) h;

	if(w<=h){
		glOrtho(-31.0,31.0,-31.0/ar,31.0/ar,0.0,1.0);
//		glOrtho(-15.0,15.0,-15.0/ar,15.0/ar,0.0,1.0);
	}else{
		glOrtho(-31.0*ar,31.0*ar,-31.0,31.0,0.0,1.0);
//		glOrtho(-15.0*ar,15.0*ar,-15.0,15.0,0.0,1.0);
	}
//	glOrtho(-10.0,10.0,-10.0,10.0,0.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void ejesCoordenada(float limite) {

	glLineWidth(2.5);

	glBegin(GL_LINES);

		glColor3f(1.0,0.0,0.0);

		glVertex2f(0,limite);

		glVertex2f(0,-limite);

		glColor3f(0.0,0.0,1.0);

		glVertex2f(limite,0);

		glVertex2f(-limite,0);

	glEnd();

	glLineWidth(1.5);

	int i;

	glColor3f(0.0,1.0,0.0);

	glBegin(GL_LINES);

		for(i = -limite; i <=limite; i++){

			if (i!=0) {		

				if ((i%2)==0){	

					glVertex2f(i,0.4);

					glVertex2f(i,-0.4);

					glVertex2f(0.4,i);

					glVertex2f(-0.4,i);

				}else{

					glVertex2f(i,0.2);

					glVertex2f(i,-0.2);

					glVertex2f(0.2,i);

					glVertex2f(-0.2,i);

				}

			}

		}

 

	glEnd();

	glLineWidth(1.0);

}

void grid(){
	GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;

	glColor3f( 0.0f, 0.7f, 0.7f );
    glBegin( GL_LINES );
	zExtent = DEF_floorGridScale * DEF_floorGridZSteps;
    for(loopX = -DEF_floorGridXSteps; loopX <= DEF_floorGridXSteps; loopX++ )
	{
		xLocal = DEF_floorGridScale * loopX;
		glVertex3f( xLocal, -zExtent, 0.0f );
		glVertex3f( xLocal, zExtent,  0.0f );
	}
    xExtent = DEF_floorGridScale * DEF_floorGridXSteps;
    for(loopZ = -DEF_floorGridZSteps; loopZ <= DEF_floorGridZSteps; loopZ++ )
	{
		zLocal = DEF_floorGridScale * loopZ;
		glVertex3f( -xExtent, zLocal, 0.0f );
		glVertex3f(  xExtent, zLocal, 0.0f );
	}

    glEnd();
}

void render(){
	glClearColor(0.0, 0.2, 0.42, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//grid();
	//ejesCoordenada(30);

	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(5.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(WALL_WIDTH,WALL_HEIGHT);
		glVertex2f(-WALL_WIDTH,WALL_HEIGHT);
		glVertex2f(-WALL_WIDTH,-WALL_HEIGHT);
		glVertex2f(WALL_WIDTH,-WALL_HEIGHT);
	glEnd();

	ally.draw();
	drawBarreras();
	drawBalas();
	drawEnemigos();
	//drawScore(SCORE_X,SCORE_Y);
	glutSwapBuffers();
}

void update(int value){
	collideWorld();
	updateBalas(WALL_HEIGHT);
	ally.update(WALL_WIDTH);
	updateEnemigos();
	collideBarrera();
	glutPostRedisplay();
	cout << score << endl;
	if(play)
		glutTimerFunc(delay,update,0);
}

void randomEnemyShoot(int value){
	if(enemigos.size() > 0){
		uniform_int_distribution<int> shotDist(0,enemigos.size()-1);
		balasEnemigas.push_back(enemigos[shotDist(eng)].shoot());
		glutTimerFunc(ENEMY_RELOAD_TIME*1000,randomEnemyShoot,0);
	}
}

void secretShip(int value){
	Enemigo s = Enemigo::Enemigo(SECRET_SHIP_X,SECRET_SHIP_Y);
	s.secret = true;
	s.vel = 3.0f;
	enemigosSecretos.push_back(s);
	glutTimerFunc(SECRET_SHIP_TIME*1000,secretShip,0);
}

void keyPressed(unsigned char key,int x,int y){
	switch(key){
		case 32: if(!ally.shot && balasAliadas.size() < 4) balasAliadas.push_back(ally.shoot()); break;
		default: cout << (int) key << endl;break;
	}
}

void keyReleased(unsigned char key,int x,int y){
	switch(key){
		case 32: ally.shot = false;break;
		default: break;
	}
}

void specialPressed(int key,int x, int y){
	switch(key){
		case GLUT_KEY_LEFT: ally.onSpecialPress(Aliado::ALLY_LEFT);break;
		case GLUT_KEY_RIGHT: ally.onSpecialPress(Aliado::ALLY_RIGHT);break;
		default: break;
	}
}

void specialReleased(int key,int x, int y){
	switch(key){
		case GLUT_KEY_LEFT: ally.onSpecialRelease(Aliado::ALLY_LEFT);break;
		case GLUT_KEY_RIGHT: ally.onSpecialRelease(Aliado::ALLY_RIGHT);break;
		default: break;
	}
}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800,400);

	glutCreateWindow("Juego Opengl");
	cargarAliado();
	cargarEnemigos();
	cargarBarreras();

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutTimerFunc(delay,update,0);
	glutTimerFunc(ENEMY_RELOAD_TIME*1000,randomEnemyShoot,0);
	glutTimerFunc(SECRET_SHIP_TIME*1000,secretShip,0);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutSpecialFunc(specialPressed);
	glutSpecialUpFunc(specialReleased);
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	glutMainLoop();
	return 0;

}