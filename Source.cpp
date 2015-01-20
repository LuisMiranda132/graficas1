#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <vector>
#include "util.h"

using namespace std;

#define DEF_floorGridScale	1.0f
//#define DEF_floorGridXSteps	20.0f
//#define DEF_floorGridZSteps	20.0f
#define DEF_floorGridXSteps	40.0f
#define DEF_floorGridZSteps	40.0f


#define numEne 6
#define niveles 5

int delay = 100;

vector<Enemigo> enemigos;
vector<Barrera> barreras;

void collideWorld(){

	for(int i =0; i<numEne*niveles;i++)
		if(enemigos[i].collideRight(25.0,15.0,25.0,-15.0)){
			for(int j =0; j<numEne*niveles;j++){
				enemigos[j].vel=-(enemigos[j].vel*1.5);
				enemigos[j].y-=2.5;
				
			}
			break;
		}else if(enemigos[i].collideLeft(-25.0,15.0,-25.0,-15.0)){
			for(int j =0; j<numEne*niveles;j++){
				enemigos[j].vel=-(enemigos[j].vel*1.5);
				enemigos[j].y-=2.5;
				
			}
			break;
		}

/*	if(enemigos[0].collideRight(20.0,15.0,20.0,-15.0)){
		enemigos[0].vel=-enemigos[0].vel*2;
		enemigos[0].y-=2;
	}else if(enemigos[0].collideLeft(-20.0,15.0,-20.0,-15.0)){
		enemigos[0].vel=-enemigos[0].vel*2;
		enemigos[0].y-=2;
	}
*/
}

void cargarEnemigos(){
	for(int j=0; j<niveles; j++)
		for(int i =0; i<numEne;i++)
			enemigos.push_back(Enemigo::Enemigo(-20.0+6.0*i+(j % 2)*3,24-5*j));
}

void cargarBarreras(){
	barreras.push_back(Barrera::Barrera(-16.0,-16.0));
	barreras.push_back(Barrera::Barrera(0.0,-16.0));
	barreras.push_back(Barrera::Barrera(16.0,-16.0));
}

void updateEnemigos(){
	for(int i =0; i<numEne*niveles;i++)
		enemigos[i].update();
}

void drawEnemigos(){
	for(int i =0; i<numEne*niveles;i++)
		enemigos[i].draw();
}

void drawBarreras(){
	for(int i =0;i<3;i++)
		barreras[i].draw();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//grid();
	//ejesCoordenada(30);

	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(5.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(25.0,30.0);
		glVertex2f(-25.0,30.0);
		glVertex2f(-25.0,-30.0);
		glVertex2f(25.0,-30.0);
	glEnd();

//	glBegin(GL_LINE_LOOP);
//		glVertex2f(-25.0,-16.0);
//		glVertex2f(25.0,-16.0);
//	glEnd();

/*
	glPushMatrix();
		glTranslatef(-2.5,0.0,0.0);
		glBegin(GL_POLYGON);
			glVertex2f(2.0,1.0);
			glVertex2f(2.0,0.0);
			glVertex2f(-2.0,0.0);
			glVertex2f(-2.0,1.0);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2.5,0.0,0.0);
		glBegin(GL_POLYGON);
			glVertex2f(2.0,1.0);
			glVertex2f(2.0,0.0);
			glVertex2f(-2.0,0.0);
			glVertex2f(-2.0,1.0);
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.0,-1.5,0.0);
		glPushMatrix();
			glTranslatef(4.5,0.0,0.0);
			glBegin(GL_POLYGON);
				glVertex2f(2.0,1.0);
				glVertex2f(2.0,0.0);
				glVertex2f(-2.0,0.0);
				glVertex2f(-2.0,1.0);
			glEnd();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-4.5,0.0,0.0);
			glBegin(GL_POLYGON);
				glVertex2f(2.0,1.0);
				glVertex2f(2.0,0.0);
				glVertex2f(-2.0,0.0);
				glVertex2f(-2.0,1.0);
			glEnd();
		glPopMatrix();
		glTranslatef(0.0,-1.5,0.0);
		glPushMatrix();
		glTranslatef(-2.5,0.0,0.0);
		glBegin(GL_POLYGON);
			glVertex2f(2.0,1.0);
			glVertex2f(2.0,0.0);
			glVertex2f(-2.0,0.0);
			glVertex2f(-2.0,1.0);
		glEnd();
		glTranslatef(-4.5,0.0,0.0);
		glBegin(GL_POLYGON);
			glVertex2f(2.0,1.0);
			glVertex2f(2.0,0.0);
			glVertex2f(-2.0,0.0);
			glVertex2f(-2.0,1.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2.5,0.0,0.0);
			glBegin(GL_POLYGON);
				glVertex2f(2.0,1.0);
				glVertex2f(2.0,0.0);
				glVertex2f(-2.0,0.0);
				glVertex2f(-2.0,1.0);
			glEnd();
			glTranslatef(4.5,0.0,0.0);
			glBegin(GL_POLYGON);
				glVertex2f(2.0,1.0);
				glVertex2f(2.0,0.0);
				glVertex2f(-2.0,0.0);
				glVertex2f(-2.0,1.0);
			glEnd();
		glPopMatrix();
	glPopMatrix();
*/

	drawBarreras();

//	drawBarrera(-16.0,-16.0);
//	drawBarrera(0,-16.0);
//	drawBarrera(16.0,-16.0);
	
	drawEnemigos();
	glutSwapBuffers();
}

void update(int value){
	updateEnemigos();
	collideWorld();
	glutPostRedisplay();	
	glutTimerFunc(delay,update,0);
}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800,400);

	glutCreateWindow("Juego Opengl");
	cargarEnemigos();
	cargarBarreras();

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
//	glutTimerFunc(delay,update,0);
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	glutMainLoop();
	return 0;

}