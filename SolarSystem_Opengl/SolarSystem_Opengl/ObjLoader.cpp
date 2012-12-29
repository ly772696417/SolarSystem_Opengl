#include "ObjLoader.h"
using namespace std;

ObjModel::ObjModel(): 	NumNormal (0),
	NumTexCoord(0),
	NumTriangle(0),
	NumVertex(0),	
	NumTexture(0),
	NumMtl(0),
	NormalArray(NULL),
	TexCoordArray(NULL),
	TriangleArray(NULL),
	VertexArray(NULL),
	TextureMark(NULL),
	TextureArray(NULL),
    TextureMarkArray(NULL) {}

ObjModel::~ObjModel() 
{
	FreeObjMdel();
}

void ObjModel::FreeObjMdel(void)
{
	//
	if(NormalArray!= NULL){ delete [] NormalArray;NormalArray= NULL;}
	if(TexCoordArray!= NULL){ delete [] TexCoordArray;TexCoordArray= NULL;}
	if(TriangleArray!= NULL){ delete [] TriangleArray;TriangleArray= NULL;}
	if(VertexArray!= NULL){ delete [] VertexArray;VertexArray= NULL;}
	if(TextureMark!= NULL){ delete [] TextureMark;TextureMark= NULL;}
	if(TextureArray!= NULL){ delete [] TextureArray;TextureArray= NULL;}
	if(TextureMarkArray!= NULL){ delete [] TextureMarkArray;TextureMarkArray= NULL;}
}

ObjModel::ObjModel(const ObjModel &copy)
{
	ObjModel::NormalArray= new ObjNormal[copy.NumNormal];
	ObjModel::TexCoordArray= new ObjTexCoord[copy.NumTexCoord];
	ObjModel::TriangleArray= new ObjTriangle[copy.NumTriangle];
	ObjModel::VertexArray= new ObjVertex[copy.NumVertex];
	ObjModel::TextureMark= new unsigned int[copy.NumTexture];
	ObjModel::TextureArray= new GLuint[copy.NumMtl];
	ObjModel::TextureMarkArray= new GLuint *[copy.NumTexture];
	ObjModel::NumNormal= copy.NumNormal;
	ObjModel::NumTexCoord= copy.NumTexCoord;
	ObjModel::NumTriangle= copy.NumTriangle;
	ObjModel::NumVertex= copy.NumVertex;
	ObjModel::NumTexture=copy.NumTexture;
	ObjModel::NumMtl=copy.NumMtl;



	for(int i= 0; i< NumNormal; ++i)
		ObjModel::NormalArray[i] = copy.NormalArray[i];

	for(int i= 0; i < NumTexCoord; ++i)
		ObjModel::TexCoordArray[i] = copy.TexCoordArray[i];

	for(int i= 0; i< NumTriangle; ++i)
		ObjModel::TriangleArray[i] = copy.TriangleArray[i];

	for(int i= 0; i< NumVertex; ++i)
		ObjModel::VertexArray[i] = copy.VertexArray[i];

	for(int i= 0; i <NumTexture; ++i)
	{
		ObjModel::TextureMarkArray[i] = copy.TextureMarkArray[i];
		ObjModel::TextureMark[i] = copy.TextureMark[i];
	}

	for(int i= 0; i< NumMtl; ++i)
		ObjModel::TextureArray[i] = copy.TextureArray[i];

}	

ObjModel& ObjModel::operator=(const ObjModel &right)
{
	FreeObjMdel();
	NormalArray = new ObjNormal[right.NumNormal];
	TexCoordArray = new ObjTexCoord[right.NumTexCoord];
	TriangleArray = new ObjTriangle[right.NumTriangle];
	VertexArray = new ObjVertex[right.NumVertex];
	TextureMark = new unsigned int[right.NumTexture];
	TextureArray = new GLuint[right.NumMtl];
	TextureMarkArray = new GLuint *[right.NumTexture];
	NumNormal = right.NumNormal;
	NumTexCoord = right.NumTexCoord;
	NumTriangle = right.NumTriangle;
	NumVertex = right.NumVertex;
	NumTexture = right.NumTexture;
	NumMtl = right.NumMtl;
	

	for(int i = 0; i < NumNormal; i++)
		NormalArray[i] = right.NormalArray[i];

	for(int i = 0; i < NumTexCoord; i++)
		TexCoordArray[i] = right.TexCoordArray[i];

	for(int i = 0; i < NumTriangle; i++)
		TriangleArray[i] = right.TriangleArray[i];

	for(int i = 0; i < NumVertex; i++)
		VertexArray[i] = right.VertexArray[i];

	for(int i= 0; i <NumTexture; i++)
	{
		ObjModel::TextureMarkArray[i] = right.TextureMarkArray[i];
		ObjModel::TextureMark[i] = right.TextureMark[i];
	}

	for(int i= 0; i< NumMtl; i++)
		ObjModel::TextureArray[i] = right.TextureArray[i];

	return *this;
}


