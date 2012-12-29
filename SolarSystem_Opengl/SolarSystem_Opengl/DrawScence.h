#pragma once

#include "header.h"
#include "SkyBox.h"
#include "Camera.h"
#include "Sphere.h"
#include "Light.h"
#include "ObjLoader.h"
#include "Terrain.h"
#include "MyTexture.h"

class DrawScence
{
public:
	DrawScence(void);
	~DrawScence(void);

	void DrawScenceInit();
	void Render(int day);
	void SetInput(char key);
	void SetItem();

private: 
	PolygonMode m_polygonMode;
	ShadingModel m_shaderMode;

	GLuint	m_sphereTexture[3];
	GLuint rayTexture;
	GLuint taiji[2];

	SkyBox *m_skybox;
	Camera *m_camera;	
	Light *m_light;

	ObjModel data;
};

