#pragma once

#include "Library\glut.h"

#include <stdio.h>
#include <stdlib.h>

#define WINDOW_TIRTLE "Solar System"

const int windowXPos = 50,windowYPos = 50;
const int windowWidth = 500,windowHeight = 500;

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