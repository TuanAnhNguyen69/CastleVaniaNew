#include "PhantomBat.h"

PhantomBat::PhantomBat()
{
}

PhantomBat::PhantomBat(float _posX, float _posY) : ActiveObject(_posX, _posY, 0.0f, 0.0f, EnumID::PhantomBat_ID)
{

}

PhantomBat::~PhantomBat()
{
}

void PhantomBat::MovePath(int deltaTime)
{
}

void PhantomBat::Draw(GCamera * camera)
{
}

void PhantomBat::Update(int deltaTime)
{
}

void PhantomBat::SetActive(float _posX_Simon, float _posY_Simon)
{
}

void PhantomBat::Collision()
{
}
