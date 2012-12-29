#pragma once

#include "header.h"
#include "Texture.h"
#include "MyTexture.h"

class SkyBox
{
public:
	SkyBox(GLfloat radius,char *fileName[],GLint texNum);
	~SkyBox(void);

	void SkyBoxInit();
	void SetImage();
	void Render();

private:
	GLfloat m_radius;
	GLuint	skyTexture[6];		
	GLint m_texNum;
};

