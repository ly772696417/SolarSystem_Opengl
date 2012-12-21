#pragma once

#include "header.h"

class Light
{
public:
	Light(GLfloat light_position[],GLfloat light_ambient[],GLfloat light_diffuse[],GLfloat light_specular[]);
	~Light(void);

	void SetLight();

private:
	GLfloat m_light_position[4];
	GLfloat m_light_ambient[4];
	GLfloat m_light_diffuse[4];
	GLfloat m_light_specular[4];
};

