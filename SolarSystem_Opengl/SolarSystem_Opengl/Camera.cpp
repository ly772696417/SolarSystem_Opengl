#include "Camera.h"

Camera::Camera(){
	
	m_eye.Posx = 5.0f;
	m_eye.Posy = 0.0f;
	m_eye.Posz = -20.0f;

	m_centery.Posx = 0.0f;
	m_centery.Posy = 0.0f;
	m_centery.Posz = 0.0f;

	m_up.vectorX = 0.0f;
	m_up.vectorY = 1.0f;
	m_up.vectorZ = 0.0f;
}

Camera::Camera(Point eye,Point centery,Vector up)
{
	m_eye = eye;
	m_centery = centery;
	m_up = up;

}


Camera::~Camera(void)
{
}

void Camera::SetCamera(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75,1,1,400);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(m_eye.Posx,m_eye.Posy,m_eye.Posz,
					m_centery.Posx,m_centery.Posy,m_centery.Posz,
					m_up.vectorX,m_up.vectorY,m_up.vectorZ);
}


