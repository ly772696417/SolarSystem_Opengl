#pragma once

#include "header.h"

class Camera
{
public:
	Camera();
	Camera(Point eye,Point centery,Vector up);
	~Camera(void);

	void SetCamera();

private:
	Point m_eye;
	Point m_centery;
	Vector m_up;
};

