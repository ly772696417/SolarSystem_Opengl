#include "DrawScence.h"

PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB= NULL;

GLuint	terrainTex;
BYTE	g_HeightMap[MAP_SIZE*MAP_SIZE];

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
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);							// 所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			// 真正精细的透视修正
	glEnable(GL_CULL_FACE);

	m_camera = new Camera();

	GLfloat sun_light_position[] = {0.0f,0.0f,0.0f,1.0f};
	GLfloat sun_light_ambient[] = {1.0,1.0f,1.0f,1.0f};
	GLfloat sun_light_diffuse[]   = {1.0f,1.0f,1.0f,1.0f};
	GLfloat sun_light_specular[] = {1.0f,1.0f,1.0f,1.0f};
	m_light = new Light(sun_light_position,sun_light_ambient,sun_light_diffuse,sun_light_specular);
	
	char *skyboxImageFileName[] = {"Image//SkyBoxImage//front.bmp",
														  "Image//SkyBoxImage//back.bmp",
														  "Image//SkyBoxImage//bottom.bmp",
														  "Image//SkyBoxImage//top.bmp",
														  "Image//SkyBoxImage//left.bmp",
														  "Image//SkyBoxImage//right.bmp"
	};
	
	m_skybox = new SkyBox(100.0f,skyboxImageFileName,1);
	m_skybox->SkyBoxInit();
	m_skybox->SetImage();

	//BuildTexture("Image//SphereImage//sun.bmp",m_sphereTexture[0]);
	//BuildTexture("Image//SphereImage//earth.bmp",m_sphereTexture[1]);
	//BuildTexture("Image//SphereImage//moon.bmp",m_sphereTexture[2]);

	m_sphereTexture[0] = load_texture("Image//SphereImage//sun.bmp");
	m_sphereTexture[1] = load_texture("Image//SphereImage//earth.bmp");
	m_sphereTexture[2] = load_texture("Image//SphereImage//moon.bmp");

	ObjLoader LoaderClass("earth.obj");
	data = LoaderClass.ReturnObj();

	//BuildTexture("Image//Ray.bmp" , rayTexture);
	rayTexture = load_texture("Image//Ray.bmp");

	//LoadRawFile("Data/Terrain.raw", MAP_SIZE * MAP_SIZE, g_HeightMap);
	//BuildTexture("Data/Terrain.jpg",terrainTex);

	/*
	taiji[0] = load_texture("Image//taiji0.bmp");
	taiji[1] = load_texture("Image//taiji.bmp");

	glActiveTextureARB=(PFNGLCLIENTACTIVETEXTUREARBPROC)wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC)wglGetProcAddress("glMultiTexCoord2fARB");
	glClientActiveTextureARB=(PFNGLACTIVETEXTUREARBPROC)wglGetProcAddress("glClientActiveTextureARB");
	*/
}

void DrawScence::Render(int day){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetItem();

	m_camera->SetCamera();
	glPushMatrix();
	m_skybox->Render();

	m_light->SetLight();	

	//RenderHeightMap(g_HeightMap, terrainTex);
	
	//太阳 - 自己通过计算坐标、法线等渲染出来的
	glBindTexture(GL_TEXTURE_2D,m_sphereTexture[0]);
	Sphere *sun = new Sphere(10.0f);
	sun->Render();

	//光晕
	glBindTexture(GL_TEXTURE_2D,rayTexture);  
	glEnable(GL_BLEND);                
	glDisable(GL_DEPTH_TEST);           
	
	glDisable(GL_LIGHTING);                         
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);   
	float increment = 0.0f;
	//顶点数组
	GLfloat arr_t2f_v3f_ray[] = {
		0.0f, 0.0f,0.0f, 0.0f, 1.0f,-10.0f+increment,-10.0f+increment, 0.0f,
		1.0f, 0.0f,0.0f, 0.0f, 1.0f,10.0f+increment,-10.0f+increment, 0.0f,
		1.0f, 1.0f,0.0f, 0.0f, 1.0f,10.0f+increment, 10.0f+increment, 0.0f,
		0.0f, 1.0f,0.0f, 0.0f, 1.0f,-10.0f+increment, 10.0f+increment, 0.0f
	};
	GLuint index_list_ray[] = {0,1,2,3};
	glInterleavedArrays(GL_T2F_N3F_V3F,0,arr_t2f_v3f_ray);
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,index_list_ray);
	glDisable(GL_BLEND);                                 
	glEnable(GL_DEPTH_TEST);

	glRotatef(day/360.0*360,0.0f,1.0f,0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	glEnable(GL_LIGHTING);                                         

	glBindTexture(GL_TEXTURE_2D,m_sphereTexture[1]);

	for(unsigned int i=0,j=0,k;i<data.NumTexture;i++)
	{
		//glBindTexture(GL_TEXTURE_2D, *data.TextureMarkArray[i]);
		glBegin(GL_TRIANGLES);
		for(;j<data.TextureMark[i];j++)
			for(k=0;k<=2;k++)
			{
				glTexCoord2f(data.TexCoordArray[data.TriangleArray[j].TexCoord[k]].U,data.TexCoordArray[data.TriangleArray[j].TexCoord[k]].V); 
				glNormal3f(data.NormalArray[data.TriangleArray[j].Normal[k]].X,data.NormalArray[data.TriangleArray[j].Normal[k]].Y,data.NormalArray[data.TriangleArray[j].Normal[k]].Z);//法向量
				glVertex3f(data.VertexArray[data.TriangleArray[j].Vertex[k]].X,data.VertexArray[data.TriangleArray[j].Vertex[k]].Y,data.VertexArray[data.TriangleArray[j].Vertex[k]].Z);
			}
			glEnd();
	}

	glRotatef(day/30.0*360.0 - day/360.0*360.0, 0.0f, 1.0f, 0.0f);
	glTranslatef(10, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D,m_sphereTexture[2]);
	Sphere *earth = new Sphere(1.5f);
	earth->Render();
	/*
	glPopMatrix();
	
	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,taiji[0]);

	glActiveTextureARB(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,taiji[1]);
	
	glTranslatef(30,0,0);
	GLfloat arr_t2f_v3f_front[] = {
		0.0f, 0.0f,-10,	-10,0,
		1.0f, 0.0f,10,-10,0,
		1.0f, 1.0f,10,10,0,
		0.0f, 1.0f,-10,	10,0
	};
	GLuint index_list_front[] = {0,1,2,3};
	glInterleavedArrays(GL_T2F_V3F,0,arr_t2f_v3f_front);
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,index_list_front);
	*/

	glFlush();
	glutSwapBuffers();
}

void DrawScence::SetItem(){

}

void DrawScence::SetInput(char key){
	Point tempEye = m_camera->getEye();
	switch (key)
	{
	case 'd':
		if (tempEye.Posx<=20.0f)
		{
			tempEye.Posx+=0.5f;
			m_camera->setEye(tempEye);
		}
		break;
	case 'a':
		if (tempEye.Posx>=-20.0f)
		{
			tempEye.Posx-=0.5f;
			m_camera->setEye(tempEye);
		}
		break;
	case 'w':
		if (tempEye.Posy<=20.0f)
		{
			tempEye.Posy+=0.5f;
			m_camera->setEye(tempEye);
		}
		break;
	case 's':
		if (tempEye.Posy>=-20.0f)
		{
			tempEye.Posy-=0.5f;
			m_camera->setEye(tempEye);
		}
		break;
	default:
		break;
	}
}