#ifndef _SWEPTAABB_
#define _SWEPTAABB_

#include <cmath>
#include <algorithm>
#include <limits>

struct Box
{
	// toa do top-left cua Box
	float x, y;

	// kich thuoc cua Box
	float w, h;

	// van toc cua Box
	float vx, vy;


	Box(float _x, float _y, float _w, float _h, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = _vx;
		vy = _vy;
	}

	Box(float _x, float _y, float _w, float _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = 0.0f;
		vy = 0.0f;
	}

	
};

inline bool isColliding(const Box& object, const Box& other)
{
	float left = other.x - (object.x + object.w);
	float top = (other.y + other.h) - object.y;
	float right = (other.x + other.w) - object.x;
	float bottom = other.y - (object.y + object.h);

	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}

inline bool AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y - b1.h > b2.y || b1.y < b2.y - b2.h);
}

inline Box getSweptBroadphaseBox(const Box& object, float t)
{
	float x = object.vx > 0 ? object.x : object.x + object.vx;
	float y = object.vy > 0 ? object.y : object.y + object.vy;
	float w = object.w + abs(object.vx *t);
	float h = object.h + abs(object.vy *t);

	return Box(x, y, w, h);
}

inline float sweptAABB(const Box& b1, const Box& b2, ECollisionDirection& result, float dt)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0.0f)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}
	if (b1.vy < 0.0f)
	{
		yInvEntry = (b1.y - b1.h) - b2.y;
		yInvExit = (b2.y - b2.h) - (b1.y - b1.h);
	}
	else
	{
		yInvEntry = (b2.y - b2.h) - b1.y;
		yInvExit = b2.y - b1.y;
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;
	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx / dt;
		xExit = xInvExit / b1.vx / dt;
	}
	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (b1.vy *dt);
		yExit = yInvExit / (b1.vy *dt);
	}

	float entryTime = xEntry > yEntry ? xEntry : yEntry;
	float exitTime = xExit < yExit ? xExit : yExit;

	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		result = ECollisionDirection::Colls_None;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				result = ECollisionDirection::Colls_Left;
			}
			else
			{
				result = ECollisionDirection::Colls_Right;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				result = ECollisionDirection::Colls_Bot;
			}
			else
			{
				result = ECollisionDirection::Colls_Top;
			}
		}
		// return the time of collision
		return entryTime;
	}
}
#endif