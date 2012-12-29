#pragma once

#include "header.h"

#define MAP_SIZE		1024										// 定义高度图的大小
#define STEP_SIZE		16											// 每个三角网格的高和宽

void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap);		// 导入.raw文件

int Height(BYTE *pHeightMap, int X, int Y);							// 根据X和Y返回高度值

void RenderHeightMap(BYTE *pHeightMap, GLuint terrainTex);			// 转换高度图并将它绘制在场景中
