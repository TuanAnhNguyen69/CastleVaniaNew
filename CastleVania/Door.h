#pragma once
#include "GameObject.h"
class Door :
	public GameObject
{
private:
	bool isOpen;
	bool playedOpen;
	bool playedClose;
public:
	int _timeCount;
	bool animating;
	Door(void);
	Door(float _posX, float _posY, int _width, int _height);
	~Door(void);
	void RenderOpen();
	void RenderClose();
	bool GetOpenDoor();
	bool isAnimating();
	void Update(int dt);
	void ResetDoor();
	void Draw(GCamera*, int vX, int stage);

};

