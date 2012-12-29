#include "SkyBox.h"


SkyBox::SkyBox(GLfloat radius,char *fileName[],GLint texNum)
{
	m_radius = radius;
	m_texNum = texNum;
	for (int i = 0;i<6;i++)
	{
		//BuildTexture(fileName[i], skyTexture[i]);
		skyTexture[i] = load_texture(fileName[i]);
	}
}


SkyBox::~SkyBox(void)
{
}

void SkyBox::SkyBoxInit(){
	glEnable(GL_TEXTURE_2D);
}

void SkyBox::SetImage(){
	for (int i = 0;i<6;i++)
	{
	}
}

void SkyBox::Render(){
	glPushMatrix();
	glDisable(GL_DEPTH);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	GLfloat cx = 0.0f,cy = 0.0f,cz = 0.0f;
	
	GLfloat width,height,length;
	width = height = length = m_radius;
	float x = cx - width  / 2.0f;
	float y = cy - height / 2.0f;
	float z = cz - length / 2.0f;

	//z negative
	glBindTexture(GL_TEXTURE_2D, skyTexture[0]);

	GLfloat arr_t2f_v3f_back[] = {
		1.0f, 0.0f,x + width,	y,					z,
		1.0f, 1.0f,x + width,	y + height,	z,
		0.0f, 1.0f,x,				y + height,	z,
		0.0f, 0.0f,x,				y,					z
	};
	GLuint index_list_back[] = {0,1,2,3};
	glInterleavedArrays(GL_T2F_V3F,0,arr_t2f_v3f_back);
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,index_list_back);

	//z positive
	glBindTexture(GL_TEXTURE_2D, skyTexture[1]);

	GLfloat arr_t2f_v3f_front[] = {
		1.0f, 0.0f,x,				y,					z + width,
		1.0f, 1.0f,x,				y + height,	z + width,
		0.0f, 1.0f,x + height,	y + height,	z + height,
		0.0f, 0.0f,x + height,	y,					z + height
	};
	GLuint index_list_front[] = {0,1,2,3};
	glInterleavedArrays(GL_T2F_V3F,0,arr_t2f_v3f_front);
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,index_list_front);
	
	// y negative
	glBindTexture(GL_TEXTURE_2D, skyTexture[2]);

	GLfloat arr_t2f_v3f_bottom[] = {
		0.0f, 0.0f,x,				y,			z + width,
		1.0f, 0.0f,x+ length,	y,			z + length,
		1.0f, 1.0f,x + width,	y,			z,
		0.0f, 1.0f,x,				y,			z
	};
	GLuint index_list_bottom[] = {0,1,2,3};
	glInterleavedArrays(GL_T2F_V3F,0,arr_t2f_v3f_bottom);
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,index_list_bottom);

	// y positive
	glBindTexture(GL_TEXTURE_2D, skyTexture[3]);

	GLfloat arr_t2f_v3f_top[] = {
		0.0f, 0.0f,x,				y + height,   z,
		1.0f, 0.0f,x + width,	y + height,   z,
		1.0f, 1.0f,x + width,	y + height,	z + length,
		0.0f, 1.0f,x,				y + height,	z + length
	};
	GLuint index_list_top[] = {0,1,2,3};
	glInterleavedArrays(GL_T2F_V3F,0,arr_t2f_v3f_top);
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,index_list_top);

	// x negative
	glBindTexture(GL_TEXTURE_2D, skyTexture[4]);

	GLfloat arr_t2f_v3f_left[] = {
		1.0f, 1.0f,x,			y + height,	z,
		0.0f, 1.0f,x,			y + height,	z + length,
		0.0f, 0.0f,x,			y,					z + length,
		1.0f, 0.0f,x,			y,					z
	};
	GLuint index_list_left[] = {0,1,2,3};
	glInterleavedArrays(GL_T2F_V3F,0,arr_t2f_v3f_left);
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,index_list_left);

	// x positive
	glBindTexture(GL_TEXTURE_2D, skyTexture[5]);

	GLfloat arr_t2f_v3f_right[] = {
		0.0f, 0.0f,x + width, y,				z,
		1.0f, 0.0f,x + width, y,				z + length,
		1.0f, 1.0f,x + width, y + height,	z + length,
		0.0f, 1.0f,x + width, y + height,	z
	};
	GLuint index_list_right[] = {0,1,2,3};
	glInterleavedArrays(GL_T2F_V3F,0,arr_t2f_v3f_right);
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,index_list_right);

	//»Ö¸´µ½Ä¬ÈÏ×´Ì¬
	glEnable(GL_DEPTH);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glPopMatrix();
}
