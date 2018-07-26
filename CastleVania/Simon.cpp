#include "Simon.h"



Simon::Simon():ActiveObject()
{
}

Simon::Simon(int _posX, int _posY) : ActiveObject(_posX, _posY, 0, -SPEED_Y, EnumID::Simon_ID)
{
	hp = 40;
	action = Action::Stand;
	giatoc = GIATOC;
	isDie = false;
	isJump = false;
	isSit = false;
	isStop = false;

	simonJum = new GSprite(TextureManager::getInstance()->getTexture(EnumID::Simon_ID), 4, 4, 300);
}

Simon::~Simon()
{
}


void Simon::Draw(GCamera* camera)
{
	//Rot xuong vuc
	if (posY < (camera->viewport.y - G_ScreenHeight))
	{
		hp = 0;
		isDie = true;
	}

	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (isDie)
	{
		simonDeath->DrawFlipX(center.x, center.y);
	}
	else
	{
		if (vX > 0 && vLast > 0)
		{
			sprite->DrawFlipX(center.x, center.y);
		}
		else
			sprite->Draw(center.x, center.y);
	}

}

void Simon::Update(int deltaTime)
{
	sprite->Update(deltaTime);

	if (isJump)
	{
		sprite->SelectIndex(4);
		posY += vY * deltaTime + 0.4 * deltaTime * deltaTime * giatoc;
		if (vY > SPEED_FALL)
			vY += giatoc * deltaTime;
		return;
	}
	else
		vY = 0;
}

void Simon::RunLeft()
{
	if (isStop && vLast < 0)
		vX = 0;
	else 
	{
		isStop = false;
		vX = -SPEED_X;
		vLast = vX;
	}
	action = Action::Run_Left;
}

void Simon::RunRight()
{
	if (isStop && vLast > 0)
		vX = 0;
	else
	{
		isStop = false;
		vX = SPEED_X;
		vLast = vX;
	}
	action = Action::Run_Right;
}

void Simon::Jump()
{
	if (!isJump)
	{
		giatoc = -GIATOC;
		vY = sqrt(-2 * giatoc * MAX_HEIGHT);
		sprite->SelectIndex(4);
		action = Action::Jump;
		isJump = true;
	}
	else
		vY = 0;
}

void Simon::Sit()
{
	if (!isJump)
	{
		posY -= 16;
		sprite->SelectIndex(4);
		vX = 0;
		//vY = -(SPEED_Y + 0.3f);
		vY = 0;
		isSit = true;
		action = Action::Sit;
	}
}

void Simon::Stop()
{
	vX = 0;
	switch (action)
	{
		case Action::Stand:
		case Action::Fight:
		case Action::Fall:
			return;
	}
	if (isSit)
	{
		posY += 16;
		isSit = false;
	}
	action = Action::Stand;
	sprite->SelectIndex(0);
}

bool Simon::AutoMove(int &rangeMove, int dt)
{
	Stop();
	if (rangeMove == 0)
		return true;
	if (rangeMove > 0)
	{
		rangeMove -= AUTO_MOVE_RANGE;
		posX += AUTO_MOVE_RANGE;
	}
	else
	{
		rangeMove += AUTO_MOVE_RANGE;
		posX -= AUTO_MOVE_RANGE;
	}
	sprite->Update(dt);
	return false;
}

Box Simon::GetBox()
{
	if (isJump || isSit)
	{
		return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 22);
	}
	return Box(posX - width / 2 + 14.5f, posY + height / 2 - 3, width - 29, height - 6);
}