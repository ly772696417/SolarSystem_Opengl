#include "Terrain.h"

void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap)		// 读取.raw文件数据
{
	FILE *pFile = NULL;

	pFile = fopen(strName, "rb");									// 以二进制形式打开文件

	if (pFile == NULL)												// 是否找到文件并打开文件
	{
		// 显示提示错误信息
		MessageBox(NULL, "高度图文件打开失败!\nCan't open the height map.", "Error", MB_OK);
		return;														// 结束函数
	}

	fread( pHeightMap, 1, nSize, pFile );							// 导入.raw 文件到 pHeightMap数组

	// 读取数据后一切是否正常
	if (ferror(pFile))
	{	// 显示出错信息
		MessageBox(NULL, "读取地形数据时出错!\nCan't get terrain data.", "Error", MB_OK);
	}

	fclose(pFile);													// 关闭文件
}

int Height(BYTE *pHeightMap, int X, int Y)							// 根据高度图的X和Y返回高度
{	
	// 防止超过数组的大小
	int x = X % MAP_SIZE;
	int y = Y % MAP_SIZE;

	if(!pHeightMap) 												// 确认数据有效
	{
		return 0;													// 否则结束函数
	}

	// 应用公式: index = (x + (y * arrayWidth) ) 来取得当前高度
	return pHeightMap[x + (y * MAP_SIZE)];							// 返回当前高度
}

void SetTextureCoord(float x, float z)
{
	// 设置高度图的当前纹理坐标
	glTexCoord2f((float)x/(float)MAP_SIZE, -(float)z/(float)MAP_SIZE);
}

void RenderHeightMap(BYTE *pHeightMap, GLuint terrainTex)
{
	int X = 0, Y = 0;												// 点在高度图上的坐标
	int x, y, z;													// 点的三维坐标
	BOOL bSwitchSides = FALSE;

	if (!pHeightMap)												// 保证高度有效
	{
		return;
	}
	glBindTexture(GL_TEXTURE_2D, terrainTex);						// 绑定纹理

	glBegin(GL_TRIANGLE_STRIP);										// 开始绘制地形

	for (X = 0; X <= MAP_SIZE; X += STEP_SIZE)						// 遍历高度图
	{
		if (bSwitchSides)											// 是否从反方向读取高度图
		{	
			// 在当前X坐标上渲染地形
			for (Y = MAP_SIZE; Y >= 0; Y -= STEP_SIZE)				// 从MAP_SIZE到0
			{
				// 取得底部左顶点的 (X, Y, Z)值	
				x = X;
				y = Height(pHeightMap, X, Y);
				z = Y;

				// 提交点并设置当前纹理坐标
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);

				// 取得底部右顶点的 (X, Y, Z)值
				x = X + STEP_SIZE;
				y = Height(pHeightMap, X + STEP_SIZE, Y);
				z = Y;

				// 提交点并设置当前纹理坐标
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		else
		{
			// 在当前X坐标上渲染地形
			for (Y = 0; Y <= MAP_SIZE; Y += STEP_SIZE)				// 从0到MAP_SIZE
			{
				// 取得底部右顶点的(x, y, z)值
				x = X + STEP_SIZE;
				y = Height(pHeightMap, X + STEP_SIZE, Y);
				z = Y;

				// 提交点并设置当前纹理坐标
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);

				// 取得底部左顶点的(x, y, z)值
				x = X;
				y = Height(pHeightMap, X, Y);
				z = Y;

				// 提交点并设置当前纹理坐标
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		bSwitchSides = !bSwitchSides;								// 改变绘制方向
	}
	glEnd();														// 结束绘制地形
}
