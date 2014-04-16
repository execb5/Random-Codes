#include "GameObject.h"

GameObject::GameObject()
{
	tx = ty = 0;
	ex = ey = 1;
	angle = 0;
}

GameObject::~GameObject()
{

}

float GameObject::getTx(void)
{
	return tx;
}

float GameObject::getTy(void)
{
	return ty;
}

float GameObject::getEx(void)
{
	return ex;
}

float GameObject::getEy(void)
{
	return ey;
}

float GameObject::getAngle(void)
{
	return angle;
}

void GameObject::incrementAngle()
{
	angle += 1;
}

void GameObject::decrementAngle()
{
	angle -= 1;
}

void GameObject::incrementTx()
{
	tx += 10;
}

void GameObject::incrementTy()
{
	ty += 10;
}

void GameObject::incrementEx()
{
	ex += 0.1;
}

void GameObject::incrementEy()
{
	ey += 0.1;
}

void GameObject::decrementTx()
{
	tx -= 10;
}

void GameObject::decrementTy()
{
	ty -= 10;
}

void GameObject::decrementEx()
{
	ex -= 0.1;
}

void GameObject::decrementEy()
{
	ey -= 0.1;
}
