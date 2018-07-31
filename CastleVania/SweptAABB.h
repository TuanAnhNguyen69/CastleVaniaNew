#ifndef _SWEPTAABB_
#define _SWEPTAABB_

#include <cmath>
#include <algorithm>
#include <limits>
// mot GameObject la 1 Box (hinh chu nhat) co cac thuoc tinh
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


//Kiem tra 2 doi tuong co giao nhau khong
static bool AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y - b1.h > b2.y || b1.y < b2.y - b2.h);
}

static bool AABB(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0.0f;

	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y - b1.h);
	float b = (b2.y - b2.h) - b1.y;

	// check that there was a collision
	if (l > 0 || r < 0 || t < 0 || b > 0)
		return false;

	// find the offset of both sides
	moveX = abs(l) < r ? l : r;
	moveY = abs(b) < t ? b : t;

	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

// tra ve 1 Box keo dai tu Box truoc va cham den Box sau va cham
// de sau nay lay Box do xet xem co chong len Object bi va cham khong
// neu khong thi khong can phai xet tiep
static Box GetSweptBroadphaseBox(Box b, int dt)
{
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f);

	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx * dt;
	broadphasebox.y = b.vy < 0 ? b.y : b.y + b.vy *dt;
	broadphasebox.w = b.vx > 0 ? b.vx * dt + b.w : b.w - b.vx * dt;
	broadphasebox.h = b.vy > 0 ? b.vy * dt + b.h : b.h - b.vy * dt;

	return broadphasebox;
}

// Xet va cham giua Box1 di chuyen va Box2 tinh
// Tra ve thoi gian va cham (>0 va <1)
// Neu <= 0, la 2 Box dang di ra xa nhau
// Neu >= 1, la 2 Box chua va cham
// vi tri moi duoc tinh bang: box.x = box.x + box.vx * collision_time
// normalx and normaly return the normal of the collided surface (this can be used to do a response)
static float SweptAABB(Box b1, Box b2, float& normalx, float& normaly, int dt)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y

	// ??ng b? d?u cho cùng h??ng thôi
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
		yInvEntry = b2.y - (b1.y - b1.h);
		yInvExit = (b2.y - b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y - b2.h) - b1.y;
		yInvExit = b2.y - (b1.y - b1.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)

	//tìm th?i gian ?? b?t ??u và k?t thúc va ch?m :
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / (b1.vx * dt);
		xExit = xInvExit / (b1.vx * dt);
	}

	if (b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (b1.vy * dt);
		yExit = yInvExit / (b1.vy * dt);
	}

  // th?i gian va ch?m là th?i gian l?n nh?t c?a 2 tr?c (2 tr?c ph?i cùng ti?p xúc thì m?i va ch?m)

	float entryTime = max(xEntry, yEntry);
// th?i gian h?t va ch?m là th?i gian c?a 2 tr?c, (1 cái ra kh?i là object h?t va ch?m)
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}


#endif