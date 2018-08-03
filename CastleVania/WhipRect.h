#pragma once
#include <Windows.h>
#include <conio.h>
#include <d3d9.h>
#include <dinput.h>

class WhipRect
{
public:
	float x;
	float y;
	float w;
	float h;
	WhipRect();
	WhipRect(float _x, float _y, float _w, float _h);
	~WhipRect();
	bool IsIntersect(WhipRect _wr);
	RECT* ToRect();
};