ObjLoader::ObjLoader() 
{
	fileName = NULL;
	theObj = NULL;
}

ObjLoader::~ObjLoader() 
{
	FreeObj();
}

void ObjLoader::FreeObj(void)
{
	if(fileName != NULL){ delete fileName;fileName= NULL;}
	if(theObj != NULL){ delete theObj;theObj= NULL;}
	if(texturen != NULL){ delete [] texturen;texturen= NULL;}
}

ObjModel ObjLoader::ReturnObj(void)
{
	return *theObj;;
}

ObjLoader::ObjLoader(string file)  
{
	fileName = new string(file);
	theObj = new ObjModel();
	ReadData();
}

void ObjLoader::LoadObj(string file) 
{
	FreeObj();
	fileName = new string(file);
	theObj = new ObjModel();
	ReadData();
}

void ObjLoader::LoadMtl(string mtlfilename)
{
	int mtlC=0,flag=0;
	AUX_RGBImageRec **TextureImage;
	string mtlbuffer , mtltemp , mtlf;
	ifstream mtlin(mtlfilename.c_str());
	        if( !mtlin)
	        {
	            cerr<<"error: unable to open input file: "<<mtlin<<endl;
	            return;
	        }
			while( !mtlin.eof() ) 
			{
				getline(mtlin, mtlbuffer);
				if(mtlbuffer.substr(0,6) == "newmtl")
					theObj->NumMtl++;
			}
			texturen = new string[theObj->NumMtl];
	        TextureImage = new AUX_RGBImageRec *[theObj->NumMtl];
			theObj->TextureArray = new GLuint[theObj->NumMtl];
			mtlin.close();


			mtlin.open(mtlfilename.c_str());

			mtlin.clear();
			while( !mtlin.eof() ) 
			{
				getline(mtlin, mtlbuffer);
				if(mtlbuffer == "");
				else if(mtlbuffer.substr(0,6) == "newmtl")
				{
					istringstream line(mtlbuffer);
					line>>mtltemp>>texturen[mtlC];
					mtlC++;
				}
				else if(mtlbuffer.substr(1,6) == "map_Kd")
				{
					istringstream line(mtlbuffer);
					line>>mtltemp>>mtlf;
					while(flag<mtlC-1)
					{
						TextureImage[flag]=NULL;
						flag++;
					}
					TextureImage[mtlC-1]=auxDIBImageLoadA(mtlf.c_str());
					glGenTextures(1, &theObj->TextureArray[mtlC-1]);
					glBindTexture(GL_TEXTURE_2D, theObj->TextureArray[mtlC-1]);
					glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[mtlC-1]->sizeX, TextureImage[mtlC-1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[mtlC-1]->data);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
					flag++;
				}
			}
			while(flag<=mtlC-1)
					{
						TextureImage[flag]=NULL;
						flag++;
					}
			mtlin.close();
			mtlin.clear();
			for(int i=0;i<theObj->NumMtl;i++)
			{
				if(TextureImage[i] != NULL)
				   delete TextureImage[i];
			}
			delete [] TextureImage;
}

