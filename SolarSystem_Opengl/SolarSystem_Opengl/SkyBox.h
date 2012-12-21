#pragma once

#include "header.h"
#include "Texture.h"

class SkyBox
{
public:
	SkyBox(GLfloat radius,char *fileName,GLint texNum);
	~SkyBox(void);

	void SkyBoxInit();
	void SetImage();
	void Render();

private:
	GLfloat m_radius;
	Texture *m_skyTexture;
	GLint m_texNum;
};

