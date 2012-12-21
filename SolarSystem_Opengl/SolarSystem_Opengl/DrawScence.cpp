#include "DrawScence.h"


DrawScence::DrawScence(void)
{
	m_polygonMode = solidModel;
	m_shaderMode = smoothShading;
}


DrawScence::~DrawScence(void)
{

}

void DrawScence::DrawScenceInit(){
	glClearColor(0.0f,0.0f,0.0f,0.5f);
	//深度测试
	glEnable(GL_DEPTH_TEST);
	//反面切割
	glEnable(GL_CULL_FACE);

	m_camera = new Camera();

	m_skybox = new SkyBox(50.0f,"Image//feng.bmp",1);

}

void DrawScence::Render(){
	SetItem();
	m_camera->SetCamera();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_skybox->SkyBoxInit();
	m_skybox->SetImage();
	m_skybox->Render();
}

void DrawScence::SetItem(){

}