void ObjLoader::ReadData(void)  
{
	string buffer,mtlfilename;

	ifstream input(fileName->c_str());


	if( !input)
	{
		cerr<<"error: unable to open input file: "<<input<<endl;
		return;
	}

	while( !input.eof() )  {
		getline(input, buffer);
		
		if(buffer.substr(0,2) == "vn")
			theObj->NumNormal++;
		else if(buffer.substr(0,2) == "vt")
			theObj->NumTexCoord++;
		else if(buffer.substr(0,1) == "v")/////////////////////////////判断顺序极其重要，不能颠倒！！！
			theObj->NumVertex++; 
		else if(buffer.substr(0,1) == "f")
			theObj->NumTriangle++;
		else if(buffer.substr(0,6) == "usemtl")
			theObj->NumTexture++;

	}
	theObj->NormalArray =   new ObjNormal[theObj->NumNormal]; 
	theObj->TexCoordArray = new ObjTexCoord[theObj->NumTexCoord];
	theObj->TriangleArray = new ObjTriangle[theObj->NumTriangle];
	theObj->VertexArray =   new ObjVertex[theObj->NumVertex];
	theObj->TextureMark =   new unsigned int[theObj->NumTexture];
	theObj->TextureMarkArray =new GLuint *[theObj->NumTexture];

	input.close();

	input.open(fileName->c_str());

	input.clear();

	if( !input)
	{
		cerr<<"error: unable to open input file: "<<input<<endl;
		return;
	}

	int nC, vC, tC, fC, mC, sC;
	nC = vC = tC = fC = mC = sC = 0;

	while( !input.eof() )  {
		getline(input, buffer);
		istringstream line(buffer);
		string temp;
		string	f1, f2, f3;
			
		if(buffer.substr(0,2) == "vn")  {
			line>> temp>> f1>> f2>> f3;
			theObj->NormalArray[nC].X = atof(f1.c_str());
			theObj->NormalArray[nC].Y = atof(f2.c_str());
			theObj->NormalArray[nC].Z = atof(f3.c_str());
			++nC;
		}
		else if(buffer.substr(0,2) == "vt")  {
			line >> temp >> f1 >> f2;
			theObj->TexCoordArray[tC].U = atof(f1.c_str());
			theObj->TexCoordArray[tC].V = atof(f2.c_str());
			++tC;
		}				
		else if(buffer.substr(0,1) == "v")  {
			line>> temp>> f1>> f2>> f3;
			theObj->VertexArray[vC].X = atof(f1.c_str());
			theObj->VertexArray[vC].Y = atof(f2.c_str());
			theObj->VertexArray[vC].Z = atof(f3.c_str());
			++vC;
		}
		else if(buffer.substr(0,1) == "f")  {
			line>> temp>> f1>> f2>> f3;
				
			int sPos = 0;
			int ePos = sPos;
			string temp;
			ePos = f1.find_first_of("/");
			if(ePos != string::npos)  {
				temp = f1.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].Vertex[0] = atoi(temp.c_str()) - 1;

				sPos = ePos+1;
				ePos = f1.find("/", sPos);
				temp = f1.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].TexCoord[0] = atoi(temp.c_str()) - 1;

				sPos = ePos+1;
				ePos = f1.length();
				temp = f1.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].Normal[0] = atoi(temp.c_str()) - 1;
			}

			sPos = 0;
			ePos = f2.find_first_of("/");
			if(ePos != string::npos)  {
				temp = f2.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].Vertex[1] = atoi(temp.c_str()) - 1;

				sPos = ePos + 1;
				ePos = f2.find("/", sPos+1);
				temp = f2.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].TexCoord[1] = atoi(temp.c_str()) - 1;

				sPos = ePos + 1;
				ePos = f2.length();
				temp = f2.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].Normal[1] = atoi(temp.c_str()) - 1;
			}

			sPos = 0;
			ePos = f3.find_first_of("/");
			if(ePos != string::npos)  {
				temp = f3.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].Vertex[2] = atoi(temp.c_str()) - 1;

				sPos = ePos + 1;
				ePos = f3.find("/", sPos+1);
				temp = f3.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].TexCoord[2] = atoi(temp.c_str()) - 1;

				sPos = ePos + 1;
				ePos = f3.length();
				temp = f3.substr(sPos, ePos - sPos);
				theObj->TriangleArray[fC].Normal[2] = atoi(temp.c_str()) - 1;
			}
			++fC;
		}
		
		else if(buffer.substr(0,6) == "usemtl")
		{
			line>>temp>>f1;
			if(fC!=0)
			{
			   theObj->TextureMark[mC] = fC;
			   ++mC;
			}
			for(sC=0;sC<theObj->NumMtl;sC++)
			{
				if(f1==texturen[sC])
					break;
			}
			theObj->TextureMarkArray[mC]=&theObj->TextureArray[sC];
		}
		else if(buffer.substr(0,6) == "mtllib")
		{
			line>>temp>>mtlfilename;
			LoadMtl(mtlfilename);
		}
	}
	theObj->TextureMark[mC] = theObj->NumTriangle;
	input.close();
	input.clear();
}