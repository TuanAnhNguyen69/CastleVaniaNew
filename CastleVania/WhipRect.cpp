#include "WhipRect.h"



WhipRect::WhipRect()
{
}

WhipRect::WhipRect(float _x, float _y, float _w, float _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

WhipRect::~WhipRect()
{
}

bool WhipRect::IsIntersect(WhipRect _wr)
{

	if (_wr.x > x + w ||
		x > _wr.x + _wr.w ||
		_wr.y > y + h ||
		y > _wr.y + _wr.h)
		return false;
	return true;
}

RECT* WhipRect::ToRect()
{
	RECT* rect = new RECT;
	rect->left = x;
	rect->top = y;
	rect->right = x + w;
	rect->bottom = y + h;
	return rect;
}