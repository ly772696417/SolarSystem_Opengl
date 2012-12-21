#include "SkyBox.h"


SkyBox::SkyBox(GLfloat radius,char *fileName,GLint texNum)
{
	m_radius = radius;
	m_texNum = texNum;
	m_skyTexture = new Texture(fileName);
}


SkyBox::~SkyBox(void)
{
}

void SkyBox::SkyBoxInit(){
	glEnable(GL_TEXTURE_2D);
}

void SkyBox::SetImage(){
	m_skyTexture->Load_texture();
}

void SkyBox::Render(){
	m_skyTexture->SetTexture();

	//x positive
	glBegin(GL_QUADS);
	glNormal3f(-1.0f,0.0f,0.0f);

	glTexCoord2f(0.0f,0.0f);
	glVertex3f(m_radius,-1.0f * m_radius,-1.0f * m_radius); 

	glTexCoord2f(1.0f * m_texNum,0.0f);
	glVertex3f(m_radius,-1.0f * m_radius,m_radius);
	
	glTexCoord2d(1.0f * m_texNum,1.0f * m_texNum);
	glVertex3f(m_radius,m_radius,m_radius);
	
	glTexCoord2f(0.0f,1.0f * m_texNum);
	glVertex3f(m_radius,m_radius,-1.0f * m_radius);

	glEnd();

	//x negative
	glBegin(GL_QUADS);
	glNormal3f(1.0f,0.0f,0.0f);

	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f * m_radius,-1.0f * m_radius,m_radius); 
	
	glTexCoord2f(1.0f * m_texNum,0.0f);
	glVertex3f(-1.0f * m_radius,-1.0f * m_radius,-1.0f * m_radius);
	
	glTexCoord2d(1.0f * m_texNum,1.0f * m_texNum);
	glVertex3f(-1.0f * m_radius,m_radius,-1.0f * m_radius);
	
	glTexCoord2f(0.0f,1.0f * m_texNum);
	glVertex3f(-1.0f * m_radius,m_radius,m_radius);

	glEnd();

	//y positive
	glBegin(GL_QUADS);
	glNormal3f(0.0f,-1.0f,0.0f);

	glTexCoord2f(0.0f,0.0f);
	glVertex3f(m_radius,m_radius,m_radius); 
	
	glTexCoord2f(1.0f * m_texNum,0.0f);
	glVertex3f(-1.0f * m_radius,m_radius,m_radius);
	
	glTexCoord2d(1.0f * m_texNum,1.0f * m_texNum);
	glVertex3f(-1.0f * m_radius,m_radius,-1.0f * m_radius);
	
	glTexCoord2f(0.0f,1.0f * m_texNum);
	glVertex3f(m_radius,m_radius,-1.0f * m_radius);

	glEnd();

	//y negative
	glBegin(GL_QUADS);
	glNormal3f(0.0f,1.0f,0.0f);

	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f * m_radius,-1.0f * m_radius,m_radius); 
	
	glTexCoord2f(1.0f * m_texNum,0.0f);
	glVertex3f(m_radius,-1.0f * m_radius,m_radius);
	
	glTexCoord2d(1.0f * m_texNum,1.0f * m_texNum);
	glVertex3f(m_radius,-1.0f * m_radius,-1.0f * m_radius);
	
	glTexCoord2f(0.0f,1.0f * m_texNum);
	glVertex3f(-1.0f * m_radius,-1.0f * m_radius,-1.0f * m_radius);

	glEnd();
	
	//positive z
	glBegin(GL_QUADS);
	glNormal3f(0.0f,0.0f,-1.0f);

	glTexCoord2f(0.0f,0.0f);
	glVertex3f(m_radius,-1.0f * m_radius,m_radius); 
	
	glTexCoord2f(1.0f * m_texNum,0.0f);
	glVertex3f(- 1.0f * m_radius,- 1.0f * m_radius,m_radius);
	
	glTexCoord2d(1.0f * m_texNum,1.0f * m_texNum);
	glVertex3f(- 1.0f * m_radius,m_radius,m_radius);
	
	glTexCoord2f(0.0f,1.0f * m_texNum);
	glVertex3f(m_radius,m_radius,m_radius);
	
	glEnd();
	
	/*
	//negative z
	glBegin(GL_QUADS);
	glNormal3f(0.0f,0.0f,1.0f);

	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f * m_radius,-1.0f * m_radius,-1.0f * m_radius); 
	
	glTexCoord2f(1.0f * m_texNum,0.0f);
	glVertex3f(m_radius,-1.0f * m_radius,-1.0f * m_radius);
	
	glTexCoord2d(1.0f * m_texNum,1.0f * m_texNum);
	glVertex3f(m_radius,m_radius,-1.0f * m_radius);
	
	glTexCoord2f(0.0f,1.0f * m_texNum);
	glVertex3f(-1.0f * m_radius,m_radius,-1.0f * m_radius);
	
	glEnd();
	*/
	
	glFlush();
	glutSwapBuffers();

}
