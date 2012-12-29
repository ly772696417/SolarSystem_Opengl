#include "Sphere.h"

#define TESSELATION	50
double c=M_PI/180.0;

Sphere::Sphere(GLfloat radius)
{
	m_radius = radius;
}


Sphere::~Sphere(void)
{
}

void Sphere::Render(){
	float length = 0.0f;

	glBegin(GL_TRIANGLE_STRIP);
	for(int i = TESSELATION; i >= 0; i--) 
	{
		double	lat0 = M_PI * (-0.5 + (double) (i - 1) / TESSELATION),
			z0  = sin(lat0),
			zr0 =  cos(lat0),
			lat1 = M_PI * (-0.5 + (double) i / TESSELATION),
			z1 = sin(lat1),
			zr1 = cos(lat1);
		for(int j = 0; j <= TESSELATION; j++) 
		{
			double	lng = 2 * M_PI * (double) (j - 1) / TESSELATION,
				x = cos(lng),
				y = sin(lng),
				len = sqrt(x * zr0 * x * zr0 + y * zr0 * y * zr0 + z0 * z0),
				len1 = sqrt(x * zr1 * x * zr1 + y * zr1 * y * zr1 + z1 * z1),
				v = acos(-y * zr0 / len) / M_PI,
				u = (atan2(z0, x * zr0) / M_PI + 1.0f) * 0.5f,
				v1 = acos(-y * zr1 / len1) / M_PI,
				u1 = (atan2(z1, x * zr1) / M_PI + 1.0f) * 0.5f;
			glTexCoord2f(u, v);
			glNormal3f(x * zr0/len,y * zr0/len,z0/len);
			glVertex3f(m_radius * x * zr0, m_radius * y * zr0, m_radius * z0);
			glTexCoord2f(u1, v1);
			glNormal3f(x * zr1/len1,y * zr1/len1,z1/len1);
			glVertex3f(m_radius * x * zr1, m_radius * y * zr1, m_radius * z1);
		}
	}
	glEnd();
}
