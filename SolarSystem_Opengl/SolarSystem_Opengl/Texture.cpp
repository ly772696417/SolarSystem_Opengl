#include "Texture.h"

Texture::Texture(char *file_name)
{
	m_file_name = file_name;
}

Texture::~Texture()
{
}

int Texture::Power_of_two(int n){
	if( n <= 0 )
        return 0;
    return (n & (n-1)) == 0;
}

void Texture::Load_texture(){
	GLint width,height,total_bytes;
	GLubyte *pixels = 0;
	GLint last_texture_ID;

	FILE *pFile = fopen(m_file_name,"rb");
	if (pFile == 0)	
	{
		return;
	}

	fseek(pFile,0x0012,SEEK_SET);
	fread(&width,4,1,pFile);
	fread(&height,4,1,pFile);
	fseek(pFile,BMP_Header_Length,SEEK_SET);

	{
		GLint line_bytes = width * 3;
		while(line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	pixels = (GLubyte *)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return;
	}

	if (fread(pixels,total_bytes,1,pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return;
	}

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE,&max);
		if (!Power_of_two(width)
			||!Power_of_two(height)
			||width > max
			||height > max 
			)
		{
			const GLint new_width = 256;
			const GLint new_height = 256;
			GLint new_line_bytes,new_total_bytes;
			GLubyte *new_pixels = 0;

			new_line_bytes = new_width * 3;
            while( new_line_bytes % 4 != 0 )
                ++new_line_bytes;
            new_total_bytes = new_line_bytes * new_height;

			new_pixels = (GLubyte*)malloc(new_total_bytes);
            if( new_pixels == 0 )
            {
                free(pixels);
                fclose(pFile);
                return;
            }

			gluScaleImage(GL_RGB,
                width, height, GL_UNSIGNED_BYTE, pixels,
                new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			free(pixels);
            pixels = new_pixels;
            width = new_width;
            height = new_height;
		}

		glGenTextures(1, &m_texture_ID);
		if( m_texture_ID == 0 )
		{
			free(pixels);
			fclose(pFile);
			return;
		}
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, m_texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	free(pixels);
}

void Texture::SetTexture(){
	glBindTexture(GL_TEXTURE_2D,m_texture_ID);
}