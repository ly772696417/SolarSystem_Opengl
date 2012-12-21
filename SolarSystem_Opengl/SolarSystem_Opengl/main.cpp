#include "header.h"
#include "DrawScence.h"

DrawScence *m_drawScence;

void init(){
	m_drawScence->DrawScenceInit();
}

void myDisplay(){
	m_drawScence->Render();
}

void myReshape(int width,int height){

}

int main(int argc , char **argv){
	glutInit(&argc,argv);
	glutInitWindowPosition(windowXPos,windowYPos);
	glutInitWindowSize(windowWidth,windowHeight);
	glutCreateWindow(WINDOW_TIRTLE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	m_drawScence = new DrawScence();
	init();

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);

	glutMainLoop();
}