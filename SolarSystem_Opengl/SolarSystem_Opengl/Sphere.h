#pragma once

#include "header.h"

class Sphere
{
public:
	Sphere(GLfloat radius);
	~Sphere(void);

	void Render();

private:
	double m_radius;
};

