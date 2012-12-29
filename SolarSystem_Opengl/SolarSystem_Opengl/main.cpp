#include "header.h"
#include "DrawScence.h"

DrawScence *m_drawScence;
static int day = 150; 

void init(){
	m_drawScence->DrawScenceInit();
}

void myDisplay(){
	m_drawScence->Render(day);
}

void myReshape(int width,int height){

}

void keyboard(unsigned char key, int x, int y)
{
	switch(key) {
	case 'd': case 'D':
		m_drawScence->SetInput('d');
		break;
	case 'a': case 'A':
		m_drawScence->SetInput('a');
		break;
	case 'w': case 'W':
		m_drawScence->SetInput('w');
		break;
	case 's': case 'S':
		m_drawScence->SetInput('s');
		break;
	case VK_ESCAPE:                                                 // °´ESC¼üÊ±ÍË³ö
		exit(0);
		break;
	default:
		break;
	}
}

void mouse(int button,int state,int x,int y){
	printf("x:%d y:%d",x,y);
}

void myIdle(void)
{
	day += 1;
	if( day >= 360 )
		day = 0;

	myDisplay();

	_sleep(30);
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
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(&myIdle);

	glutMainLoop();
}