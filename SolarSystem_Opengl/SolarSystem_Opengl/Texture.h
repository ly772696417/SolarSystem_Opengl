#pragma once

#include "header.h"

#define BMP_Header_Length 54

class Texture
{
public:
	Texture(char *file_name);
	~Texture();

	int Power_of_two(int n);
	void Load_texture();
	void SetTexture();

private:
	char *m_file_name;
	GLuint m_texture_ID;
};



