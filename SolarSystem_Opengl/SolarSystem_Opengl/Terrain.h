#pragma once

#include "header.h"

#define MAP_SIZE		1024										// ����߶�ͼ�Ĵ�С
#define STEP_SIZE		16											// ÿ����������ĸߺͿ�

void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap);		// ����.raw�ļ�

int Height(BYTE *pHeightMap, int X, int Y);							// ����X��Y���ظ߶�ֵ

void RenderHeightMap(BYTE *pHeightMap, GLuint terrainTex);			// ת���߶�ͼ�����������ڳ�����
