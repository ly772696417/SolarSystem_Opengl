#pragma once

#include "Library\glut.h"
#include "glext.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<time.h>
#include<math.h>

#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )	
#pragma comment( lib, "glut32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment( lib, "glaux.lib")
#pragma comment( lib, "vfw32.lib" )	

#define WINDOW_TIRTLE "Solar System"
#define  M_PI 3.1415926

const int windowXPos = 50,windowYPos = 50;
const int windowWidth = 500,windowHeight = 500;

#define GL_CLAMP_TO_EDGE	0x812F

enum PolygonMode
{
	pointMode,
	wireframeMode,
	solidModel,
};

enum ShadingModel
{
	flatShading,
	smoothShading,
};

struct Point
{
	double Posx,Posy,Posz;
};

struct Vector
{
	double vectorX,vectorY,vectorZ;
};