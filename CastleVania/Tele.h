#include "GameObject.h" 

class Tele : public GameObject {
public: 
	Tele();
	Tele(float _posX, float _posY, int _width, int _height);
	~Tele();
};