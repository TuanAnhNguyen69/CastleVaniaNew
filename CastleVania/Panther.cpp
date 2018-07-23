#include "Panther.h"



Panther::Panther() : ActiveObject()
{
	active = true;
}

Panther::Panther(float _posX, float _posY)
	: ActiveObject(_posX, _posY, PANTHER_SPEED, 0, EnumID::Panther_ID)
{
	active = true;
	canBeKilled = true;
	type = ObjectType::Enemy_Type;
	isJump = false;
}
Panther::~Panther()
{
}

void Panther::Draw(GCamera* camera)
{
	ActiveObject::Draw(camera);
}

void Panther::Update(int deltaTime)
{
	posX += vX * deltaTime;
	if (posX <= width / 2 + 5 || posX >= G_MapWidth - width / 2 - 5)
		vX = -vX;
	
	if(isJump)
	{
		posY += vY;
		if (posY >= PANTHER_JUMP_HEIGHT)
			vY = -vY;

		//Neu cham dat, chua dinh nghia
		if (false)
		{
			isJump = false;
			isGrounding = true;
			vY = 0.0f;
		}
	}
	else
		sprite->Update(deltaTime);
}

void Panther::SetActive(float _posX_Simon, float _posY_Siomon)
{
	bool simonLeft = true;
	if (posX < _posX_Simon)
		simonLeft = false;

	if (abs(posX - _posX_Simon) <= 200)
	{
		if ((posY - _posY_Siomon) <= 0 && (posY - _posY_Siomon) >= -50)
		{
			if (!simonLeft)
				vX = PANTHER_SPEED;
			else
				vX = -PANTHER_SPEED;
		}
		else
			if ((posY - _posY_Siomon) >= 30 && (posY - _posY_Siomon) <= 150)
				Jump();
	}
}

void Panther::Jump()
{
	isGrounding = false;
	vX = -PANTHER_SPEED;
	vY = PANTHET_JUMP_SPEED;
	isJump = true;
	sprite = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Panther_ID), 1, 3, 60);
	sprite->SelectIndex(3);
	
}

void Panther::Collision()
{
	//Chua dinh nghia
}