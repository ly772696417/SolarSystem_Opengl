#include "Light.h"


Light::Light(GLfloat light_position[],GLfloat light_ambient[],GLfloat light_diffuse[],GLfloat light_specular[])
{
	for (int i = 0; i < 4; i++)
	{
		m_light_position[i] = light_position[i];
		m_light_ambient[i] = light_ambient[i];
		m_light_diffuse[i] = light_diffuse[i];
		m_light_specular[i] = light_specular[i];
	}
}


Light::~Light(void)
{
}


void Light::SetLight(){
	glLightfv(GL_LIGHT0,GL_POSITION,m_light_position);
	glLightfv(GL_LIGHT0,GL_AMBIENT,m_light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,m_light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,m_light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}
