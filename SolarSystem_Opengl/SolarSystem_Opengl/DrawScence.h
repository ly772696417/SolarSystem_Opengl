#pragma once

#include "header.h"
#include "SkyBox.h"
#include "Camera.h"

class DrawScence
{
public:
	DrawScence(void);
	~DrawScence(void);

	void DrawScenceInit();
	void Render();

	void SetItem();

private: 
	PolygonMode m_polygonMode;
	ShadingModel m_shaderMode;

	SkyBox *m_skybox;
	Camera *m_camera;
};

