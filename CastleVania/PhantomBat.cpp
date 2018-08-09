#include "PhantomBat.h"

PhantomBat::PhantomBat() : Enemy()
{
}

PhantomBat::PhantomBat(float _posX, float _posY) : Enemy(_posX, _posY, 0.0f, 0.0f, EnumID::PhantomBat_ID)
{
	hp = 1;
	damage = 2;
	point = 200;
}

PhantomBat::~PhantomBat()
{
}

void PhantomBat::MovePath(int dt)
{
}

void PhantomBat::Draw(GCamera * camera)
{
}

void PhantomBat::Update(int dt)
{
}

void PhantomBat::SetActive(float _posX_Simon, float _posY_Simon)
{
}

void PhantomBat::Collision()
{

}
