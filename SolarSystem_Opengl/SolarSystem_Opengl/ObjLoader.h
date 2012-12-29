#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include"glaux.h"		

using namespace std;

	struct ObjVertex{
		 float X, Y, Z;
	};

	struct ObjNormal{
		 double X, Y, Z;
	};

	struct ObjTexCoord{
		 float U, V;
	};

	struct ObjTriangle{
		unsigned int Vertex[3];
		unsigned int Normal[3];
		unsigned int TexCoord[3];
	};

	struct ObjModel {
		public:
			ObjModel();
			~ObjModel();

			ObjModel(const ObjModel& copy);
			ObjModel& operator=(const ObjModel& right);

			void FreeObjMdel(void);
			
			unsigned int NumVertex, NumNormal, NumTexCoord, NumTriangle, NumTexture, NumMtl, *TextureMark;

			ObjVertex *VertexArray;
			ObjNormal *NormalArray;
			ObjTexCoord *TexCoordArray;

			ObjTriangle *TriangleArray;

			GLuint *TextureArray;

			GLuint	**TextureMarkArray;
	};

	class ObjLoader  {
		public:
			ObjLoader();
			~ObjLoader();

			ObjLoader(string file);
			void LoadObj(string file);
			void FreeObj(void);
			ObjModel ReturnObj(void);

		protected:
			string *fileName;
			ObjModel *theObj;
			string *texturen;
			
			void LoadMtl(string mtlfilename);
			void ReadData(void);
	};