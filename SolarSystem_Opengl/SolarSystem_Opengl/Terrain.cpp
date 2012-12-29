#include "Terrain.h"

void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap)		// ��ȡ.raw�ļ�����
{
	FILE *pFile = NULL;

	pFile = fopen(strName, "rb");									// �Զ�������ʽ���ļ�

	if (pFile == NULL)												// �Ƿ��ҵ��ļ������ļ�
	{
		// ��ʾ��ʾ������Ϣ
		MessageBox(NULL, "�߶�ͼ�ļ���ʧ��!\nCan't open the height map.", "Error", MB_OK);
		return;														// ��������
	}

	fread( pHeightMap, 1, nSize, pFile );							// ����.raw �ļ��� pHeightMap����

	// ��ȡ���ݺ�һ���Ƿ�����
	if (ferror(pFile))
	{	// ��ʾ������Ϣ
		MessageBox(NULL, "��ȡ��������ʱ����!\nCan't get terrain data.", "Error", MB_OK);
	}

	fclose(pFile);													// �ر��ļ�
}

int Height(BYTE *pHeightMap, int X, int Y)							// ���ݸ߶�ͼ��X��Y���ظ߶�
{	
	// ��ֹ��������Ĵ�С
	int x = X % MAP_SIZE;
	int y = Y % MAP_SIZE;

	if(!pHeightMap) 												// ȷ��������Ч
	{
		return 0;													// �����������
	}

	// Ӧ�ù�ʽ: index = (x + (y * arrayWidth) ) ��ȡ�õ�ǰ�߶�
	return pHeightMap[x + (y * MAP_SIZE)];							// ���ص�ǰ�߶�
}

void SetTextureCoord(float x, float z)
{
	// ���ø߶�ͼ�ĵ�ǰ��������
	glTexCoord2f((float)x/(float)MAP_SIZE, -(float)z/(float)MAP_SIZE);
}

void RenderHeightMap(BYTE *pHeightMap, GLuint terrainTex)
{
	int X = 0, Y = 0;												// ���ڸ߶�ͼ�ϵ�����
	int x, y, z;													// �����ά����
	BOOL bSwitchSides = FALSE;

	if (!pHeightMap)												// ��֤�߶���Ч
	{
		return;
	}
	glBindTexture(GL_TEXTURE_2D, terrainTex);						// ������

	glBegin(GL_TRIANGLE_STRIP);										// ��ʼ���Ƶ���

	for (X = 0; X <= MAP_SIZE; X += STEP_SIZE)						// �����߶�ͼ
	{
		if (bSwitchSides)											// �Ƿ�ӷ������ȡ�߶�ͼ
		{	
			// �ڵ�ǰX��������Ⱦ����
			for (Y = MAP_SIZE; Y >= 0; Y -= STEP_SIZE)				// ��MAP_SIZE��0
			{
				// ȡ�õײ��󶥵�� (X, Y, Z)ֵ	
				x = X;
				y = Height(pHeightMap, X, Y);
				z = Y;

				// �ύ�㲢���õ�ǰ��������
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);

				// ȡ�õײ��Ҷ���� (X, Y, Z)ֵ
				x = X + STEP_SIZE;
				y = Height(pHeightMap, X + STEP_SIZE, Y);
				z = Y;

				// �ύ�㲢���õ�ǰ��������
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		else
		{
			// �ڵ�ǰX��������Ⱦ����
			for (Y = 0; Y <= MAP_SIZE; Y += STEP_SIZE)				// ��0��MAP_SIZE
			{
				// ȡ�õײ��Ҷ����(x, y, z)ֵ
				x = X + STEP_SIZE;
				y = Height(pHeightMap, X + STEP_SIZE, Y);
				z = Y;

				// �ύ�㲢���õ�ǰ��������
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);

				// ȡ�õײ��󶥵��(x, y, z)ֵ
				x = X;
				y = Height(pHeightMap, X, Y);
				z = Y;

				// �ύ�㲢���õ�ǰ��������
				SetTextureCoord((float)x, (float)z);
				glVertex3i(x, y, z);
			}
		}
		bSwitchSides = !bSwitchSides;								// �ı���Ʒ���
	}
	glEnd();														// �������Ƶ���
}
